// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurfaceTraceComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTALSPLUGIN_API USurfaceTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool bDrawDebugInfo;

	/** Trace on provided max distance and max number of ricochets */
	UFUNCTION(BlueprintCallable, Category = SurfaceTracing)
	virtual void TraceWithRicochets(FVector TraceStart, FVector TraceDirection, float MaxTraceDistance, int32 MaxNumRicochets);

	/** Trace checking for portal actors recursively on provided max distance and max number of ricochets */
	UFUNCTION(BlueprintCallable, Category = SurfaceTracing)
	virtual void TraceForPortalRecursivelyWithRicochets(class APortalActor* PortalActor, FVector TraceStart, FVector TraceDirection, float MaxTraceDistance, int32 MaxNumRicochets);
};
