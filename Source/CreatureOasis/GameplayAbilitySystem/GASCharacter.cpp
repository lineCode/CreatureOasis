// Fill out your copyright notice in the Description page of Project Settings.

#include "GASCharacter.h"

#include "BaseAbilitySystemComponent.h"
#include "BaseGameplayAbility.h"
#include "AttributeSets/ChaoCoreAttributeSet.h"

// Sets default values
AGASCharacter::AGASCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
}

// Called when the game starts or when spawned
void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(AbilitySystemComponent))
	{
		BaseAttributeSet = AbilitySystemComponent->GetSet<UBaseAttributeSet>();
	}
}

void AGASCharacter::InitializeAttributes()
{
	if (!IsValid(AbilitySystemComponent) && !IsValid(DefaultAttributes))
	{
		return;
	}
	
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void AGASCharacter::AddStartupEffects()
{
	if (!IsValid(AbilitySystemComponent) || AbilitySystemComponent->bStartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (const TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}

	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void AGASCharacter::GiveAbilities()
{
	if (!IsValid(AbilitySystemComponent) || AbilitySystemComponent->bAbilitiesGiven)
	{
		return;
	}
	
	// Grant abilities
	for (TSubclassOf<UBaseGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		if (IsValid(StartupAbility))
		{
			AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		}
	}

	AbilitySystemComponent->bAbilitiesGiven = true;
}

void AGASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	AddStartupEffects();
	GiveAbilities();
}

UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASCharacter::RemoveCharacterAbilities()
{
	if (!IsValid(AbilitySystemComponent) || !AbilitySystemComponent->bAbilitiesGiven)
	{
		return;
	}

	// Remove any abilities added from a previous call. This checks to make sure the ability is in the startup 'CharacterAbilities' array.
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	// Do in two passes so the removal happens after we have the full list
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->bAbilitiesGiven = false;
}

float AGASCharacter::GetCharacterLevel() const
{
	if (IsValid(BaseAttributeSet))
	{
		return BaseAttributeSet->GetLevel();
	}

	return 0.0f;
}
