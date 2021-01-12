// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actors/PortalActor.h"
#include "SurfaceTraceComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTALSPLUGIN_API USurfaceTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USurfaceTraceComponent();

	UFUNCTION(BlueprintCallable, Category = SurfaceTracing)
		virtual void TraceLoop(FVector TraceStart, FVector TraceDirection, float MaxTraceDistance, int32 MaxNumRicochets);

	UFUNCTION(BlueprintCallable, Category = SurfaceTracing)
		virtual void TracePortal(FVector TraceStart, FVector TraceDirection, float MaxTraceDistance);

	UFUNCTION(BlueprintCallable, Category = SurfaceTracing)
		virtual void TracePortalRecursive(APortalActor* PortalActor, FVector PreviousTraceDirection, float MaxTraceDistance, FVector PreviousImpactPoint);
};
