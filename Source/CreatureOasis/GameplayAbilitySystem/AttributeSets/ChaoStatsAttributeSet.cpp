#include "ChaoStatsAttributeSet.h"

#include "CreatureOasis/Structs/ProjectSettings/CreatureStatSettings.h"

void UChaoStatsAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	const UCreatureStatSettings* StatSettings = GetDefault<UCreatureStatSettings>();

	if (StatSettings->StatRelationDataMap.Contains(Attribute))
	{
		const FCreatureStatRelationData* StatRelationData = StatSettings->StatRelationDataMap.Find(Attribute);
		if (NewValue >= 100.f)	
		{
			const float CurrentLevel = StatRelationData->LvlAttribute.GetNumericValue(this);
			if (CurrentLevel >= 99)
			{
				NewValue = 0.f;
				return;
			}
			
			float LvlProgressRemainder = FMath::Fmod(NewValue, 100.f);
			StatRelationData->LvlProgressAttribute.SetNumericValueChecked(LvlProgressRemainder, this);

			float NewLevel = StatRelationData->LvlAttribute.GetNumericValue(this) + 1;
			StatRelationData->LvlAttribute.SetNumericValueChecked(NewLevel, this);

			const ECreatureStatProficiencyGrade ProficiencyGrade = static_cast<ECreatureStatProficiencyGrade>(FMath::RoundToInt32(StatRelationData->ProficiencyGrade.GetNumericValue(this)));
			const FCreatureStatProficiencyData* ProficiencyData = StatSettings->StatProficiencyGradeDataMap.Find(ProficiencyGrade);
			
			const float PointsToAdd = FMath::FRandRange(ProficiencyData->MinPointsAwarded, ProficiencyData->MaxPointsAwarded);
			float NewPoints = StatRelationData->PointsAttribute.GetNumericValue(this) + PointsToAdd;
			StatRelationData->PointsAttribute.SetNumericValueChecked(NewPoints, this);
		}
	}
}

void UChaoStatsAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	
}
