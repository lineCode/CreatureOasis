#include "CreatureOasisBlueprintLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "CreatureOasisLoadingScreen/CreatureOasisLoadingScreen.h"

void UCreatureOasisBlueprintLibrary::PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime)
{
	FCreatureOasisLoadingScreenModule& LoadingScreenModule = FCreatureOasisLoadingScreenModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(bPlayUntilStopped, PlayTime);
}

void UCreatureOasisBlueprintLibrary::StopLoadingScreen()
{
	FCreatureOasisLoadingScreenModule& LoadingScreenModule = FCreatureOasisLoadingScreenModule::Get();
	LoadingScreenModule.StopInGameLoadingScreen();
}

FLinearColor UCreatureOasisBlueprintLibrary::GenerateRandomColor()
{
	return {FMath::RandRange(0.f, 1.f), FMath::RandRange(0.f, 1.f), FMath::RandRange(0.f, 1.f), 1.f};
}

bool UCreatureOasisBlueprintLibrary::GetDirectActiveChildTag(UAbilitySystemComponent* ASC, FGameplayTag ParentTag, FGameplayTag& OutGameplayTag)
{
	if (!IsValid(ASC))
	{
		return false;
	}
	
	const FGameplayTagContainer DirectChildTagContainer = UGameplayTagsManager::Get().RequestGameplayTagChildren(ParentTag);

	FGameplayTagContainer ASCTagContainer;
	ASC->GetOwnedGameplayTags(ASCTagContainer);
	
	TArray<FGameplayTag> ASCTagArray;
	ASCTagContainer.GetGameplayTagArray(ASCTagArray);
	
	for (FGameplayTag GameplayTag : ASCTagArray)
	{
		if (DirectChildTagContainer.HasTag(GameplayTag))
		{
			OutGameplayTag = GameplayTag;
			return true;
		}
	}
	
	return false;
}

bool UCreatureOasisBlueprintLibrary::GetNameOfTopMostChildTag(const FGameplayTag& TargetTag, FName& OutName)
{
	if (!TargetTag.IsValid())
	{
		return false;
	}
	
	TArray<FName> SplitTagArray;
	UGameplayTagsManager::Get().SplitGameplayTagFName(TargetTag, SplitTagArray);

	OutName = SplitTagArray[SplitTagArray.Num() - 1];
	
	return true;
}

bool UCreatureOasisBlueprintLibrary::GetRandomTagFromGameplayTagContainer(const FGameplayTagContainer InTagContainer,
	FGameplayTag& OutTag)
{
	if (!InTagContainer.IsValid())
	{
		return false;
	}
	
	TArray<FGameplayTag> TagArray;
	InTagContainer.GetGameplayTagArray(TagArray);

	OutTag = TagArray[FMath::RandRange(0, TagArray.Num() - 1)];
	
	return true;
}

FGameplayTag UCreatureOasisBlueprintLibrary::GetTypeTagAssignedToAbilitySystemComponent(
	UAbilitySystemComponent* AbilitySystemComponent)
{
	FGameplayTag ResultingTag = FGameplayTag::EmptyTag;
	UCreatureOasisBlueprintLibrary::GetDirectActiveChildTag(AbilitySystemComponent, FGameplayTag::RequestGameplayTag("Type"), ResultingTag);
	return ResultingTag;
}

void UCreatureOasisBlueprintLibrary::SetAttributeBaseInAbilitySystemComponent(const FGameplayAttribute& TargetAttribute, const float NewValue,
                                                                              UAbilitySystemComponent* AbilitySystemComponent)
{
	AbilitySystemComponent->SetNumericAttributeBase(TargetAttribute, NewValue);
}

FString UCreatureOasisBlueprintLibrary::GetNameOfGameplayAttribute(const FGameplayAttribute& TargetAttribute)
{
	if (TargetAttribute.IsValid())
	{
		return TargetAttribute.AttributeName;
	}
	
	return "None";
}
