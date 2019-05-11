// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DevFunctionLibrary.generated.h"

UCLASS()
class UDevFunctionLibrary : public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = DevFunctions)
	static void DrawDebugGizmo(UObject* WorldContextObject, FVector Location, FRotator Rotation);
};
