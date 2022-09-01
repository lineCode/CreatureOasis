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
	
// Based on https://forums.unrealengine.com/t/easy-offscreen-indicator-blueprint-node/21342
void UCreatureOasisBlueprintLibrary::FindScreenEdgeLocationForWorldLocation(const UObject* WorldContextObject,
	const FVector& InLocation, const float EdgePercent, FVector2D& OutScreenPosition, float& OutRotationAngleDegrees, bool& bIsOnScreen)
{
	bIsOnScreen = false;
	OutRotationAngleDegrees = 0.f;
	FVector2D ScreenPosition = FVector2D(0.f, 0.f);

	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D ViewportCenter = FVector2D(ViewportSize.X/2, ViewportSize.Y/2);

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	
	if (!World)
	{
		return;
	}
	
	const APlayerController* PlayerController = World->GetFirstPlayerController();;
	APawn* PlayerPawn = PlayerController->GetPawn();

	if (!PlayerPawn)
	{
		return;
	}
	
	const bool bProjectResult = PlayerController->ProjectWorldLocationToScreen(InLocation, ScreenPosition);
	if (bProjectResult)
	{
		// Check to see if it's on screen. If it is, ProjectWorldLocationToScreen is all we need, return it.
		if (ScreenPosition.X >= 0.f && ScreenPosition.X <= ViewportSize.X
			&& ScreenPosition.Y >= 0.f && ScreenPosition.Y <= ViewportSize.Y)
		{
			OutScreenPosition = ScreenPosition;
			bIsOnScreen = true;
			return;
		}
	}
	
	const FVector2D Dir = (FVector2D(InLocation) - FVector2D(PlayerPawn->GetActorLocation())).GetSafeNormal();
	
	const float AngleRadians = FMath::Atan2(Dir.Y, Dir.X) + FMath::DegreesToRadians(-PlayerController->PlayerCameraManager->GetCameraRotation().Yaw);

	const float Cos = cosf(AngleRadians);
	const float Sin = -sinf(AngleRadians);

	const float Cot = Cos / Sin;

	const FVector2D ScreenBounds = ViewportCenter * EdgePercent;
	
	if (Cos > 0)
	{
		ScreenPosition = FVector2D(-ScreenBounds.Y / Cot, -ScreenBounds.Y);
	}
	else
	{
		ScreenPosition = FVector2D(ScreenBounds.Y / Cot, ScreenBounds.Y);
	}

	if (ScreenPosition.X > ScreenBounds.X)
	{
		ScreenPosition = FVector2D(ScreenBounds.X, ScreenBounds.X * Cot);
	}
	else if (ScreenPosition.X < -ScreenBounds.X)
	{
		ScreenPosition = FVector2D(-ScreenBounds.X, -ScreenBounds.X * Cot);
	}

	OutRotationAngleDegrees = FMath::RadiansToDegrees(AngleRadians);
	OutScreenPosition = ScreenPosition + ViewportCenter;
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

FGameplayTag UCreatureOasisBlueprintLibrary::RequestGameplayTagFromName(const FName InTagName)
{
	return FGameplayTag::RequestGameplayTag(InTagName);
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
