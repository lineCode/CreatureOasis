#include "HoldableAnchorComponent.h"

UHoldableAnchorComponent::UHoldableAnchorComponent() :
	SocketNameToAttachTo(NAME_None), ActorWeAreHolding(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHoldableAnchorComponent::AttachHoldable(AActor* HoldableActor)
{
	OnStartHoldDelegate.Broadcast();
	
	ActorWeAreHolding = HoldableActor;
	
	HoldableActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketNameToAttachTo);
}

void UHoldableAnchorComponent::DetachHoldable()
{
	OnEndHoldDelegate.Broadcast();
	
	if (ActorWeAreHolding != nullptr)
	{
		ActorWeAreHolding->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		ActorWeAreHolding = nullptr;
	}
}

AActor* UHoldableAnchorComponent::GetActorWeAreHolding() const
{
	return ActorWeAreHolding;
}

