#pragma once

#include "CoreMinimal.h"
#include "HoldableAnchorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartHold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndHold);

/**
 * HoldableAnchorComponent is used to define a location where holdable objects should be anchored upon
 */
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CREATUREOASIS_API UHoldableAnchorComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UHoldableAnchorComponent();

	/*
	 * Detects and return a holdable Actor
	 * @return HoldableActor if any detected, guaranteed to return an Actor that has the IHoldableInterface
	 */
	AActor* DetectHoldableActor() const;

	void AttachHoldable(AActor* HoldableActor);
	void DetachHoldable();

	UFUNCTION(BlueprintCallable)
	AActor* GetActorWeAreHolding() const;
	
	UPROPERTY(BlueprintAssignable, Category = "Holdable")
	FOnStartHold OnStartHoldDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Holdable")
	FOnEndHold OnEndHoldDelegate;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Sockets")
	FName SocketNameToAttachTo;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "HoldableTriggerVolume")
	float PickUpSphereRadius;
	
protected:
	UPROPERTY()
	AActor* ActorWeAreHolding;
};
