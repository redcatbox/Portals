// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/MirrorActor.h"

AMirrorActor::AMirrorActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PostUpdateWork;

	SceneCaptureComponent2D->bEnableClipPlane = true;

	//Default assets
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/PortalsPlugin/Dev/Materials/Mirrors/M_MirrorBase.M_MirrorBase"));
	DefaultMaterial = MaterialObj.Object;
	MaterialAsset = DefaultMaterial;
	//Default assets
}

void AMirrorActor::BeginPlay()
{
	Super::BeginPlay();

	if (bRenderEnabled)
	{
		EnableRender();
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
	//Update clip plane
	FVector ActorLocation = GetActorLocation();
	FVector ActorForwardVector = GetActorForwardVector();
	SceneCaptureComponent2D->ClipPlaneBase = ActorLocation;
	SceneCaptureComponent2D->ClipPlaneNormal = ActorForwardVector;

	//Get player camera params
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);

	//FOV
	SceneCaptureComponent2D->FOVAngle = PlayerCameraManager->GetFOVAngle();

	//Location
	FVector SceneCaptureLocation = PlayerCameraManager->GetCameraLocation();
	FTransform ActorTransform = GetActorTransform();
	SceneCaptureLocation = ActorTransform.InverseTransformPosition(SceneCaptureLocation);
	FVector Scale = ActorTransform.GetScale3D();
	Scale = FVector(Scale.X * -1.f, Scale.Y, Scale.Z);
	ActorTransform.SetScale3D(Scale);
	SceneCaptureLocation = ActorTransform.TransformPosition(SceneCaptureLocation);

	//Rotation
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
