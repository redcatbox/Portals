// Fill out your copyright notice in the Description page of Project Settings.

#include "DevFunctionLibrary.h"

void UDevFunctionLibrary::DrawDebugGizmo(UObject* WorldContextObject, FVector Location, FRotator Rotation)
{
	FVector Axis_X;
	FVector Axis_Y;
	FVector Axis_Z;

	FRotationMatrix R(Rotation);
	R.GetScaledAxes(Axis_X, Axis_Y, Axis_Z);

	UKismetSystemLibrary::DrawDebugLine(WorldContextObject, Location, Location + Axis_X * 100.0, FLinearColor(1.0, 0.0, 0.0, 1.0), 0.0, 5.0);
	UKismetSystemLibrary::DrawDebugLine(WorldContextObject, Location, Location + Axis_Y * 100.0, FLinearColor(0.0, 1.0, 0.0, 1.0), 0.0, 5.0);
	UKismetSystemLibrary::DrawDebugLine(WorldContextObject, Location, Location + Axis_Z * 100.0, FLinearColor(0.0, 0.0, 1.0, 1.0), 0.0, 5.0);
}
