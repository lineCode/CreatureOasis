﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ApplyCreatureExpressionTag.h"

#include "CreatureOasis/Interfaces/CreatureComponentGetterInterface.h"

void UAnimNotify_ApplyCreatureExpressionTag::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                    const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

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