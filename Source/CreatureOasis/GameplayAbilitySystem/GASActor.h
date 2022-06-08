#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GASActor.generated.h"

class UBaseAttributeSet;

/** 
 * GASActor is the base class of all actors that should make use of the Gameplay Ability System (GAS)
 */
UCLASS(BlueprintType, Blueprintable)
class AGASActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actors properties
	AGASActor();

	virtual void PostInitializeComponents() override;
	
	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// End

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UBaseAttributeSet* AttributeSetBase;
};