// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/PortalActor.h"

APortalActor::APortalActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PostUpdateWork;

	PortalSurfaceSize = FVector(1.f, 200.f, 200.f);
	bUseInnerReplacement = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxExtent = FVector(10.f, 100.f, 100.f);
	BoxCollision->BodyInstance.SetCollisionProfileName(FName(TEXT("Custom")));
	
	SceneCaptureComponent2D->bEnableClipPlane = true;
	//SceneCaptureComponent2D->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

	//Default assets
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/PortalsPlugin/Dev/Materials/Portals/M_PortalBase.M_PortalBase"));
	DefaultMaterial = MaterialObj.Object;
	MaterialAsset = DefaultMaterial;
	//Default assets

	TargetPortal = nullptr;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
	ArrowComponent->Mobility = EComponentMobility::Static;
	ArrowComponent->ArrowColor = FColor(255, 0, 255, 255);
	ArrowComponent->bVisualizeComponent = true;

	DestinationPoint = FVector(0.f, 0.f, 0.f);
}

void APortalActor::BeginPlay()
{
	Super::BeginPlay();

	if (bRenderEnabled)
	{
		EnableRender();
		APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
		AddTickPrerequisiteActor(PlayerCameraManager);
	}
}

void APortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRenderEnabled)
	{
		if (CheckSCCNeedsToUpdate())
		{
			UpdateSCC2DTransform();
			SceneCaptureComponent2D->CaptureScene();
		}

		if (bUseInnerReplacement)
			UpdateReplacementRenderParams();
	}
}

void APortalActor::UpdateSCC2DTransform()
{
	if (::IsValid(TargetPortal))
	{
		//Update clip plane
		SceneCaptureComponent2D->ClipPlaneBase = TargetPortal->GetActorLocation();
		SceneCaptureComponent2D->ClipPlaneNormal = TargetPortal->GetActorForwardVector();

		APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
		FVector SceneCaptureLocation = PlayerCameraManager->GetCameraLocation();
		FRotator SceneCaptureRotation = PlayerCameraManager->GetCameraRotation();

		SceneCaptureLocation = UPortalsFunctionLibrary::PortalConvertLocation(this, TargetPortal, SceneCaptureLocation);
		SceneCaptureRotation = UPortalsFunctionLibrary::PortalConvertRotation(this, TargetPortal, SceneCaptureRotation);

		SceneCaptureComponent2D->SetWorldLocationAndRotationNoPhysics(SceneCaptureLocation, SceneCaptureRotation);
	}
}

void APortalActor::UpdateReplacementRenderParams() {}

void APortalActor::UpdateArrowPointer() {}

#if WITH_EDITOR
void APortalActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == TEXT("Transform") || TEXT("PortalSurfaceSize") || TEXT("BoxExtent"))
	{
		PortalSurfaceSize = FVector(
			FMath::Clamp(PortalSurfaceSize.X, 0.f, PortalSurfaceSize.X),
			FMath::Clamp(PortalSurfaceSize.Y, 0.f, PortalSurfaceSize.Y),
			FMath::Clamp(PortalSurfaceSize.Z, 0.f, PortalSurfaceSize.Z));

		StaticMeshComponent->SetRelativeScale3D(PortalSurfaceSize);

		BoxExtent = FVector(
			FMath::Clamp(BoxExtent.X, 0.f, BoxExtent.X),
			FMath::Clamp(BoxExtent.Y, 0.f, BoxExtent.Y),
			FMath::Clamp(BoxExtent.Z, 0.f, BoxExtent.Z));

		BoxCollision->SetBoxExtent(BoxExtent);
		BoxCollision->SetRelativeLocation(FVector(BoxExtent.X, 0.f, 0.f), false, nullptr, ETeleportType::None);
	}
}
#endif
