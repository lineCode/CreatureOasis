#include "HoldableAnchorComponent.h"

UHoldableAnchorComponent::UHoldableAnchorComponent() :
	SocketNameToAttachTo(NAME_None), ActorWeAreHolding(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UHoldableAnchorComponent::AttachHoldable(AActor* HoldableActor)
{
	OnStartHoldDelegate.Broadcast();
	
	ActorWeAreHolding = HoldableActor;
	
	HoldableActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketNameToAttachTo);
	return true;
}

bool UHoldableAnchorComponent::DetachHoldable()
{
	OnEndHoldDelegate.Broadcast();
	
	if (ActorWeAreHolding != nullptr)
	{
		ActorWeAreHolding->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		ActorWeAreHolding = nullptr;
	}
	return true;
}

AActor* UHoldableAnchorComponent::GetActorWeAreHolding() const
{
	return ActorWeAreHolding;
}

