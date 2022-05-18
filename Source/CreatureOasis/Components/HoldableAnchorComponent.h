#pragma once

#include "CoreMinimal.h"
#include "HoldableAnchorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartHold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndHold);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CREATUREOASIS_API UHoldableAnchorComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UHoldableAnchorComponent();

	void AttachHoldable(AActor* HoldableActor);
	void DetachHoldable();
	
	UPROPERTY(BlueprintAssignable, Category = "Holdable")
	FOnStartHold OnStartHoldDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Holdable")
	FOnEndHold OnEndHoldDelegate;

	UFUNCTION(BlueprintCallable)
	AActor* GetActorWeAreHolding() const;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Sockets")
	FName SocketNameToAttachTo;
	
protected:
	UPROPERTY()
	AActor* ActorWeAreHolding;
};
