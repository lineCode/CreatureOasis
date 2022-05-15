#pragma once

#include "CoreMinimal.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"

#include "CreatureOasis/Components/CreatureExpressionComponent.h"
#include "CreatureOasis/Components/CreatureAppearanceComponent.h"
#include "CreatureOasis/Interfaces/HoldableInterface.h"

#include "CreatureCharacter.generated.h"

UCLASS()
class CREATUREOASIS_API ACreatureCharacter : public AGASCharacter, public IHoldableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreatureCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// From IHoldableInterface
	virtual bool StartHold_Implementation(AActor* InstigatorActor) override;
	virtual bool EndHold_Implementation() override;
	// End
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* PickUpBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* PickUpAnchor;

	UPROPERTY(BlueprintReadOnly)
	UCreatureAppearanceComponent* AppearanceComponent;
	
	UPROPERTY(BlueprintReadOnly)
	UCreatureExpressionComponent* ExpressionComponent;
};
