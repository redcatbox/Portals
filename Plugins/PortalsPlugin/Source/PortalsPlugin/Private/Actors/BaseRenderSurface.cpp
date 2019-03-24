// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseRenderSurface.h"

ABaseRenderSurface::ABaseRenderSurface()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/PortalsPlugin/Dev/Meshes/SM_1UnitPlane.SM_1UnitPlane"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/PortalsPlugin/Dev/Materials/Screens/M_ScreenBase.M_ScreenBase"));
	DefaultMesh = MeshObj.Object;
	DefaultMaterial = MaterialObj.Object;
	MeshAsset = DefaultMesh;
	MaterialAsset = DefaultMaterial;
	//Default assets

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetStaticMesh(DefaultMesh);
	StaticMeshComponent->SetMaterial(0, DefaultMaterial);
	//StaticMeshComponent->SetRelativeScale3D(FVector(1.f, 100.f, 100.f));

	bRenderEnabled = true;
	bRT_UseViewportSize = false;
	RenderTargetTexture = nullptr;
	RenderTargetResolution = FVector2D(256.f, 256.f);
	RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA16f;

	MID = nullptr;

	bUseUpdateDistance = true;
	MaxCaptureUpdateDistance = 5000.f;
	bUseUpdateDirection = true;
}

// Called when the game starts or when spawned
void ABaseRenderSurface::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseRenderSurface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseRenderSurface::AdjustValues()
{
	RenderTargetResolution.X = FMath::TruncToInt(RenderTargetResolution.X);
	RenderTargetResolution.Y = FMath::TruncToInt(RenderTargetResolution.Y);
}

void ABaseRenderSurface::InitSceneCapture()
{
	if (bRT_UseViewportSize)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
		if (World && World->IsGameWorld())
		{
			if (UGameViewportClient* ViewportClient = World->GetGameViewport())
			{
				ViewportClient->GetViewportSize(RenderTargetResolution);
			}
		}
	}

	RenderTargetTexture = UKismetRenderingLibrary::CreateRenderTarget2D(this, RenderTargetResolution.X, RenderTargetResolution.Y, RenderTargetFormat);
	SceneCaptureComponent2D->TextureTarget = RenderTargetTexture;

	if (::IsValid(MeshAsset))
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset);
	}
	else
	{
		MeshAsset = DefaultMesh;
		StaticMeshComponent->SetStaticMesh(DefaultMesh);
	}

	if (::IsValid(MaterialAsset))
	{
		MID = StaticMeshComponent->CreateDynamicMaterialInstance(0, MaterialAsset);
		MID->UMaterialInstanceDynamic::SetTextureParameterValue(TEXT("TextureRT"), RenderTargetTexture);
		MID->SetScalarParameterValue(TEXT("Param"), 0.f);
	}
	else
	{
		StaticMeshComponent->SetMaterial(0, DefaultMaterial);
		MID = nullptr;
	}
}

void ABaseRenderSurface::EnableRender()
{
	bRenderEnabled = true;
	InitSceneCapture();
}

bool ABaseRenderSurface::CheckSCCNeedsToUpdate()
{
	//UE_LOG(LogTemp, Log, TEXT("Update"));
	bool bUpdate = false;

	if (WasRecentlyRendered(0.1f))
	{
		bool bUpdateByDistance = false;
		bool bUpdateByDirection = false;
		int32 SwitchState = 0;

		if (bUseUpdateDistance && MaxCaptureUpdateDistance > 0)
		{

			bUpdateByDistance = UPortalsFunctionLibrary::CheckVisibilityByDistance(this, MaxCaptureUpdateDistance, GetActorLocation());
			SwitchState = 1;
		}

		if (bUseUpdateDirection)
		{
			bUpdateByDirection = UPortalsFunctionLibrary::CheckVisibilityByDirection(this, GetActorLocation(), GetActorForwardVector());
			SwitchState = 2;
		}

		if (bUseUpdateDistance && bUseUpdateDirection)
		{
			SwitchState = 3;
		}

		switch (SwitchState)
		{
		case 1: bUpdate = bUpdateByDistance;
			break;
		case 2: bUpdate = bUpdateByDirection;
			break;
		case 3: bUpdate = (bUpdateByDistance && bUpdateByDirection);
			break;
		default: bUpdate = true;
		}
	}

	return bUpdate;
}

void ABaseRenderSurface::UpdateSCC2DTransform() {}

// Update with changed property
#if WITH_EDITOR
void ABaseRenderSurface::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == TEXT("StaticMeshComponent") || TEXT("MeshAsset") || TEXT("MaterialAsset")
		|| TEXT("bRT_UseViewportSize") || TEXT("RenderTargetResolution") || TEXT("RenderTargetFormat") ||
		TEXT("bUseUpdateDistance") || TEXT("MaxCaptureUpdateDistance") || TEXT("bUseUpdateDirection"))
	{
		AdjustValues();
		InitSceneCapture();
	}
}
#endif