// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/BaseRenderSurface.h"
#include "PortalsPlugin.h"
#include "Objects/PortalFunctionLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Engine/StreamableManager.h"

ABaseRenderSurface::ABaseRenderSurface()
{
	PrimaryActorTick.bCanEverTick = false;
	//PrimaryActorTick.TickGroup = ETickingGroup::TG_PostUpdateWork;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	DefaultSceneRoot->Mobility = EComponentMobility::Static;
	DefaultSceneRoot->bVisualizeComponent = true;

	SceneCaptureRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneCaptureRoot"));
	SceneCaptureRoot->SetupAttachment(RootComponent);

	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
	SceneCaptureComponent2D->SetupAttachment(SceneCaptureRoot);
	SceneCaptureComponent2D->bCaptureEveryFrame = false;
	SceneCaptureComponent2D->bCaptureOnMovement = false;
	SceneCaptureComponent2D->bAutoActivate = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	bRenderEnabled = true;
	bRenderTargetEqualsViewportSize = true;
	RenderTargetResolution = FIntPoint(128);
	RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA16f;

	RenderTargetParameterName = FName(TEXT("TextureRT"));

	bUseUpdateDistance = true;
	MaxCaptureUpdateDistance = 1000.f;
	bUseUpdateDirection = true;
}

void ABaseRenderSurface::EnableRender(bool bEnable)
{
	bRenderEnabled = bEnable;

	if (!StaticMeshComponent->GetStaticMesh())
	{
		UE_LOG(LogPortals, Warning, TEXT("Static mesh is not valid!"));
		UE_LOG(LogPortals, Warning, TEXT("Can't enable render."));
		bRenderEnabled = false;
	}

	RenderMaterial.LoadSynchronous();
	if (!RenderMaterial.IsValid())
	{
		UE_LOG(LogPortals, Warning, TEXT("Render material is not valid!"));
		UE_LOG(LogPortals, Warning, TEXT("Can't enable render."));
		bRenderEnabled = false;
	}

	if (bRenderEnabled)
	{
		if (bRenderTargetEqualsViewportSize)
		{
			if (GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport)
			{
				const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
				if (ViewportSize.X > 0 && ViewportSize.Y > 0)
				{
					RenderTargetResolution = FIntPoint(ViewportSize.X, ViewportSize.Y);
				}
			}
		}

		RenderTargetTexture = UKismetRenderingLibrary::CreateRenderTarget2D(this, RenderTargetResolution.X, RenderTargetResolution.Y, RenderTargetFormat);
		SceneCaptureComponent2D->TextureTarget = RenderTargetTexture;

		MID = StaticMeshComponent->CreateDynamicMaterialInstance(0, RenderMaterial.Get());
		MID->SetTextureParameterValue(RenderTargetParameterName, RenderTargetTexture);
	}
	else
	{
		StaticMeshComponent->OverrideMaterials.Empty();
		RenderTargetTexture = nullptr;
		MID = nullptr;
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
			bUpdateByDistance = UPortalFunctionLibrary::CheckVisibilityByDistance(this, MaxCaptureUpdateDistance, GetActorLocation());
			bUpdate = bUpdateByDistance;
		}

		if (bUseUpdateDirection)
		{
			bUpdateByDirection = UPortalFunctionLibrary::CheckVisibilityByDirection(this, GetActorLocation(), GetActorForwardVector());
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

//#if WITH_EDITOR
//void ABaseRenderSurface::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
//{
//	Super::PostEditChangeProperty(PropertyChangedEvent);
//	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
//	if (PropertyName == TEXT("RenderMaterial"))
//	{}
//}
//#endif
