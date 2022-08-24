// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadSubsystem.h"

#include "AbilitySystemComponent.h"
#include "GardenActorsSubsystem.h"
#include "JsonObjectConverter.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "CreatureOasis/Actors/GardenActor.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"
#include "CreatureOasis/Interfaces/CreatureComponentLoadableInterface.h"
#include "CreatureOasis/Structs/ProjectSettings/GardenSettings.h"

#include "Kismet/GameplayStatics.h"

USaveLoadSubsystem::USaveLoadSubsystem()
	: LoadedSlotName(TEXT("Default"))
{
}

void USaveLoadSubsystem::PrepareGardenSaveGame()
{
	if (!IsValid(CreatureSaveGame))
	{
		return;
	}
	
	const UWorld* World = GetGameInstance()->GetWorld();

	// Hard skip Worlds that do not contain "Garden" in their name, 
	if (!World->GetMapName().Contains("Garden"))
	{
		return;
	}

	TSharedPtr<FJsonObject> RootJsonObject(new FJsonObject);
	
	if (!CreatureSaveGame->GardenActorsJsonString.IsEmpty())
	{
		TSharedPtr<FJsonValue> RootDeserializedJsonValue;
	
		// Create a reader pointer to read the json data
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(CreatureSaveGame->GardenActorsJsonString);

		if (!FJsonSerializer::Deserialize(Reader, RootDeserializedJsonValue))
		{
			return;
		}

		RootJsonObject = RootDeserializedJsonValue->AsObject();
	}
	else
	{
		RootJsonObject = MakeShared<FJsonObject>();
	}

	// Remove Map if RootJsonObject has it, this so we can recreate it later on
	if (RootJsonObject->HasField(World->GetMapName()))
	{
		RootJsonObject->RemoveField(World->GetMapName());
	}
	
	const TSharedPtr<FJsonObject> GardenRootJsonObject(new FJsonObject());
	RootJsonObject->SetObjectField(World->GetMapName(), GardenRootJsonObject);

	UpdateSaveGameWithGardenObjects(GardenRootJsonObject);
	UpdateSaveGameWithCreatures(GardenRootJsonObject);

	const TSharedRef< TJsonWriter< > > Writer = TJsonWriterFactory<>::Create(&CreatureSaveGame->GardenActorsJsonString);
	FJsonSerializer::Serialize(RootJsonObject.ToSharedRef(), Writer);
	
	UE_LOG(LogTemp, Warning, TEXT("resulting jsonString -> %s"), *CreatureSaveGame->GardenActorsJsonString);
}

void USaveLoadSubsystem::UpdateSaveGameWithGardenObjects(const TSharedPtr<FJsonObject> InGardenRootJsonObject)
{
	UGardenActorsSubsystem* GardenActorsSubsystem = GetGameInstance()->GetWorld()->GetSubsystem<UGardenActorsSubsystem>();

	const TSharedPtr<FJsonObject> GardenObjectsRootJsonObject(new FJsonObject());
	const TSharedPtr<FJsonObject> GardenObjectsJsonObject(new FJsonObject());
	
	InGardenRootJsonObject->SetObjectField(TEXT("GardenObjects"), GardenObjectsRootJsonObject);
	
	TArray<TSharedPtr<FJsonValue>> CreatureJsonValueObjectArray;
	
	TArray<AActor*> CreatureActors;
	GardenActorsSubsystem->GetGardenActorsByTag(FGameplayTag::RequestGameplayTag("Type.Garden.Fruit"),CreatureActors);
	
	for (AActor* Actor : CreatureActors)
	{
		TSharedPtr<FJsonObject> CreatureJsonObject(new FJsonObject);
		
		const AGardenActor* GardenActor = Cast<AGardenActor>(Actor);
		UAbilitySystemComponent* ASC = GardenActor->GetAbilitySystemComponent();
		
		if (ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Type.Unsavable")))
		{
			continue;
		}
		
		TSharedPtr<FJsonObject> GardenObjectData = MakeShared<FJsonObject>();
		GardenObjectData->SetStringField("MainTypeTag", GardenActor->GetMainTypeTag().ToString());
		GardenObjectData->SetStringField("SubTypeTag", GardenActor->GetSubTypeTag().ToString());

		CreatureJsonObject->SetObjectField("Data", GardenObjectData);
		CreatureJsonObject->SetObjectField(TEXT("Attributes"), SerializeAttributesIntoJsonObject(ASC));

		CreatureJsonValueObjectArray.Add(MakeShared<FJsonValueObject>(CreatureJsonObject));
	}
	
	InGardenRootJsonObject->SetArrayField(TEXT("GardenObjects"), CreatureJsonValueObjectArray);
}

void USaveLoadSubsystem::UpdateSaveGameWithCreatures(const TSharedPtr<FJsonObject> InGardenRootJsonObject)
{
	UGardenActorsSubsystem* GardenActorsSubsystem = GetGameInstance()->GetWorld()->GetSubsystem<UGardenActorsSubsystem>();

	const TSharedPtr<FJsonObject> GardenCreatureRootJsonObject(new FJsonObject());
	const TSharedPtr<FJsonObject> GardenObjectsJsonObject(new FJsonObject());
	
	InGardenRootJsonObject->SetObjectField(TEXT("Creatures"), GardenCreatureRootJsonObject);
	
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

		FCreatureDataLoad CreatureDataLoad;

		TArray<UActorComponent*> Components = GASCharacter->GetComponentsByInterface(UCreatureComponentLoadableInterface::StaticClass());
		for	(UActorComponent* Component : Components)
		{
			ICreatureComponentLoadableInterface::Execute_GatherCreatureData(Component, CreatureDataLoad);
		}
		
		FJsonObjectConverter JsonObjectConverter;
		TSharedPtr<FJsonObject> CreatureDataLoadJsonObject = JsonObjectConverter.UStructToJsonObject(CreatureDataLoad);
		
		CreatureJsonObject->SetObjectField("Data", CreatureDataLoadJsonObject);
		CreatureJsonObject->SetObjectField(TEXT("Attributes"), SerializeAttributesIntoJsonObject(ASC));

		CreatureJsonValueObjectArray.Add(MakeShared<FJsonValueObject>(CreatureJsonObject));
	}
	
	InGardenRootJsonObject->SetArrayField(TEXT("Creatures"), CreatureJsonValueObjectArray);
}

void USaveLoadSubsystem::LoadGardenUsingSaveObject()
{
	if (!IsValid(CreatureSaveGame) && CreatureSaveGame->GardenActorsJsonString.IsEmpty())
	{
		return;
	}
	
	UWorld* World = GetGameInstance()->GetWorld();

	// Hard skip Worlds that do not contain "Garden" in their name, 
	if (!World->GetMapName().Contains("Garden"))
	{
		return;
	}
	
	const UGardenSettings* GardenSettings = GetDefault<UGardenSettings>();

	// Create a reader pointer to read the json data
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(CreatureSaveGame->GardenActorsJsonString);
	
	TSharedPtr<FJsonValue> RootJsonValue;
	if (FJsonSerializer::Deserialize(Reader, RootJsonValue) && RootJsonValue->AsObject()->HasField(World->GetMapName()))
	{
		LoadAllCreatures(RootJsonValue, GardenSettings);
		LoadAllGardenObjects(RootJsonValue, GardenSettings);
	}
	else
	{
		const TSubclassOf<AActor> ClassTypeToSpawn = GardenSettings->GardenActorTypeClassRelationMap.FindRef(FGameplayTag::RequestGameplayTag("Type.Creature"));

		// If no save-data is present for this specific map, we spawn a set amount of Creatures at start
		for (int32 Count = 0; Count < GardenSettings->AmountOfStartingCreaturesToSpawnOnEmptySave; Count++)
		{
			FNavLocation SpawnNavLocation;
			FRotator SpawnRotation(0.f, FMath::FRandRange(0.f, 360.f), 0.f);
			if (UNavigationSystemV1::GetCurrent(World)->GetRandomPoint(SpawnNavLocation))
			{
				AGASCharacter* SpawnedGASCharacter = Cast<AGASCharacter, AActor>(World->SpawnActor(ClassTypeToSpawn, &SpawnNavLocation.Location, &SpawnRotation, FActorSpawnParameters()));
				if (IsValid(SpawnedGASCharacter))
				{
					SpawnedGASCharacter->SpawnDefaultController();
				}
			}
		}
	}
}

void USaveLoadSubsystem::LoadAllCreatures(const TSharedPtr<FJsonValue> InRootJsonObject, const UGardenSettings* InGardenSettings) const
{
	const TSubclassOf<AActor> ClassTypeToSpawn = InGardenSettings->GardenActorTypeClassRelationMap.FindRef(FGameplayTag::RequestGameplayTag("Type.Creature"));
	UWorld* World = GetGameInstance()->GetWorld();

	TArray<TSharedPtr<FJsonValue>> CreatureArray = InRootJsonObject->AsObject()->GetObjectField(World->GetMapName())->GetArrayField("Creatures");

	for (const TSharedPtr<FJsonValue> CreatureEntry : CreatureArray)
	{
		FNavLocation SpawnNavLocation;
		FRotator SpawnRotation(0.f, FMath::FRandRange(0.f, 360.f), 0.f);
		if (UNavigationSystemV1::GetCurrent(World)->GetRandomPoint(SpawnNavLocation))
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			SpawnNavLocation.Location += FVector(0.f, 0.f, 100.f);
			
			AGASCharacter* SpawnedGASCharacter = Cast<AGASCharacter, AActor>(World->SpawnActor(ClassTypeToSpawn, &SpawnNavLocation.Location, &SpawnRotation, SpawnParameters));
			if (IsValid(SpawnedGASCharacter))
			{
				// Lets load some save data
				const TSharedPtr<FJsonObject> CreatureObjectEntry = CreatureEntry->AsObject();
				SpawnedGASCharacter->SpawnDefaultController();
				
				UAbilitySystemComponent* AbilitySystemComponent = SpawnedGASCharacter->GetAbilitySystemComponent();
	
				InitAttributesFromJsonObject(AbilitySystemComponent, CreatureObjectEntry->GetObjectField("Attributes"));
				
				FCreatureDataLoad CreatureDataLoad;
				FJsonObjectConverter JsonObjectConverter;
				if (CreatureObjectEntry->HasField("Data")
					&& JsonObjectConverter.JsonObjectToUStruct(CreatureObjectEntry->GetObjectField("Data").ToSharedRef(), FCreatureDataLoad::StaticStruct(), &CreatureDataLoad))
				{
					TArray<UActorComponent*> Components = SpawnedGASCharacter->GetComponentsByInterface(UCreatureComponentLoadableInterface::StaticClass());
					for	(UActorComponent* Component : Components)
					{
						ICreatureComponentLoadableInterface::Execute_LoadCreatureData(Component, CreatureDataLoad);
					}
				}
			}
		}
	}
}

void USaveLoadSubsystem::LoadAllGardenObjects(const TSharedPtr<FJsonValue> InRootJsonObject, const UGardenSettings* InGardenSettings) const
{
	UWorld* World = GetGameInstance()->GetWorld();

	TArray<TSharedPtr<FJsonValue>> CreatureArray = InRootJsonObject->AsObject()->GetObjectField(World->GetMapName())->GetArrayField("GardenObjects");

	for (const TSharedPtr<FJsonValue> CreatureEntry : CreatureArray)
	{
		FNavLocation SpawnNavLocation;
		FRotator SpawnRotation(0.f, FMath::FRandRange(0.f, 360.f), 0.f);
		if (UNavigationSystemV1::GetCurrent(World)->GetRandomPoint(SpawnNavLocation))
		{
			const TSharedPtr<FJsonObject> CreatureObjectEntry = CreatureEntry->AsObject();

			if (CreatureObjectEntry->HasField("Data"))
			{
				const FName MainTypeTagStr(CreatureObjectEntry->GetObjectField("Data")->GetStringField("MainTypeTag"));
				const FName SubTypeTagStr(CreatureObjectEntry->GetObjectField("Data")->GetStringField("SubTypeTag"));

				const TSubclassOf<AActor> ClassTypeToSpawn = InGardenSettings->GardenActorTypeClassRelationMap.FindRef(FGameplayTag::RequestGameplayTag(MainTypeTagStr));

				AGardenActor* SpawnedGardenActor = Cast<AGardenActor, AActor>(World->SpawnActor(ClassTypeToSpawn, &SpawnNavLocation.Location, &SpawnRotation, FActorSpawnParameters()));
				if (IsValid(SpawnedGardenActor))
				{
					UAbilitySystemComponent* AbilitySystemComponent = SpawnedGardenActor->GetAbilitySystemComponent();
					InitAttributesFromJsonObject(AbilitySystemComponent, CreatureObjectEntry->GetObjectField("Attributes"));
				
					SpawnedGardenActor->InitializeFromSaveGame(
					FGameplayTag::RequestGameplayTag(MainTypeTagStr)
					,FGameplayTag::RequestGameplayTag(SubTypeTagStr));
				}
			}
		}
	}
}

void USaveLoadSubsystem::UpdateSaveGameWithActiveTrackGenerator()
{
}

void USaveLoadSubsystem::LoadTrackFromSaveGame()
{
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
