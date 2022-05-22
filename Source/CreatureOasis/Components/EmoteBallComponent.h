#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EmoteBallComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CREATUREOASIS_API UEmoteBallComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEmoteBallComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void SetEmoteBallMeshComp(UStaticMeshComponent* MeshComp);
	
protected:
	virtual void BeginPlay() override;
	
	virtual void OnComponentCreated() override;

	void SetEmoteBallLoc(const float DeltaTime = 0.f) const;
	
	UPROPERTY()
	UStaticMeshComponent* EmoteBallMeshComponent;
	
	UPROPERTY()
	USkeletalMeshComponent* OwnerMeshComponent;
	
	UPROPERTY()
	FName SocketNameToAttachTo;

	UPROPERTY(EditAnywhere)
	float InterpSpeed;
};
