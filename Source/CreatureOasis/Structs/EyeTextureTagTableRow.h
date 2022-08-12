#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"

#include "EyeTextureTagTableRow.generated.h"

USTRUCT(BlueprintType)
struct FEyeTextureTagTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EyeRowBase")
	FGameplayTag EyeGameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EyeRowBase")
	UTexture* EyeTexture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EyeRowBase", meta=(ClampMin=0.f, ClampMax=1.f))
	float EyeLidCloseScale = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EyeRowBase", meta=(ClampMin=0.f, ClampMax=1.f))
	float EyeLidSlantedScale = 0.f;
};
