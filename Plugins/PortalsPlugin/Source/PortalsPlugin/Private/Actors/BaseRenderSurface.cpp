// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/BaseRenderSurface.h"

ABaseRenderSurface::ABaseRenderSurface()
{
	PrimaryActorTick.bCanEverTick = false;
	//PrimaryActorTick.TickGroup = ETickingGroup::TG_PostUpdateWork;

	// Scene root
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	DefaultSceneRoot->Mobility = EComponentMobility::Static;
	DefaultSceneRoot->bVisualizeComponent = true;

	SceneSCC = CreateDefaultSubobject<USceneComponent>(TEXT("SceneSCC"));
	SceneSCC->SetupAttachment(RootComponent);
	DefaultSceneRoot->Mobility = EComponentMobility::Static;
	DefaultSceneRoot->bVisualizeComponent = true;

	//SceneCaptureComponent2D
	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
	SceneCaptureComponent2D->SetupAttachment(SceneSCC);
	//SceneCaptureComponent2D->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	//SceneCaptureComponent2D->bEnableClipPlane = true;
	SceneCaptureComponent2D->bCaptureEveryFrame = false;
	SceneCaptureComponent2D->bCaptureOnMovement = false;
	SceneCaptureComponent2D->bAutoActivate = false;

	//Default assets
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/PortalsPlugin/Dev/Meshes/SM_1UnitPlane.SM_1UnitPlane"));
	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/PortalsPlugin/Dev/Materials/Screens/M_ScreenBase.M_ScreenBase"));
	//DefaultMesh = MeshObj.Object;
	//DefaultMaterial = MaterialObj.Object;
	//MeshAsset = DefaultMesh;
	//MaterialAsset = DefaultMaterial;
	//Default assets

	// Static mesh component
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	

	bRenderEnabled = true;
	bRT_UseViewportSize = false;
	RenderTargetTexture = nullptr;
	RenderTargetResolution = FVector2D(128.f);
	RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA16f;

	// Dynamic material instance
	RenderTargetParameterName = FName(TEXT("TextureRT"));

	bUseUpdateDistance = true;
	MaxCaptureUpdateDistance = 1000.f;
	bUseUpdateDirection = true;
}

void ABaseRenderSurface::InitSceneCapture()
{
	if (bRT_UseViewportSize)
	{
		FViewport* Viewport = GEngine->GameViewport->Viewport;
		if (Viewport)
		{
			const FVector2D ViewportSize = FVector2D(Viewport->GetSizeXY());
			if (ViewportSize.Y != 0)
			{
				RenderTargetResolution = ViewportSize;
			}
		}
	}

	RenderTargetTexture = UKismetRenderingLibrary::CreateRenderTarget2D(this, RenderTargetResolution.X, RenderTargetResolution.Y, RenderTargetFormat);
	SceneCaptureComponent2D->TextureTarget = RenderTargetTexture;

	if (StaticMeshComponent->GetStaticMesh())
	{
		for (int32 i = 0; i < StaticMeshComponent->GetNumMaterials(); ++i)
		{
			UMaterialInterface* Material = StaticMeshComponent->GetStaticMesh()->GetMaterial(i);
			UMaterialInstanceDynamic* MID = StaticMeshComponent->CreateDynamicMaterialInstance(i, Material);
			MID->SetTextureParameterValue(TEXT("TextureRT"), RenderTargetTexture);
			MIDs.Add(MID);
		}
	}
	else
	{
		MIDs.Empty();
		StaticMeshComponent->OverrideMaterials.Empty();
	}
}

void ABaseRenderSurface::EnableRender(bool bEnable)
{
	if (bEnable)
	{
		bRenderEnabled = true;
		InitSceneCapture();
	}
	else
	{
		bRenderEnabled = false;
	}
}

bool ABaseRenderSurface::CheckSCCNeedsToUpdate()
{
	bool bUpdate = false;

	if (WasRecentlyRendered(0.1f))
	{
		bool bUpdateByDistance = false;
		bool bUpdateByDirection = false;

		if (bUseUpdateDistance && MaxCaptureUpdateDistance > 0)
		{
			bUpdateByDistance = UPortalsFunctionLibrary::CheckVisibilityByDistance(this, MaxCaptureUpdateDistance, GetActorLocation());
			bUpdate = bUpdateByDistance;
		}

		if (bUseUpdateDirection)
		{
			bUpdateByDirection = UPortalsFunctionLibrary::CheckVisibilityByDirection(this, GetActorLocation(), GetActorForwardVector());
			bUpdate = bUpdateByDirection;
		}

		if (bUseUpdateDistance && bUseUpdateDirection)
		{
			bUpdate = bUpdateByDistance && bUpdateByDirection;
		}
	}

	return bUpdate;
}

void ABaseRenderSurface::UpdateSCC2DTransform() {}

#if WITH_EDITOR
void ABaseRenderSurface::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == TEXT("StaticMeshComponent")
		|| TEXT("MeshAsset") || TEXT("MaterialAsset")
		|| TEXT("bRT_UseViewportSize") || TEXT("RenderTargetResolution") || TEXT("RenderTargetFormat")
		|| TEXT("bUseUpdateDistance") || TEXT("MaxCaptureUpdateDistance") || TEXT("bUseUpdateDirection"))
	{
		RenderTargetResolution.X = FMath::TruncToInt(RenderTargetResolution.X);
		RenderTargetResolution.Y = FMath::TruncToInt(RenderTargetResolution.Y);
		InitSceneCapture();
	}
}
#endif
