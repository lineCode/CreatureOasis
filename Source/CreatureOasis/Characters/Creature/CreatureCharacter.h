#pragma once

#include "CoreMinimal.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"

#include "CreatureOasis/Interfaces/HoldableInterface.h"

#include "CreatureCharacter.generated.h"

class ACreatureAIController;

UCLASS()
class CREATUREOASIS_API ACreatureCharacter : public AGASCharacter, public IHoldableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreatureCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	
	// IHoldableInterface
	virtual void StartBeingHold_Implementation(AGASCharacter* InstigatorCharacter) override;
	virtual void EndBeingHold_Implementation() override;
	virtual AGASCharacter* GetCharacterCurrentlyHoldingUs_Implementation() override;
	// End

private:
	UPROPERTY()
	ACreatureAIController* CreatureAIController;

	UPROPERTY()
	AGASCharacter* CharacterCurrentlyHoldingUs;
};
