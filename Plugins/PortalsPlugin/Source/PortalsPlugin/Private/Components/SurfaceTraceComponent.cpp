// Fill out your copyright notice in the Description page of Project Settings.

#include "SurfaceTraceComponent.h"

// Sets default values for this component's properties
USurfaceTraceComponent::USurfaceTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USurfaceTraceComponent::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void USurfaceTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USurfaceTraceComponent::TraceLoop(FVector TraceStart, FVector TraceDirection, float TraceDistance, int NumRicochets)
{
	TraceDirection = TraceDirection.GetSafeNormal();
	FVector TraceEnd = TraceStart + TraceDirection * TraceDistance;

	for (int32 i = 0; i < NumRicochets; i++)
	{
		FHitResult OutHit;
		TArray<AActor*> ActorsToIgnore;
		bool bHit = UKismetSystemLibrary::LineTraceSingle(this, TraceStart, TraceEnd, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true, FLinearColor::Red, FLinearColor::Green, 5.f);

		if (bHit)
		{

		}
		//Trace
		//FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
		//TraceParams.bTraceAsyncScene = true;
		//TraceParams.bReturnPhysicalMaterial = false;
		//FHitResult TraceOutHit(ForceInit);
		//FVector TraceStart = GetActorTransform().TransformPosition(Location);
		//FVector TraceEnd = TraceStart - (GetActorUpVector()) * BoxExtent.Z * 1.1;
		//bool bHit = GetWorld()->LineTraceSingleByChannel(
		//	TraceOutHit,
		//	TraceStart,
		//	TraceEnd,
		//	ECC_Visibility,
		//	TraceParams
		//);
	}
}

void USurfaceTraceComponent::TracePortal(FVector TraceStart, FVector TraceDirection, float TraceDistance) {}

void USurfaceTraceComponent::TracePortalRecursive(APortalActor* PortalActor, FVector PreviousTraceDirection, float TraceDistance, FVector PreviousImpactPoint) {}