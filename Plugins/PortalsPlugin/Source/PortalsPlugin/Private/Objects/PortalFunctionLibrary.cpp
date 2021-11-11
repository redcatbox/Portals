// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/PortalFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

FVector UPortalFunctionLibrary::PortalConvertDirection(AActor* CurrentPortal, AActor* TargetPortal, FVector Direction)
{
	const FTransform CurrentPortalTransform = CurrentPortal ? CurrentPortal->GetActorTransform() : FTransform();
	const FTransform TargetPortalTransform = TargetPortal ? TargetPortal->GetActorTransform() : FTransform();
	
	FVector ConvertedDirection = CurrentPortalTransform.InverseTransformVectorNoScale(Direction);
	ConvertedDirection = FMath::GetReflectionVector(ConvertedDirection, FVector(1.f, 0.f, 0.f));
	ConvertedDirection = FMath::GetReflectionVector(ConvertedDirection, FVector(0.f, 1.f, 0.f));
	ConvertedDirection = TargetPortalTransform.TransformVectorNoScale(ConvertedDirection);
	return ConvertedDirection;
}

FVector UPortalFunctionLibrary::PortalConvertLocation(AActor* CurrentPortal, AActor* TargetPortal, FVector Location)
{
	FTransform CurrentPortalTransform = CurrentPortal ? CurrentPortal->GetActorTransform() : FTransform();
	const FTransform TargetPortalTransform = TargetPortal ? TargetPortal->GetActorTransform() : FTransform();
	
	FVector Scale = CurrentPortalTransform.GetScale3D();
	Scale = FVector(Scale.X * -1.f, Scale.Y * -1.f, Scale.Z);
	CurrentPortalTransform.SetScale3D(Scale);

	FVector ConvertedLocation = CurrentPortalTransform.InverseTransformPositionNoScale(Location);
	ConvertedLocation = TargetPortalTransform.TransformPositionNoScale(ConvertedLocation);
	return ConvertedLocation;
}

FVector UPortalFunctionLibrary::PortalConvertLocationMirrored(AActor* CurrentPortal, AActor* TargetPortal, FVector Location)
{
	FTransform CurrentPortalTransform = CurrentPortal ? CurrentPortal->GetActorTransform() : FTransform();
	const FTransform TargetPortalTransform = TargetPortal ? TargetPortal->GetActorTransform() : FTransform();
	
	FVector Scale = CurrentPortalTransform.GetScale3D();
	Scale = FVector(Scale.X, Scale.Y * -1.f, Scale.Z);
	CurrentPortalTransform.SetScale3D(Scale);

	FVector ConvertedLocation = CurrentPortalTransform.InverseTransformPositionNoScale(Location);
	ConvertedLocation = TargetPortalTransform.TransformPositionNoScale(ConvertedLocation);
	return ConvertedLocation;
}

FRotator UPortalFunctionLibrary::PortalConvertRotation(AActor* CurrentPortal, AActor* TargetPortal, FRotator Rotation)
{
	FRotationMatrix R(Rotation);
	FVector X;
	FVector Y;
	FVector Z;
	R.GetScaledAxes(X, Y, Z);
	
	FVector DirX = PortalConvertDirection(CurrentPortal, TargetPortal, X);
	FVector DirY = PortalConvertDirection(CurrentPortal, TargetPortal, Y);

	const FRotator ConvertedRotation = FRotationMatrix::MakeFromXY(X, Y).Rotator();
	return ConvertedRotation;
}

FVector UPortalFunctionLibrary::PortalConvertVelocity(AActor* CurrentPortal, AActor* TargetPortal, FVector Velocity)
{
	const float VelocitySize = Velocity.Size();
	const FVector VelocityDirection = Velocity.GetSafeNormal();
	const FVector ConvertedVelocity = PortalConvertDirection(CurrentPortal, TargetPortal, VelocityDirection) * VelocitySize;
	return ConvertedVelocity;
}

bool UPortalFunctionLibrary::CheckVisibilityByDistance(UObject* WorldContextObject, float MaxRenderDistance, FVector ActorLocation)
{
	bool bVisible = false;
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(WorldContextObject, 0);

	if (PlayerCameraManager)
	{
		const FVector PlayerCameraLocation = PlayerCameraManager->GetCameraLocation();
		const float Distance = (PlayerCameraLocation - ActorLocation).Size();

		if (Distance <= MaxRenderDistance)
		{
			bVisible = true;
		}
	}

	return bVisible;
}

bool UPortalFunctionLibrary::CheckVisibilityByDirection(UObject* WorldContextObject, FVector ActorLocation, FVector ActorForwardVector)
{
	bool bVisible = false;
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(WorldContextObject, 0);
	if (PlayerCameraManager)
	{
		const FVector PlayerCameraLocation = PlayerCameraManager->GetCameraLocation();
		const float Projection = FVector::DotProduct(PlayerCameraLocation - ActorLocation, ActorForwardVector);

		if (Projection >= 0)
		{
			bVisible = true;
		}
	}
	
	return bVisible;
}
