#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"

#include "MouthTextureTagTableRow.generated.h"

USTRUCT(BlueprintType)
struct FMouthTextureTagTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FaceRowBase")
	FGameplayTag MouthGameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FaceRowBase")
	UTexture* MouthTexture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FaceRowBase")
	UTexture* SideMouthTexture = nullptr;
};
