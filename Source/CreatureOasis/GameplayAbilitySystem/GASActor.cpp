#include "GASActor.h"

#include "AttributeSets/BaseAttributeSet.h"
#include "BaseAbilitySystemComponent.h"

AGASActor::AGASActor()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
}

void AGASActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddSet<UBaseAttributeSet>();
	}
}

UAbilitySystemComponent* AGASActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
