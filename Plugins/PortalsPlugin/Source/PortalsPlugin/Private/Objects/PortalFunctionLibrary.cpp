// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/PortalFunctionLibrary.h"
#include "PortalsPlugin.h"
#include "Kismet/GameplayStatics.h"

void UPortalFunctionLibrary::PortalConvertDirection(const AActor* CurrentPortal, const AActor* TargetPortal, const FVector& InDirection, FVector& OutDirection)
{
	const FTransform CurrentPortalTransform = CurrentPortal ? CurrentPortal->GetActorTransform() : FTransform();
	const FTransform TargetPortalTransform = TargetPortal ? TargetPortal->GetActorTransform() : FTransform();
	
	OutDirection = CurrentPortalTransform.InverseTransformVectorNoScale(InDirection);
	OutDirection = FMath::GetReflectionVector(OutDirection, FVector(1.f, 0.f, 0.f));
	OutDirection = FMath::GetReflectionVector(OutDirection, FVector(0.f, 1.f, 0.f));
	OutDirection = TargetPortalTransform.TransformVectorNoScale(OutDirection);
}

void UPortalFunctionLibrary::PortalConvertLocation(const AActor* CurrentPortal, const AActor* TargetPortal, const FVector& InLocation, FVector& OutLocation)
{
	FTransform CurrentPortalTransform = CurrentPortal ? CurrentPortal->GetActorTransform() : FTransform();
	FVector Scale = CurrentPortalTransform.GetScale3D();
	Scale = FVector(-Scale.X, -Scale.Y, Scale.Z);
	CurrentPortalTransform.SetScale3D(Scale);

	const FTransform TargetPortalTransform = TargetPortal ? TargetPortal->GetActorTransform() : FTransform();
	
	const FVector ConvertedLocation = CurrentPortalTransform.InverseTransformPosition(InLocation);
	OutLocation = TargetPortalTransform.TransformPositionNoScale(ConvertedLocation);
}

void UPortalFunctionLibrary::PortalConvertLocationMirrored(const AActor* CurrentPortal, const AActor* TargetPortal, const FVector& InLocation, FVector& OutLocation)
{
	FTransform CurrentPortalTransform = CurrentPortal ? CurrentPortal->GetActorTransform() : FTransform();
	FVector Scale = CurrentPortalTransform.GetScale3D();
	Scale = FVector(Scale.X, -Scale.Y, Scale.Z);
	CurrentPortalTransform.SetScale3D(Scale);

	const FTransform TargetPortalTransform = TargetPortal ? TargetPortal->GetActorTransform() : FTransform();

	const FVector ConvertedLocation = CurrentPortalTransform.InverseTransformPosition(InLocation);
	OutLocation = TargetPortalTransform.TransformPositionNoScale(ConvertedLocation);
}

void UPortalFunctionLibrary::PortalConvertRotation(const AActor* CurrentPortal, const AActor* TargetPortal, const FRotator& InRotation, FRotator& OutRotation)
{
	const FQuat Rotation = InRotation.Quaternion();
	FVector DirX, DirY;
	PortalConvertDirection(CurrentPortal, TargetPortal, Rotation.GetAxisX(), DirX);
	PortalConvertDirection(CurrentPortal, TargetPortal, Rotation.GetAxisY(), DirY);
	OutRotation = FRotationMatrix::MakeFromXY(DirX, DirY).Rotator();
}

void UPortalFunctionLibrary::PortalConvertVelocity(const AActor* CurrentPortal, const AActor* TargetPortal, const FVector& InVelocity, FVector& OutVelocity)
{
	PortalConvertDirection(CurrentPortal, TargetPortal, InVelocity.GetSafeNormal(), OutVelocity);
	OutVelocity *= InVelocity.Size();
}

bool UPortalFunctionLibrary::CheckVisibilityByDistance(UObject* WorldContextObject, const float& MaxRenderDistance, const FVector& ActorLocation)
{
	if (const APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(WorldContextObject, 0))
	{
		const FVector PlayerCameraLocation = PlayerCameraManager->GetCameraLocation();
		const float Distance = (PlayerCameraLocation - ActorLocation).Size();
		if (Distance <= MaxRenderDistance)
		{
			return true;
		}
	}

	return false;
}

bool UPortalFunctionLibrary::CheckVisibilityByDirection(UObject* WorldContextObject, const FVector& ActorLocation, const FVector& ActorForwardVector)
{
	if (const APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(WorldContextObject, 0))
	{
		const FVector PlayerCameraLocation = PlayerCameraManager->GetCameraLocation();
		const float Projection = FVector::DotProduct(PlayerCameraLocation - ActorLocation, ActorForwardVector);
		if (Projection >= 0)
		{
			return true;
		}
	}
	
	return false;
}
