// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PortalTraceComponent.generated.h"

/**
 * Tracing through portals
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTALSPLUGIN_API UPortalTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool bDrawDebugInfo;

	//Trace on provided max distance and max number of ricochets
	UFUNCTION(BlueprintCallable, Category = PortalTracing)
	virtual void TraceRicochets(FVector TraceStart, FVector TraceDirection, float MaxTraceDistance, int32 MaxNumRicochets, bool bDrawDebugHelpers = false);

	// Trace checking for portal actors recursively on provided max distance and max number of ricochets
	UFUNCTION(BlueprintCallable, Category = PortalTracing)
	virtual void PortalRecursivelyTraceRicochets(class APortalActor* PortalActor, FVector TraceStart, FVector TraceDirection, float MaxTraceDistance, int32 MaxNumRicochets, bool bDrawDebugHelpers = false);
};
