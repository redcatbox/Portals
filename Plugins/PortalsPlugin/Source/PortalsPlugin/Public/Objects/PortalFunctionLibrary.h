// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "PortalFunctionLibrary.generated.h"

UCLASS()
class PORTALSPLUGIN_API UPortalFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static void PortalConvertDirection(const AActor* CurrentPortal, const AActor* TargetPortal, const FVector& InDirection, FVector& OutDirection);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static void PortalConvertLocation(const AActor* CurrentPortal, const AActor* TargetPortal, const FVector& InLocation, FVector& OutLocation);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static void PortalConvertLocationMirrored(const AActor* CurrentPortal, const AActor* TargetPortal, const FVector& InLocation, FVector& OutLocation);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static void PortalConvertRotation(const AActor* CurrentPortal, const AActor* TargetPortal, const FRotator& InRotation, FRotator& OutRotation);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static void PortalConvertVelocity(const AActor* CurrentPortal, const AActor* TargetPortal, const FVector& InVelocity, FVector& OutVelocity);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static bool CheckVisibilityByDistance(UObject* WorldContextObject, const float& MaxRenderDistance, const FVector& ActorLocation);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static bool CheckVisibilityByDirection(UObject* WorldContextObject, const FVector& ActorLocation, const FVector& ActorForwardVector);
};
