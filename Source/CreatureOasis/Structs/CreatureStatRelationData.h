#pragma once

#include "AttributeSet.h"

#include "CreatureStatRelationData.Generated.h"

USTRUCT(BlueprintType)
struct FCreatureStatRelationData
{
	GENERATED_USTRUCT_BODY()
        
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatRelationData")
	FGameplayAttribute PointsAttribute;
            
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatRelationData")
	FGameplayAttribute LvlAttribute;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatRelationData")
	FGameplayAttribute LvlProgressAttribute;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatRelationData")
	FGameplayAttribute PrototypeAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatRelationData")
	FGameplayAttribute ProficiencyGrade;
};

USTRUCT(BlueprintType)
struct FCreatureStatProficiencyData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatProficiencyData")
	float MinPointsAwarded;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatProficiencyData")
	float MaxPointsAwarded;
};