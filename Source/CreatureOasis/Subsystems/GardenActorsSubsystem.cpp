// Fill out your copyright notice in the Description page of Project Settings.


#include "GardenActorsSubsystem.h"

#include "AIController.h"

void UGardenActorsSubsystem::AddGardenActor(FGameplayTag GardenActorTypeTag, AActor* GardenActor)
{
	GardenActorsMultiMap.Add(GardenActorTypeTag, GardenActor);
}

void UGardenActorsSubsystem::RemoveGardenActor(const FGameplayTag GardenActorTypeTag, AActor* GardenActor)
{
	GardenActorsMultiMap.RemoveSingle(GardenActorTypeTag, GardenActor);
}

int UGardenActorsSubsystem::GetGardenActorCountByTag(FGameplayTag GameplayTag) const
{
	if (GardenActorsMultiMap.IsEmpty())
	{
		return 0;
	}
	
	TArray<AActor*> FoundActors;
	GardenActorsMultiMap.MultiFind(GameplayTag, FoundActors);
	return FoundActors.Num();
}

bool UGardenActorsSubsystem::GetGardenActorsByTag(FGameplayTag GameplayTag, TArray<AActor*>& OutGardenActors)
{
	if (GardenActorsMultiMap.IsEmpty())
	{
		return false;
	}

	OutGardenActors.Empty();
	
	GardenActorsMultiMap.MultiFind(GameplayTag, OutGardenActors);
	
	return !OutGardenActors.IsEmpty();
}

bool UGardenActorsSubsystem::GetAllGardenActors(TArray<AActor*>& OutGardenActors)
{
	if (GardenActorsMultiMap.IsEmpty())
	{
		return false;	
	}
	
	GardenActorsMultiMap.GenerateValueArray(OutGardenActors);
	
	return true;
}

void UGardenActorsSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

AActor* UGardenActorsSubsystem::GetClosestGardenActorInRange(FVector Start,
	const float Range, FGameplayTag GardenActorTag)
{
	TArray<AActor*> GardenActors;
	GetGardenActorsByTag(GardenActorTag, GardenActors);

	TPair<float, AActor*> ClosestActor(TNumericLimits<float>::Max(), nullptr);
	for (AActor* Actor : GardenActors)
	{
		const float Distance = FVector::Distance(Start, Actor->GetActorLocation());
		if (Distance < Range && Distance < ClosestActor.Key)
		{
			ClosestActor.Key = Distance;
			ClosestActor.Value = Actor;
		}
	}

	return ClosestActor.Value;
}

bool UGardenActorsSubsystem::GetGardenActorsInRange(FVector Start,
															const float Range, FGameplayTag GardenActorTag, TArray<AActor*>& OutGardenActors)
{
	TArray<AActor*> GardenActors;
	GetGardenActorsByTag(GardenActorTag, GardenActors);
	for (AActor* Actor : GardenActors)
	{
		const float Distance = FVector::Distance(Start, Actor->GetActorLocation());
		if (Distance < Range)
		{
			OutGardenActors.Add(Actor);
		}
	}

	return !OutGardenActors.IsEmpty();
}

AActor* UGardenActorsSubsystem::GetClosestGardenActorInViewCone(FVector Start, FVector Direction, float ConeAngle,
	const float Range, FGameplayTag GardenActorTag)
{
	TArray<AActor*> GardenActors;
	GetGardenActorsByTag(GardenActorTag, GardenActors);
	
	TPair<float, AActor*> ClosestActor(TNumericLimits<float>::Max(), nullptr);
	for (AActor* Actor : GardenActors)
	{
		const FVector DirToStart = (Actor->GetActorLocation() - Start).GetSafeNormal();

		const float Distance = FVector::Distance(Start, Actor->GetActorLocation());
		const float DotResult = Direction.Dot(DirToStart);
		if (Distance < Range && DotResult > ConeAngle && Distance < ClosestActor.Key)
		{
			ClosestActor.Key = Distance;
			ClosestActor.Value = Actor;
		}
	}

	return ClosestActor.Value;
}

AActor* UGardenActorsSubsystem::GetClosestGardenActorInViewConeUsingActor(const AActor* OriginActor, float ConeAngle,
	const float Range, FGameplayTag GardenActorTag)
{
	return GetClosestGardenActorInViewCone(OriginActor->GetActorLocation(), OriginActor->GetActorForwardVector(), ConeAngle,
	Range, GardenActorTag);
}

bool UGardenActorsSubsystem::HasGardenActorInViewCone(FVector Start, FVector Direction, float ConeAngle,
	const float Range, FGameplayTag GardenActorTag)
{
	TArray<AActor*> GardenActors;
	GetGardenActorsByTag(GardenActorTag, GardenActors);
	
	//DrawDebugSphere(GetWorld(), Start, Range, 12, FColor::Yellow, false, 10.f, 0, 6.f);

	for (const AActor* Actor : GardenActors)
	{
		const FVector DirToStart = (Actor->GetActorLocation() -Start).GetSafeNormal();

		const float Distance = FVector::Distance(Start, Actor->GetActorLocation());
		const float DotResult = Direction.Dot(DirToStart);
		if (Distance < Range && DotResult > ConeAngle)
		{
			//DrawDebugLine(GetWorld(), Start, Start + DirToStart * Distance, FColor::Green, false, 10.f, 0, 2.f);

			return true;
		}
		// else if (Distance > Range && DotResult > ConeAngle)
		// {
		// 	DrawDebugLine(GetWorld(), Start, Start + DirToStart * Distance, FColor::Red, false, 10.f, 0, 2.f);
		// }
		// else
		// {
		// 	DrawDebugLine(GetWorld(), Start, Start + DirToStart * Distance, FColor::Blue, false, 10.f, 0, 1.f);
		// }
	}
	
	return false;
}

bool UGardenActorsSubsystem::HasGardenActorInViewConeUsingActor(const AActor* OriginActor, const float ConeAngle,
	const float Range, const FGameplayTag GardenActorTag)
{
	return HasGardenActorInViewCone(OriginActor->GetActorLocation(), OriginActor->GetActorForwardVector(), ConeAngle, Range, GardenActorTag);
}

bool UGardenActorsSubsystem::IsAnyGardenActorOfTypeInRange(FVector Start,
                                                           const float Range, FGameplayTag GardenActorTypeTag)
{
	TArray<AActor*> GardenActors;
	if (GetGardenActorsByTag(GardenActorTypeTag, GardenActors))
	{
		for (const AActor* Actor : GardenActors)
		{
			const float Distance = FVector::Distance(Start, Actor->GetActorLocation());
			if (Distance < Range)
			{
				return true;
			}
		}
	}

	return false;
}

bool UGardenActorsSubsystem::HasGardenActorFromInActorArray(FGameplayTag GardenActorTypeTag, TArray<AActor*> InActorArray)
{
	TArray<AActor*> GardenActors;
	if (GetGardenActorsByTag(GardenActorTypeTag, GardenActors))
	{
		for (const AActor* InActor : InActorArray)
		{
			for (const AActor* GardenActor : GardenActors)
			{
				if (InActor == GardenActor)
				{
					return true;
				}
			}
		}
	}

	return false;
}

AActor* UGardenActorsSubsystem::GetClosestGardenActorFromInActorArray(const FVector Start, FGameplayTag GardenActorTypeTag, const TArray<AActor*> InActorArray)
{
	TArray<AActor*> GardenActors;
	if (GetGardenActorsByTag(GardenActorTypeTag, GardenActors))
	{
		TPair<float, AActor*> ClosestActor(TNumericLimits<float>::Max(), nullptr);
		for (const AActor* InActor : InActorArray)
		{
			for (AActor* GardenActor : GardenActors)
			{
				if (InActor == GardenActor)
				{
					const float Distance = FVector::Distance(Start, GardenActor->GetActorLocation());
					if (Distance < ClosestActor.Key)
					{
						ClosestActor.Key = Distance;
						ClosestActor.Value = GardenActor;
					}
				}
			}
		}
		
		return ClosestActor.Value;
	}

	return nullptr;
}