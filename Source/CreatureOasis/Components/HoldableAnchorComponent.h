﻿#pragma once

#include "CoreMinimal.h"
#include "HoldableAnchorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartHold, AActor*, ActorBeingHeld);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndHold);

class UPrimitiveComponent;

/**
 * HoldableAnchorComponent is used to define a location where holdable objects should be anchored upon
 */
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CREATUREOASIS_API UHoldableAnchorComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UHoldableAnchorComponent();

	virtual void BeginPlay() override;
	
	/*
	 * Detects and return a holdable Actor, guaranteed to return an Actor that has the IHoldableInterface
	 * @return Returns a nullptr if no valid Actor with the IHoldableInterface is detected
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

	UPROPERTY(EditDefaultsOnly, Category = "HoldableTriggerVolume")
	FComponentReference ComponentReference;
	
protected:
	UPROPERTY()
	UPrimitiveComponent* PickupDetectionPrimitive;
	
	UPROPERTY()
	AActor* ActorWeAreHolding;
};
