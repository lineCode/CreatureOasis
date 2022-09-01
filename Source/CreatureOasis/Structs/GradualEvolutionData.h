#pragma once
#include "AttributeSet.h"

#include "GradualEvolutionData.Generated.h"

USTRUCT(BlueprintType)
struct FGradualEvolutionTextureData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ParameterName = TEXT("");
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture* Texture = nullptr;
};

USTRUCT(BlueprintType)
struct FGradualEvolutionBoneData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName BoneName = TEXT("");
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector BoneOffset = FVector(0.f);
};

USTRUCT(BlueprintType)
struct FGradualEvolutionDataSingleEntry
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName MorphTarget = TEXT("");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGradualEvolutionTextureData> GradualEvolutionTextureArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bOverrideColor = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="bOverrideColor"))
	FLinearColor PrimaryColor = FLinearColor(0.f, 0.f, 0.f, 1.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="bOverrideColor"))
	FLinearColor SecondaryColor = FLinearColor(0.f, 0.f, 0.f, 1.f);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGradualEvolutionBoneData> BoneDataArray;
};

USTRUCT(BlueprintType)
struct FGradualEvolutionDataEntry
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGradualEvolutionDataSingleEntry Left;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGradualEvolutionDataSingleEntry Right;
};

USTRUCT(BlueprintType)
struct FGradualEvolutionData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayAttribute, FGradualEvolutionDataEntry> GradualEvolutionDataEntries;
};

