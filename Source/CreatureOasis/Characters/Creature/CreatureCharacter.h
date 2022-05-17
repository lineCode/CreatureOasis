#pragma once

#include "CoreMinimal.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"

#include "CreatureOasis/Components/CreatureExpressionComponent.h"
#include "CreatureOasis/Components/CreatureAppearanceComponent.h"
#include "CreatureOasis/Components/HoldableAnchorComponent.h"
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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	
	// IHoldableInterface
	virtual void StartBeingHold_Implementation(AActor* InstigatorActor) override;
	virtual void EndBeingHold_Implementation() override;
	// End

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHoldableAnchorComponent* HoldableAnchor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCreatureAppearanceComponent* AppearanceComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCreatureExpressionComponent* ExpressionComponent;

	UPROPERTY()
	ACreatureAIController* CreatureAIController;
};
