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
	// Sets default values for this component's properties
	USurfaceTraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		virtual void TraceLoop(FVector TraceStart, FVector TraceDirection, float TraceDistance, int NumRicochets);

	UFUNCTION()
		virtual void TracePortal(FVector TraceStart, FVector TraceDirection, float TraceDistance);

	UFUNCTION()
		virtual void TracePortalRecursive(APortalActor* PortalActor, FVector PreviousTraceDirection, float TraceDistance, FVector PreviousImpactPoint);
};
