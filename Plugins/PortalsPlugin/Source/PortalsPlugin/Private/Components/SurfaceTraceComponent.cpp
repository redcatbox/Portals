// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SurfaceTraceComponent.h"

USurfaceTraceComponent::USurfaceTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USurfaceTraceComponent::TraceLoop(FVector TraceStart, FVector TraceDirection, float MaxTraceDistance, int32 MaxNumRicochets)
{
	FVector Start = TraceStart;
	FVector Direction = TraceDirection.GetSafeNormal();
	float Distance = MaxTraceDistance;
	FVector End = Start + Direction * Distance;

	for (int32 i = 0; i < MaxNumRicochets; ++i)
	{
		FHitResult OutHit;
		TArray<AActor*> ActorsToIgnore;

		const bool bHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true, FLinearColor::Red, FLinearColor::Green, 1.f);

		if (bHit)
		{
			Distance -= (Start - OutHit.ImpactPoint).Size();
			Start = OutHit.ImpactPoint;
			Direction = OutHit.ImpactNormal;
			End = Start + Direction * Distance;
		}
		else
		{
			break;
		}
	}
}

void USurfaceTraceComponent::TracePortal(FVector TraceStart, FVector TraceDirection, float MaxTraceDistance)
{
	FVector Start = TraceStart;
	FVector Direction = TraceDirection.GetSafeNormal();
	float Distance = MaxTraceDistance;
	FVector End = Start + Direction * Distance;


}

void USurfaceTraceComponent::TracePortalRecursive(APortalActor* PortalActor, FVector TraceDirection, float MaxTraceDistance, FVector ImpactPoint)
{
	APortalActor* NewPortalActor = nullptr;
	FVector NewTraceDirection;
	FVector NewImpactPoint;

	FVector Start = NewImpactPoint;
	FVector Direction = TraceDirection.GetSafeNormal();
	float Distance = MaxTraceDistance;
	FVector End = Start + Direction * Distance;

	FHitResult OutHit;
	TArray<AActor*> ActorsToIgnore;
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true, FLinearColor::Red, FLinearColor::Green, 1.f);
	if (bHit)
	{
		TracePortalRecursive(NewPortalActor, NewTraceDirection, Distance, NewImpactPoint);
	}
}
