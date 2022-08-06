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

	float MinDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;
	if (!OverlappingActors.IsEmpty())
	{
		for	(AActor* Actor : OverlappingActors)
		{
			if (IsValid(Actor)
				&& Actor != GetOwner()
				&& Actor->GetClass()->ImplementsInterface(UHoldableInterface::StaticClass()))
			{
				const float Distance = FVector::Distance(Actor->GetActorLocation(), GetOwner()->GetActorLocation());
				if (Distance < MinDistance)
				{
					MinDistance = Distance;
					ClosestActor = Actor;
				}
			}
		}
	}
	
	return ClosestActor;
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

bool UHoldableAnchorComponent::IsHoldingActor() const
{
	return ActorWeAreHolding != nullptr;
}

