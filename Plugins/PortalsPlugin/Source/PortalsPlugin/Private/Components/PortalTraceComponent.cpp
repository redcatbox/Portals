// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PortalTraceComponent.h"
#include "Actors/PortalActor.h"
#include "Objects/PortalFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#if ENABLE_DRAW_DEBUG
#include "DrawDebugHelpers.h"
#endif

void UPortalTraceComponent::TraceRicochets(FVector& TraceStart, FVector& TraceDirection, float MaxTraceDistance, int32 MaxNumRicochets, bool bDrawDebugHelpers)
{
	if (MaxNumRicochets > -1)
	{
		FVector Start = TraceStart;
		FVector Direction = TraceDirection;
		float Distance = MaxTraceDistance;
		FVector End = Start + Direction * Distance;
		int32 NumRicochets = MaxNumRicochets;
		if (MaxNumRicochets > 1)
		{
			NumRicochets = FMath::RandRange(1, MaxNumRicochets);
		}

		bool bHit;
		FHitResult OutHit;

		if (bDrawDebugHelpers)
		{
			TArray<AActor*> ActorsToIgnore;
			bHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true, FLinearColor::Red, FLinearColor::Green, 5.f);
		}
		else
		{
			FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(PortalTrace), true, GetOwner());
			TraceParams.bReturnPhysicalMaterial = true;
			bHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, TraceParams);
		}

		if (bHit)
		{
			Distance -= OutHit.Distance;
			Direction = FMath::GetReflectionVector(Direction, OutHit.ImpactNormal);
			Start = OutHit.ImpactPoint + Direction;
			NumRicochets--;

#if ENABLE_DRAW_DEBUG
			if (bDrawDebugHelpers)
			{
				const FVector AxisY = FVector::CrossProduct(-TraceDirection, OutHit.ImpactNormal);
				const FVector AxisX = FVector::CrossProduct(AxisY, OutHit.ImpactNormal);
				const FRotator DebugRot = FRotationMatrix::MakeFromXZ(AxisX, OutHit.ImpactNormal).Rotator();
				DrawDebugCoordinateSystem(GetWorld(), Start, DebugRot, 100.f, false, 5.f, 0, 2.f);
			}
#endif

			TraceRicochets(Start, Direction, Distance, NumRicochets, bDrawDebugHelpers);
		}
	}
}

void UPortalTraceComponent::PortalRecursivelyTraceRicochets(const APortalActor* PortalActor, const FVector& TraceStart, const FVector& TraceDirection, const float MaxTraceDistance, const int32 MaxNumRicochets, const bool bDrawDebugHelpers)
{
	FVector Start, Direction, End;
	float Distance = MaxTraceDistance;
	int32 NumRicochets = MaxNumRicochets;
	if (MaxNumRicochets > 1)
	{
		NumRicochets = FMath::RandRange(1, MaxNumRicochets);
	}

	bool bShouldTraceAgain = false;

	if (PortalActor && PortalActor->TargetPortal)
	{
		UPortalFunctionLibrary::PortalConvertLocation(PortalActor, PortalActor->TargetPortal, TraceStart, Start);
		UPortalFunctionLibrary::PortalConvertDirection(PortalActor, PortalActor->TargetPortal, TraceDirection, Direction);
		Start += Direction;
		End = Start + Direction * Distance;

		bShouldTraceAgain = true;
	}
	else if (MaxNumRicochets > -1)
	{
		Start = TraceStart;
		Direction = TraceDirection;
		End = Start + Direction * Distance;

		bShouldTraceAgain = true;
	}

	if (bShouldTraceAgain)
	{
		bool bHit;
		FHitResult OutHit;

		if (bDrawDebugHelpers)
		{
			TArray<AActor*> ActorsToIgnore;
			bHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true, FLinearColor::Red, FLinearColor::Green, 5.f);
		}
		else
		{
			FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(PortalTrace), true, GetOwner());
			TraceParams.bReturnPhysicalMaterial = true;
			bHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, TraceParams);
		}

		if (bHit)
		{
#if ENABLE_DRAW_DEBUG
			if (bDrawDebugHelpers)
			{
				const FVector AxisY = FVector::CrossProduct(-TraceDirection, OutHit.ImpactNormal);
				const FVector AxisX = FVector::CrossProduct(AxisY, OutHit.ImpactNormal);
				const FRotator DebugRot = FRotationMatrix::MakeFromXZ(AxisX, OutHit.ImpactNormal).Rotator();
				DrawDebugCoordinateSystem(GetWorld(), OutHit.ImpactPoint, DebugRot, 100.f, false, 5.f, 0, 2.f);
			}
#endif

			Distance -= OutHit.Distance;

			APortalActor* Portal = Cast<APortalActor>(OutHit.GetActor());
			if (Portal)
			{
				Start = OutHit.ImpactPoint;
			}
			else
			{
				NumRicochets--;

				Direction = FMath::GetReflectionVector(Direction, OutHit.ImpactNormal);
				Start = OutHit.ImpactPoint + Direction;
			}

			PortalRecursivelyTraceRicochets(Portal, Start, Direction, Distance, NumRicochets, bDrawDebugHelpers);
		}
	}
}
