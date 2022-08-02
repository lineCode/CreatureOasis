#include "HoldableAnchorComponent.h"

#include "Components/ShapeComponent.h"
#include "CreatureOasis/Interfaces/HoldableInterface.h"

UHoldableAnchorComponent::UHoldableAnchorComponent()
	: SocketNameToAttachTo(NAME_None)
	, PickupDetectionPrimitive(nullptr)
	, ActorWeAreHolding(nullptr)
{
	ComponentReference.ComponentProperty = "HoldableDetectionSphere";
	
	PrimaryComponentTick.bCanEverTick = false;
	bEditableWhenInherited = true;
}

void UHoldableAnchorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PickupDetectionPrimitive = Cast<UPrimitiveComponent>(ComponentReference.GetComponent(GetOwner()));
}

AActor* UHoldableAnchorComponent::DetectHoldableActor() const
{
	if (!IsValid(PickupDetectionPrimitive))
	{
		return nullptr;
	}
	
	TArray<AActor*> OverlappingActors;
	PickupDetectionPrimitive->GetOverlappingActors(OverlappingActors);
	
	if (!OverlappingActors.IsEmpty())
	{
		AActor* CandidateActor = OverlappingActors[0];
		if (IsValid(CandidateActor) &&
			CandidateActor->GetClass()->ImplementsInterface(UHoldableInterface::StaticClass()))
		{
			return CandidateActor;
		}
	}
	
	return nullptr;
}

void UHoldableAnchorComponent::AttachHoldable(AActor* HoldableActor)
{
	ActorWeAreHolding = HoldableActor;
	
	HoldableActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketNameToAttachTo);

	OnStartHoldDelegate.Broadcast(HoldableActor);
}

void UHoldableAnchorComponent::DetachHoldable()
{
	if (ActorWeAreHolding != nullptr)
	{
		ActorWeAreHolding->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		ActorWeAreHolding = nullptr;
	}
	
	OnEndHoldDelegate.Broadcast();
}

AActor* UHoldableAnchorComponent::GetActorWeAreHolding() const
{
	return ActorWeAreHolding;
}

