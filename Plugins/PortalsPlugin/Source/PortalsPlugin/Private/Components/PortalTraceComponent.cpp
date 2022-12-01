// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PortalTraceComponent.h"
#include "Actors/PortalActor.h"
#include "Objects/PortalFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#if ENABLE_DRAW_DEBUG
#include "DrawDebugHelpers.h"
#endif

void UPortalTraceComponent::TraceRicochets(FVector TraceStart, FVector TraceDirection, float MaxTraceDistance, int32 MaxNumRicochets, bool bDrawDebugHelpers)
{
	if (MaxNumRicochets > -1)
	{
		FVector Start = TraceStart;
		FVector Direction = TraceDirection.GetSafeNormal();
		float Distance = MaxTraceDistance;
		FVector End = Start + Direction * Distance;
		int32 NumRicochets = MaxNumRicochets;

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

void UPortalTraceComponent::PortalRecursivelyTraceRicochets(APortalActor* PortalActor, FVector TraceStart, FVector TraceDirection, float MaxTraceDistance, int32 MaxNumRicochets, bool bDrawDebugHelpers)
{
	if (PortalActor && PortalActor->TargetPortal)
	{
		FVector Start = UPortalFunctionLibrary::PortalConvertLocation(PortalActor, PortalActor->TargetPortal, TraceStart);
		FVector Direction = UPortalFunctionLibrary::PortalConvertDirection(PortalActor, PortalActor->TargetPortal, TraceDirection.GetSafeNormal());
		//Start += Direction;
		float Distance = MaxTraceDistance;
		FVector End = Start + Direction * Distance;
		int32 NumRicochets = MaxNumRicochets;

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

			APortalActor* Portal = Cast<APortalActor>(OutHit.GetActor());
			if (Portal)
			{
				Direction = UPortalFunctionLibrary::PortalConvertDirection(Portal, Portal->TargetPortal, Direction);
			}
			else
			{
				Direction = FMath::GetReflectionVector(Direction, OutHit.ImpactNormal);
			}

			Start = OutHit.ImpactPoint + Direction;

#if ENABLE_DRAW_DEBUG
			if (bDrawDebugHelpers)
			{
				const FVector AxisY = FVector::CrossProduct(-TraceDirection, OutHit.ImpactNormal);
				const FVector AxisX = FVector::CrossProduct(AxisY, OutHit.ImpactNormal);
				const FRotator DebugRot = FRotationMatrix::MakeFromXZ(AxisX, OutHit.ImpactNormal).Rotator();
				DrawDebugCoordinateSystem(GetWorld(), Start, DebugRot, 100.f, false, 5.f, 0, 2.f);
			}
#endif

			PortalRecursivelyTraceRicochets(Portal, Start, Direction, Distance, NumRicochets);
		}
	}
	else if (MaxNumRicochets > -1)
	{
		FVector Start = TraceStart;
		FVector Direction = TraceDirection.GetSafeNormal();
		float Distance = MaxTraceDistance;
		FVector End = Start + Direction * Distance;
		int32 NumRicochets = MaxNumRicochets;

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

#if ENABLE_DRAW_DEBUG
			if (bDrawDebugHelpers)
			{
				const FVector AxisY = FVector::CrossProduct(-TraceDirection, OutHit.ImpactNormal);
				const FVector AxisX = FVector::CrossProduct(AxisY, OutHit.ImpactNormal);
				const FRotator DebugRot = FRotationMatrix::MakeFromXZ(AxisX, OutHit.ImpactNormal).Rotator();
				DrawDebugCoordinateSystem(GetWorld(), Start, DebugRot, 100.f, false, 5.f, 0, 2.f);
			}
#endif

			APortalActor* Portal = Cast<APortalActor>(OutHit.GetActor());
			if (!Portal)
			{
				NumRicochets--;
			}

			PortalRecursivelyTraceRicochets(Portal, Start, Direction, Distance, NumRicochets, bDrawDebugHelpers);
		}
	}
}
