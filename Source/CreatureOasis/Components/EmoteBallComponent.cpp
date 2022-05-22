#include "EmoteBallComponent.h"

#include "GameFramework/Character.h"

UEmoteBallComponent::UEmoteBallComponent() :
	EmoteBallMeshComponent(nullptr)
	, OwnerMeshComponent(nullptr)
	, SocketNameToAttachTo(TEXT("EmoteBall"))
	, InterpSpeed(10.f)
{
	PrimaryComponentTick.bCanEverTick = true;

	if (IsValid(GetOwner()))
	{
		OwnerMeshComponent = Cast<ACharacter>(GetOwner())->GetMesh();
	}
}

void UEmoteBallComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UEmoteBallComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	SetEmoteBallLoc();
}

void UEmoteBallComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetEmoteBallLoc(DeltaTime);
}

void UEmoteBallComponent::SetEmoteBallMeshComp(UStaticMeshComponent* MeshComp)
{
	EmoteBallMeshComponent = MeshComp;
}

void UEmoteBallComponent::SetEmoteBallLoc(const float DeltaTime) const
{
	if (IsValid(EmoteBallMeshComponent))
	{
		const FVector TargetLoc = FMath::VInterpTo(EmoteBallMeshComponent->GetComponentLocation(), OwnerMeshComponent->GetSocketLocation(SocketNameToAttachTo), DeltaTime, InterpSpeed);
		EmoteBallMeshComponent->SetWorldLocation(TargetLoc);
	}
}

