#include "HoldableAnchorComponent.h"

#include "CreatureOasis/Interfaces/HoldableInterface.h"

UHoldableAnchorComponent::UHoldableAnchorComponent()
	: SocketNameToAttachTo(NAME_None)
	, PickUpSphereRadius(50.f)
	, ActorWeAreHolding(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
	bEditableWhenInherited = true;
}

AActor* UHoldableAnchorComponent::DetectHoldableActor() const
{
	AActor* Owner = GetOwner();

	FHitResult OutHit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	
	const FVector PickUpLoc = Owner->GetActorLocation()
		+ FVector(0.f, 0.f, -17.5f)
		+ (Owner->GetActorForwardVector() * 32.5f);

	DrawDebugSphere(GetWorld(), PickUpLoc, PickUpSphereRadius, 12, FColor(0, 0, 0, 255), false, 2.f);
	
	if (GetWorld()->SweepSingleByChannel(OutHit, PickUpLoc, PickUpLoc,
		FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(PickUpSphereRadius), QueryParams))
	{
		AActor* CandidateActor = OutHit.GetActor();
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

	OnStartHoldDelegate.Broadcast();
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

