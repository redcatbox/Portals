// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/PortalFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

FVector UPortalFunctionLibrary::PortalConvertDirection(AActor* CurrentPortal, AActor* TargetPortal, FVector InDirection)
{
	const FTransform CurrentPortalTransform = CurrentPortal ? CurrentPortal->GetActorTransform() : FTransform();
	const FTransform TargetPortalTransform = TargetPortal ? TargetPortal->GetActorTransform() : FTransform();
	
	FVector ConvertedDirection = CurrentPortalTransform.InverseTransformVectorNoScale(InDirection);
	ConvertedDirection = FMath::GetReflectionVector(ConvertedDirection, FVector(1.f, 0.f, 0.f));
	ConvertedDirection = FMath::GetReflectionVector(ConvertedDirection, FVector(0.f, 1.f, 0.f));
	ConvertedDirection = TargetPortalTransform.TransformVectorNoScale(ConvertedDirection);
	return ConvertedDirection;
}

FVector UPortalFunctionLibrary::PortalConvertLocation(AActor* CurrentPortal, AActor* TargetPortal, FVector InLocation)
{
	FTransform CurrentPortalTransform = CurrentPortal ? CurrentPortal->GetActorTransform() : FTransform();
	const FTransform TargetPortalTransform = TargetPortal ? TargetPortal->GetActorTransform() : FTransform();
	
	FVector Scale = CurrentPortalTransform.GetScale3D();
	Scale = FVector(Scale.X * -1.f, Scale.Y * -1.f, Scale.Z);
	CurrentPortalTransform.SetScale3D(Scale);

	FVector ConvertedLocation = CurrentPortalTransform.InverseTransformPositionNoScale(InLocation);
	ConvertedLocation = TargetPortalTransform.TransformPositionNoScale(ConvertedLocation);
	return ConvertedLocation;
}

FVector UPortalFunctionLibrary::PortalConvertLocationMirrored(AActor* CurrentPortal, AActor* TargetPortal, FVector InLocation)
{
	FTransform CurrentPortalTransform = CurrentPortal ? CurrentPortal->GetActorTransform() : FTransform();
	const FTransform TargetPortalTransform = TargetPortal ? TargetPortal->GetActorTransform() : FTransform();
	
	FVector Scale = CurrentPortalTransform.GetScale3D();
	Scale = FVector(Scale.X, Scale.Y * -1.f, Scale.Z);
	CurrentPortalTransform.SetScale3D(Scale);

	FVector ConvertedLocation = CurrentPortalTransform.InverseTransformPositionNoScale(InLocation);
	ConvertedLocation = TargetPortalTransform.TransformPositionNoScale(ConvertedLocation);
	return ConvertedLocation;
}

FRotator UPortalFunctionLibrary::PortalConvertRotation(AActor* CurrentPortal, AActor* TargetPortal, FRotator InRotation)
{
	FRotationMatrix R(InRotation);
	FVector X;
	FVector Y;
	FVector Z;
	R.GetScaledAxes(X, Y, Z);
	
	FVector DirX = PortalConvertDirection(CurrentPortal, TargetPortal, X);
	FVector DirY = PortalConvertDirection(CurrentPortal, TargetPortal, Y);

	const FRotator ConvertedRotation = FRotationMatrix::MakeFromXY(X, Y).Rotator();
	return ConvertedRotation;
}

FVector UPortalFunctionLibrary::PortalConvertVelocity(AActor* CurrentPortal, AActor* TargetPortal, FVector InVelocity)
{
	const float VelocitySize = InVelocity.Size();
	const FVector VelocityDirection = InVelocity.GetSafeNormal();
	const FVector ConvertedVelocity = PortalConvertDirection(CurrentPortal, TargetPortal, VelocityDirection) * VelocitySize;
	return ConvertedVelocity;
}

bool UPortalFunctionLibrary::CheckVisibilityByDistance(UObject* WorldContextObject, float MaxRenderDistance, FVector InActorLocation)
{
	bool bVisible = false;
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(WorldContextObject, 0);

	if (PlayerCameraManager)
	{
		const FVector PlayerCameraLocation = PlayerCameraManager->GetCameraLocation();
		const float Distance = (PlayerCameraLocation - InActorLocation).Size();

		if (Distance <= MaxRenderDistance)
		{
			bVisible = true;
		}
	}

	return bVisible;
}

bool UPortalFunctionLibrary::CheckVisibilityByDirection(UObject* WorldContextObject, FVector ActorLocation, FVector InActorForwardVector)
{
	bool bVisible = false;
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(WorldContextObject, 0);
	if (PlayerCameraManager)
	{
		const FVector PlayerCameraLocation = PlayerCameraManager->GetCameraLocation();
		const float Projection = FVector::DotProduct(PlayerCameraLocation - ActorLocation, InActorForwardVector);

		if (Projection >= 0)
		{
			bVisible = true;
		}
	}
	
	return bVisible;
}
