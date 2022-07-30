#pragma once

#include "AttributeSet.h"

#include "CreatureStatEntryTableRow.Generated.h"

USTRUCT(BlueprintType)
struct FCreatureStatEntryTableRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatEntry")
    FText Name;
        
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatEntry")
    FGameplayAttribute PointsAttribute;
            
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatEntry")
    FGameplayAttribute LvlAttribute;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatEntry")
    FGameplayAttribute LvlProgressAttribute;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatEntry")
    FGameplayAttribute PrototypeAttribute; 
           
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StatEntry")
    bool bIsHidden;
};