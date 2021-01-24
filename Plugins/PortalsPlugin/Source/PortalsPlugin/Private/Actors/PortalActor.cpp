// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/PortalActor.h"

APortalActor::APortalActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PostUpdateWork;

	bUseInnerReplacement = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxExtent = FVector(10.f, 100.f, 100.f);
	BoxCollision->BodyInstance.SetCollisionProfileName(FName(TEXT("Custom")));

	SceneCaptureComponent2D->bEnableClipPlane = true;
	//SceneCaptureComponent2D->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
	
	TargetPortal = nullptr;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
	ArrowComponent->Mobility = EComponentMobility::Static;
	ArrowComponent->ArrowColor = FColor(255, 0, 255, 255);
	ArrowComponent->bVisualizeComponent = true;

	DestinationPoint = FVector::ZeroVector;
}

void APortalActor::BeginPlay()
{
	Super::BeginPlay();

	if (bRenderEnabled)
	{
		EnableRender(bRenderEnabled);
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
	if (TargetPortal)
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
	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == TEXT("BoxExtent"))
	{
		BoxExtent = FVector(
			FMath::Clamp(BoxExtent.X, 0.f, BoxExtent.X),
			FMath::Clamp(BoxExtent.Y, 0.f, BoxExtent.Y),
			FMath::Clamp(BoxExtent.Z, 0.f, BoxExtent.Z));

		BoxCollision->SetBoxExtent(BoxExtent);
		BoxCollision->SetRelativeLocation(FVector(BoxExtent.X, 0.f, 0.f), false, nullptr, ETeleportType::None);
	}
}

void APortalActor::EditorApplyScale(const FVector& DeltaScale, const FVector* PivotLocation, bool bAltDown, bool bShiftDown, bool bCtrlDown)
{
	Super::EditorApplyScale(DeltaScale, PivotLocation, bAltDown, bShiftDown, bCtrlDown);

	FVector ScaleToApply = StaticMeshComponent->GetRelativeScale3D();
	if (bUsePercentageBasedScaling)
	{
		ScaleToApply *= FVector::OneVector + DeltaScale;
	}
	else
	{
		ScaleToApply += DeltaScale;
	}

	BoxCollision->SetBoxExtent(BoxExtent * DeltaScale);
	BoxCollision->SetRelativeLocation(FVector(BoxExtent.X, 0.f, 0.f), false, nullptr, ETeleportType::None);
	StaticMeshComponent->SetRelativeScale3D(ScaleToApply);
}

void APortalActor::EditorApplyMirror(const FVector& MirrorScale, const FVector& PivotLocation)
{
	Super::EditorApplyMirror(MirrorScale, PivotLocation);
	SetActorScale3D(FVector::OneVector);
}
#endif
