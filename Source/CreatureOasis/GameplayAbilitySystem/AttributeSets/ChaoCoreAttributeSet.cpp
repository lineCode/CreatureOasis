#include "ChaoCoreAttributeSet.h"

#include "GameplayEffectExtension.h"

void UChaoCoreAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	NewValue = FMath::Clamp(NewValue, MinValue, MaxValue);
}

void UChaoCoreAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute.GetAttributeSetClass() == UChaoCoreAttributeSet::StaticClass())
	{
		float NewValue = FMath::Clamp(Data.EvaluatedData.Attribute.GetNumericValueChecked(this), MinValue, MaxValue);
		Data.EvaluatedData.Attribute.SetNumericValueChecked(
			NewValue, this);
	}
}

void UChaoCoreAttributeSet::InitFromMetaDataTable(const UDataTable* DataTable)
{
	Super::InitFromMetaDataTable(DataTable);
}
