// Fill out your copyright notice in the Description page of Project Settings.

#include "GASPawn.h"

#include "BaseAbilitySystemComponent.h"
#include "BaseGameplayAbility.h"
#include "AttributeSets/BaseAttributeSet.h"

// Sets default values
AGASPawn::AGASPawn()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
	
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("Attributes");
}

// Called to bind functionality to input
void AGASPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if(AbilitySystemComponent && PlayerInputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EAbilityInputID", static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, Binds);
	}
}

void AGASPawn::InitializeAttributes()
{
	if (!IsValid(AbilitySystemComponent) && DefaultAttributes)
	{
		return;
	}
	
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (SpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void AGASPawn::AddStartupEffects()
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
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}

	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void AGASPawn::GiveAbilities()
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

void AGASPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	AddStartupEffects();
	GiveAbilities();
}

UAbilitySystemComponent* AGASPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASPawn::RemoveCharacterAbilities()
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

int32 AGASPawn::GetCharacterLevel() const
{
	if (IsValid(BaseAttributeSet))
	{
		return BaseAttributeSet->GetLevel();
	}

	return 0.0f;
}

float AGASPawn::GetHealth() const
{
	if (IsValid(BaseAttributeSet))
	{
		return BaseAttributeSet->GetHealth();
	}

	return 0.0f;
}

