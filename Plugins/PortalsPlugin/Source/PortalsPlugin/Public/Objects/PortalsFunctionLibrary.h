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
	UFUNCTION(BlueprintCallable, meta = (Category = "PortalsFunctions"))
		static FVector PortalConvertDirection(AActor* CurrentPortal, AActor* TargetPortal, FVector Direction);

	UFUNCTION(BlueprintCallable, meta = (Category = "PortalsFunctions"))
		static FVector PortalConvertLocation(AActor* CurrentPortal, AActor* TargetPortal, FVector Location);

	UFUNCTION(BlueprintCallable, meta = (Category = "PortalsFunctions"))
		static FVector PortalConvertLocationMirrored(AActor* CurrentPortal, AActor* TargetPortal, FVector Location);

	UFUNCTION(BlueprintCallable, meta = (Category = "PortalsFunctions"))
		static FRotator PortalConvertRotation(AActor* CurrentPortal, AActor* TargetPortal, FRotator Rotation);

	UFUNCTION(BlueprintCallable, meta = (Category = "PortalsFunctions"))
		static FVector PortalConvertVelocity(AActor* CurrentPortal, AActor* TargetPortal, FVector Velocity);

	UFUNCTION(BlueprintCallable, meta = (Category = "PortalsFunctions"))
		static bool CheckPortalsValidity(AActor* CurrentPortal, AActor* TargetPortal);

	UFUNCTION(BlueprintCallable, meta = (Category = "PortalsFunctions"))
		static void GetPortalsTransforms(AActor* CurrentPortal, AActor* TargetPortal, FTransform& CurrentPortalTransform, FTransform& TargetPortalTransform);

	UFUNCTION(BlueprintCallable, meta = (Category = "PortalsFunctions"))
		static bool CheckVisibilityByDistance(UObject* WorldContextObject, float MaxRenderDistance, FVector ActorLocation);

	UFUNCTION(BlueprintCallable, meta = (Category = "PortalsFunctions"))
		static bool CheckVisibilityByDirection(UObject* WorldContextObject, FVector ActorLocation, FVector ActorForwardVector);
};