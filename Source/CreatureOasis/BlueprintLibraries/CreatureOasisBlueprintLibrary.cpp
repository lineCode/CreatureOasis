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

bool UCreatureOasisBlueprintLibrary::GetDirectActiveChildTag(UAbilitySystemComponent* ASC, FGameplayTag ParentTag, FGameplayTag& InGameplayTag)
{
	const FGameplayTagContainer DirectChildTagContainer = UGameplayTagsManager::Get().RequestGameplayTagChildren(ParentTag);

	FGameplayTagContainer ASCTagContainer;
	ASC->GetOwnedGameplayTags(ASCTagContainer);
	
	TArray<FGameplayTag> ASCTagArray;
	ASCTagContainer.GetGameplayTagArray(ASCTagArray);
	
	for (FGameplayTag GameplayTag : ASCTagArray)
	{
		if (DirectChildTagContainer.HasTag(GameplayTag))
		{
			InGameplayTag = GameplayTag;
			return true;
		}
	}
	
	return false;
}
