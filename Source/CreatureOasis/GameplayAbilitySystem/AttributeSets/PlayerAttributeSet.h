#pragma once

#include "BaseAttributeSet.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UPlayerAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Rings;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Rings);
};
