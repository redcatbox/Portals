// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/MirrorActor.h"

AMirrorActor::AMirrorActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PostUpdateWork;

	SceneCaptureComponent2D->bEnableClipPlane = true;

	//Default assets
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/PortalsPlugin/Dev/Materials/Mirrors/M_MirrorBase.M_MirrorBase"));
	//DefaultMaterial = MaterialObj.Object;
	//MaterialAsset = DefaultMaterial;
	//Default assets
}

void AMirrorActor::BeginPlay()
{
	Super::BeginPlay();

	if (bRenderEnabled)
	{
		EnableRender(bRenderEnabled);
		APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
		AddTickPrerequisiteActor(PlayerCameraManager);
	}
}

void AMirrorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRenderEnabled)
	{
		if (CheckSCCNeedsToUpdate())
		{
			UpdateSCC2DTransform();
			SceneCaptureComponent2D->CaptureScene();
		}
	}
}

void AMirrorActor::UpdateSCC2DTransform()
{
	FVector ActorLocation = GetActorLocation();
	FVector ActorForwardVector = GetActorForwardVector();
	SceneCaptureComponent2D->ClipPlaneBase = ActorLocation;
	SceneCaptureComponent2D->ClipPlaneNormal = ActorForwardVector;

	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);

	SceneCaptureComponent2D->FOVAngle = PlayerCameraManager->GetFOVAngle();

	FVector SceneCaptureLocation = PlayerCameraManager->GetCameraLocation();
	FTransform ActorTransform = GetActorTransform();
	SceneCaptureLocation = ActorTransform.InverseTransformPosition(SceneCaptureLocation);
	FVector Scale = ActorTransform.GetScale3D();
	Scale = FVector(Scale.X * -1.f, Scale.Y, Scale.Z);
	ActorTransform.SetScale3D(Scale);
	SceneCaptureLocation = ActorTransform.TransformPosition(SceneCaptureLocation);

	FRotator SceneCaptureRotation = PlayerCameraManager->GetCameraRotation();
	FVector X;
	FVector Y;
	FVector Z;
	FRotationMatrix R(SceneCaptureRotation);
	R.GetScaledAxes(X, Y, Z);
	X = FMath::GetReflectionVector(X, ActorForwardVector);
	Y = FMath::GetReflectionVector(Y, ActorForwardVector);
	Z = FMath::GetReflectionVector(Z, ActorForwardVector);
	SceneCaptureRotation = FRotationMatrix::MakeFromXY(X, Y).Rotator();

	SceneCaptureComponent2D->SetWorldLocationAndRotationNoPhysics(SceneCaptureLocation, SceneCaptureRotation);
}

#if WITH_EDITOR
void AMirrorActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
