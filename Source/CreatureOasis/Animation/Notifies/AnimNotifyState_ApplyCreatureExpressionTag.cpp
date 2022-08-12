// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_ApplyCreatureExpressionTag.h"

#include "CreatureOasis/Interfaces/CreatureComponentGetterInterface.h"

void UAnimNotifyState_ApplyCreatureExpressionTag::NotifyBegin(USkeletalMeshComponent* MeshComp,
                                                              UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	AActor* OwnerActor = MeshComp->GetOwner();
	if (IsValid(OwnerActor) && OwnerActor->GetClass()->ImplementsInterface(UCreatureComponentGetterInterface::StaticClass()))
	{
		if (UCreatureExpressionComponent* CreatureExpressionComp = ICreatureComponentGetterInterface::Execute_GetCreatureExpressionComponent(OwnerActor))
		{
			if (EyeTag.IsValid())
			{
				CreatureExpressionComp->SetEyeTag(EyeTag);
			}

			if (MouthTag.IsValid())
			{
				CreatureExpressionComp->SetMouthTag(MouthTag);
			}
		}
	}
}

void UAnimNotifyState_ApplyCreatureExpressionTag::NotifyEnd(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AActor* OwnerActor = MeshComp->GetOwner();
	if (IsValid(OwnerActor) && OwnerActor->GetClass()->ImplementsInterface(UCreatureComponentGetterInterface::StaticClass()))
	{
		if (UCreatureExpressionComponent* CreatureExpressionComp = ICreatureComponentGetterInterface::Execute_GetCreatureExpressionComponent(OwnerActor); IsValid(CreatureExpressionComp))
		{
			// Clear only eye/mouth tags that are still the same, the active eye/mouth tag could have changed since last time we set it
			// We dont want to do anything in that case
			if (CreatureExpressionComp->GetActiveEyeTag() == EyeTag)
			{
				CreatureExpressionComp->ClearEyeTag();
			}

			if (CreatureExpressionComp->GetActiveMouthTag() == MouthTag)
			{
				CreatureExpressionComp->ClearMouthTag();
			}
		}
	}
}
