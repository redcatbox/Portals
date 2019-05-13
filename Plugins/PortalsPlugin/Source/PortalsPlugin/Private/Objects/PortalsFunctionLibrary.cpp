// Fill out your copyright notice in the Description page of Project Settings.

#include "PortalsFunctionLibrary.h"

FVector UPortalsFunctionLibrary::PortalConvertDirection(AActor* CurrentPortal, AActor* TargetPortal, FVector Direction)
{
	FTransform CurrentPortalTransform;
	FTransform TargetPortalTransform;
	GetPortalsTransforms(CurrentPortal, TargetPortal, CurrentPortalTransform, TargetPortalTransform);

	FVector ConvertedDirection = CurrentPortalTransform.InverseTransformVectorNoScale(Direction);
	ConvertedDirection = FMath::GetReflectionVector(ConvertedDirection, FVector(1.f, 0.f, 0.f));
	ConvertedDirection = FMath::GetReflectionVector(ConvertedDirection, FVector(0.f, 1.f, 0.f));
	ConvertedDirection = TargetPortalTransform.TransformVectorNoScale(ConvertedDirection);
	return ConvertedDirection;
}

FVector UPortalsFunctionLibrary::PortalConvertLocation(AActor* CurrentPortal, AActor* TargetPortal, FVector Location)
{
	FTransform CurrentPortalTransform;
	FTransform TargetPortalTransform;
	GetPortalsTransforms(CurrentPortal, TargetPortal, CurrentPortalTransform, TargetPortalTransform);

	FVector Scale = CurrentPortalTransform.GetScale3D();
	Scale = FVector(Scale.X * -1.f, Scale.Y * -1.f, Scale.Z);
	CurrentPortalTransform.SetScale3D(Scale);

	FVector ConvertedLocation = CurrentPortalTransform.InverseTransformPositionNoScale(Location);
	ConvertedLocation = TargetPortalTransform.TransformPositionNoScale(ConvertedLocation);
	return ConvertedLocation;
}

FVector UPortalsFunctionLibrary::PortalConvertLocationMirrored(AActor* CurrentPortal, AActor* TargetPortal, FVector Location)
{
	FTransform CurrentPortalTransform;
	FTransform TargetPortalTransform;
	GetPortalsTransforms(CurrentPortal, TargetPortal, CurrentPortalTransform, TargetPortalTransform);

	FVector Scale = CurrentPortalTransform.GetScale3D();
	Scale = FVector(Scale.X, Scale.Y * -1.f, Scale.Z);
	CurrentPortalTransform.SetScale3D(Scale);

	FVector ConvertedLocation = CurrentPortalTransform.InverseTransformPositionNoScale(Location);
	ConvertedLocation = TargetPortalTransform.TransformPositionNoScale(ConvertedLocation);
	return ConvertedLocation;
}

FRotator UPortalsFunctionLibrary::PortalConvertRotation(AActor* CurrentPortal, AActor* TargetPortal, FRotator Rotation)
{
	FRotationMatrix R(Rotation);
	FVector X;
	FVector Y;
	FVector Z;
	R.GetScaledAxes(X, Y, Z);
	
	FVector DirX = PortalConvertDirection(CurrentPortal, TargetPortal, X);
	FVector DirY = PortalConvertDirection(CurrentPortal, TargetPortal, Y);

	FRotator ConvertedRotation = FRotationMatrix::MakeFromXY(X, Y).Rotator();
	return ConvertedRotation;
}

FVector UPortalsFunctionLibrary::PortalConvertVelocity(AActor* CurrentPortal, AActor* TargetPortal, FVector Velocity)
{
	float VelocitySize = Velocity.Size();
	FVector VelocityDirection = Velocity.GetSafeNormal();
	FVector ConvertedVelocity = PortalConvertDirection(CurrentPortal, TargetPortal, VelocityDirection) * VelocitySize;
	return ConvertedVelocity;
}

bool UPortalsFunctionLibrary::CheckPortalsValidity(AActor* CurrentPortal, AActor* TargetPortal)
{
	if (::IsValid(CurrentPortal) && ::IsValid(TargetPortal))
	{
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid portal actor pointer!"));
		return false;
	}
}

void UPortalsFunctionLibrary::GetPortalsTransforms(AActor* CurrentPortal, AActor* TargetPortal, FTransform& CurrentPortalTransform, FTransform& TargetPortalTransform)
{
	if (CheckPortalsValidity(CurrentPortal, TargetPortal))
	{
		CurrentPortalTransform = CurrentPortal->GetActorTransform();
		TargetPortalTransform = TargetPortal->GetActorTransform();
	}
}

bool UPortalsFunctionLibrary::CheckVisibilityByDistance(UObject* WorldContextObject, float MaxRenderDistance, FVector ActorLocation)
{
	bool bVisible = false;
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(WorldContextObject, 0);
	FVector PlayerCameraLocation = PlayerCameraManager->GetCameraLocation();
	float Distance = (PlayerCameraLocation - ActorLocation).Size();
	
	if (Distance <= MaxRenderDistance)
	{
		bVisible = true;
	}

	return bVisible;
}

bool UPortalsFunctionLibrary::CheckVisibilityByDirection(UObject* WorldContextObject, FVector ActorLocation, FVector ActorForwardVector)
{
	bool bVisible = false;
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(WorldContextObject, 0);
	FVector PlayerCameraLocation = PlayerCameraManager->GetCameraLocation();
	float Projection = FVector::DotProduct(PlayerCameraLocation - ActorLocation, ActorForwardVector);

	if (Projection >= 0)
		bVisible = true;

	return bVisible;
}