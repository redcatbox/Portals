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
	static FVector PortalConvertDirection(AActor* CurrentPortal, AActor* TargetPortal, FVector InDirection);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static FVector PortalConvertLocation(AActor* CurrentPortal, AActor* TargetPortal, FVector InLocation);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static FVector PortalConvertLocationMirrored(AActor* CurrentPortal, AActor* TargetPortal, FVector InLocation);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static FRotator PortalConvertRotation(AActor* CurrentPortal, AActor* TargetPortal, FRotator InRotation);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static FVector PortalConvertVelocity(AActor* CurrentPortal, AActor* TargetPortal, FVector InVelocity);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static bool CheckVisibilityByDistance(UObject* WorldContextObject, float MaxRenderDistance, FVector InActorLocation);

	UFUNCTION(BlueprintCallable, Category = PortalsFunctions)
	static bool CheckVisibilityByDirection(UObject* WorldContextObject, FVector ActorLocation, FVector InActorForwardVector);
};
