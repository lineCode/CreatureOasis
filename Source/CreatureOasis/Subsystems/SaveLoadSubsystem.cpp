// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadSubsystem.h"

#include "AbilitySystemComponent.h"
#include "GardenActorsSubsystem.h"
#include "JsonObjectConverter.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"
#include "CreatureOasis/Structs/ProjectSettings/GardenSettings.h"
#include "Kismet/GameplayStatics.h"

USaveLoadSubsystem::USaveLoadSubsystem()
	: LoadedSlotName(TEXT("Default"))
{
}

void USaveLoadSubsystem::UpdateSaveGameWithGardenObjects()
{
	if (!IsValid(CreatureSaveGame))
	{
		return;
	}
	
	const UWorld* World = GetGameInstance()->GetWorld();
	UGardenActorsSubsystem* GardenActorsSubsystem = World->GetSubsystem<UGardenActorsSubsystem>();

	const TSharedPtr<FJsonObject> RootJsonObject(new FJsonObject);
	
	const TSharedPtr<FJsonObject> GardenRootJsonObject(new FJsonObject());
	const TSharedPtr<FJsonObject> GardenCreatureRootJsonObject(new FJsonObject());
	const TSharedPtr<FJsonObject> GardenObjectsJsonObject(new FJsonObject());

	RootJsonObject->SetObjectField(World->GetMapName(), GardenRootJsonObject);
	
	GardenRootJsonObject->SetObjectField(TEXT("Creatures"), GardenCreatureRootJsonObject);
	
	TArray<TSharedPtr<FJsonValue>> CreatureJsonValueObjectArray;
	
	TArray<AActor*> CreatureActors;
	GardenActorsSubsystem->GetGardenActorsByTag(FGameplayTag::RequestGameplayTag("Type.Creature"),CreatureActors);
	
	for (AActor* Actor : CreatureActors)
	{
		TSharedPtr<FJsonObject> CreatureJsonObject(new FJsonObject);
		
		const AGASCharacter* GASCharacter = Cast<AGASCharacter>(Actor);
		UAbilitySystemComponent* ASC = GASCharacter->GetAbilitySystemComponent();
		
		if (ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Type.Unsavable")))
		{
			continue;
		}
		
		CreatureJsonObject->SetStringField("Name", "Default");
		CreatureJsonObject->SetObjectField(TEXT("Attributes"), SerializeAttributesIntoJsonObject(ASC));

		CreatureJsonValueObjectArray.Add(MakeShared<FJsonValueObject>(CreatureJsonObject));
	}
	
	GardenRootJsonObject->SetArrayField(TEXT("Creatures"), CreatureJsonValueObjectArray);

	const TSharedRef< TJsonWriter< > > Writer = TJsonWriterFactory<>::Create(&CreatureSaveGame->GardenActorsJsonString);
	FJsonSerializer::Serialize(RootJsonObject.ToSharedRef(), Writer);
	
	UE_LOG(LogTemp, Warning, TEXT("resulting jsonString -> %s"), *CreatureSaveGame->GardenActorsJsonString);
}

void USaveLoadSubsystem::LoadGardenObjectsFromSaveGame()
{
	if (!IsValid(CreatureSaveGame) && CreatureSaveGame->GardenActorsJsonString.IsEmpty())
	{
		return;
	}
	
	TSharedPtr<FJsonValue> RootJsonValue;
	
	// Create a reader pointer to read the json data
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(CreatureSaveGame->GardenActorsJsonString);

	if (!FJsonSerializer::Deserialize(Reader, RootJsonValue))
	{
		return;
	}
	
	UWorld* World = GetGameInstance()->GetWorld();
	const UGardenSettings* GardenSettings = GetDefault<UGardenSettings>();

	TSharedPtr<FJsonObject> TestData = RootJsonValue->AsObject();
	TArray<TSharedPtr<FJsonValue>> CreatureArray = RootJsonValue->AsObject()->GetObjectField(World->GetMapName())->GetArrayField("Creatures");

	for (const TSharedPtr<FJsonValue> CreatureEntry : CreatureArray)
	{
		const TSubclassOf<AActor> ClassTypeToSpawn = GardenSettings->GardenActorTypeClassRelationMap.FindRef(FGameplayTag::RequestGameplayTag("Type.Creature"));
		
		FNavLocation SpawnNavLocation;
		FRotator SpawnRotation(0.f, FMath::FRandRange(0.f, 360.f), 0.f);
		UNavigationSystemV1::GetCurrent(World)->GetRandomPoint(SpawnNavLocation);

		AGASCharacter* SpawnedGASCharacter = Cast<AGASCharacter, AActor>(World->SpawnActor(ClassTypeToSpawn, &SpawnNavLocation.Location, &SpawnRotation, FActorSpawnParameters()));
		SpawnedGASCharacter->SpawnDefaultController();
		
		UAbilitySystemComponent* AbilitySystemComponent = SpawnedGASCharacter->GetAbilitySystemComponent();
		
		InitAttributesFromJsonObject(AbilitySystemComponent, CreatureEntry->AsObject()->GetObjectField("Attributes"));
	}
}

void USaveLoadSubsystem::WriteSaveGameToDisk() const
{
	if (!IsValid(CreatureSaveGame))
	{
		return;
	}

	UGameplayStatics::SaveGameToSlot(CreatureSaveGame, LoadedSlotName, 0);
}

void USaveLoadSubsystem::LoadSaveGameFromDisk()
{
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(LoadedSlotName, 0);
	
	if (!IsValid(LoadedGame))
	{
		LoadedGame = UGameplayStatics::CreateSaveGameObject(UCreatureOasisSaveGame::StaticClass());
	}

	CreatureSaveGame = Cast<UCreatureOasisSaveGame>(LoadedGame);
}

void USaveLoadSubsystem::InitAttributesFromJsonObject(UAbilitySystemComponent* AbilitySystemComponent, const TSharedPtr<FJsonObject> JsonObject) const
{
	TArray<FGameplayAttribute> GameplayAttributes;
	AbilitySystemComponent->GetAllAttributes(GameplayAttributes);
	
	// Create the GE at runtime.
	UGameplayEffect* GameplayEffect = NewObject<UGameplayEffect>(GetTransientPackage(), TEXT("RuntimeInstantGE"));
	GameplayEffect->DurationPolicy = EGameplayEffectDurationType::Instant; // Only instant works with runtime GE.
	
	for( FGameplayAttribute Attribute : GameplayAttributes )
	{
		if(!JsonObject->HasField(Attribute.GetName()))
		{
			continue;
		}

		// Add a simple scalable float modifier, which overrides MyAttribute with 42.
		// In real world applications, consume information passed via TriggerEventData.
		const int32 Idx = GameplayEffect->Modifiers.Num();
		GameplayEffect->Modifiers.SetNum(Idx + 1);
		FGameplayModifierInfo& ModifierInfo = GameplayEffect->Modifiers[Idx];
		ModifierInfo.Attribute.SetUProperty(Attribute.GetUProperty());
		ModifierInfo.ModifierMagnitude = FScalableFloat(JsonObject->GetNumberField(Attribute.GetName()));
		ModifierInfo.ModifierOp = EGameplayModOp::Override;
	}

	// Apply the GE.

	// Create the GESpec here to avoid the behavior of ASC to create GESpecs from the GE class default object.
	// Since we have a dynamic GE here, this would create a GESpec with the base GameplayEffect class, so we
	// would lose our modifiers. Attention: It is unknown, if this "hack" done here can have drawbacks!
	// The spec prevents the GE object being collected by the GarbageCollector, since the GE is a UPROPERTY on the spec.
	const FGameplayEffectSpec* GESpec = new FGameplayEffectSpec(GameplayEffect, {}, 0.f); // "new", since lifetime is managed by a shared ptr within the handle

	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GESpec);
}

TSharedPtr<FJsonObject> USaveLoadSubsystem::SerializeAttributesIntoJsonObject(UAbilitySystemComponent* AbilitySystemComponent)
{
	TSharedPtr<FJsonObject> JsonObject(new FJsonObject());
	
	TArray<FGameplayAttribute> GameplayAttributes;
	AbilitySystemComponent->GetAllAttributes(GameplayAttributes);

	const UAttributeSet* AttributeSet = AbilitySystemComponent->GetAttributeSet(UAttributeSet::StaticClass());
	
	for( FGameplayAttribute Attribute : GameplayAttributes )
	{
		JsonObject->SetNumberField(Attribute.GetName(), Attribute.GetNumericValueChecked(AttributeSet));
	}
	
	return JsonObject;
}
