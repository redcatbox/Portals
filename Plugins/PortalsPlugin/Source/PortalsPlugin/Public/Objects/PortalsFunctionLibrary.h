// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "PortalsFunctionLibrary.generated.h"

UCLASS()
class PORTALSPLUGIN_API UPortalsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static FVector PortalConvertDirection(AActor* CurrentPortal, AActor* TargetPortal, FVector Direction);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static FVector PortalConvertLocation(AActor* CurrentPortal, AActor* TargetPortal, FVector Location);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static FVector PortalConvertLocationMirrored(AActor* CurrentPortal, AActor* TargetPortal, FVector Location);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static FRotator PortalConvertRotation(AActor* CurrentPortal, AActor* TargetPortal, FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static FVector PortalConvertVelocity(AActor* CurrentPortal, AActor* TargetPortal, FVector Velocity);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static bool CheckVisibilityByDistance(UObject* WorldContextObject, float MaxRenderDistance, FVector ActorLocation);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static bool CheckVisibilityByDirection(UObject* WorldContextObject, FVector ActorLocation, FVector ActorForwardVector);
};
