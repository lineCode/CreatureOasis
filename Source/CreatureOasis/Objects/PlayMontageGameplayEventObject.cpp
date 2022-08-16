#include "PlayMontageGameplayEventObject.h"

#include "BehaviorTree/BTTaskNode.h"

UPlayMontageGameplayEventObject::UPlayMontageGameplayEventObject()
{
}

void UPlayMontageGameplayEventObject::InitializeWithData(UAnimMontage* InMontageToPlay, TArray<FName> InSectionNames,
	float InMinTime, float InMaxTime, bool InbFinishAfterMontageCompleted, float InOverwritePlayRate, UBehaviorTreeComponent* InCompThatCalledThis, UBTTaskNode* InTaskNode)
{
	MontageToPlay = InMontageToPlay;
	SectionNames = InSectionNames;
	MinTime = InMinTime;
	MaxTime = InMaxTime;
	CompThatCalledThis = InCompThatCalledThis;
	TaskNode = InTaskNode;
	bFinishAfterMontageCompleted = InbFinishAfterMontageCompleted;
	OverwritePlayRate = InOverwritePlayRate;
}

void UPlayMontageGameplayEventObject::FinishLatentTaskUsingTaskNode() const
{
	TaskNode->FinishLatentTask(*CompThatCalledThis, EBTNodeResult::Succeeded);
}
