// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/ScreenActor.h"

AScreenActor::AScreenActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraPreview = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraPreview->SetupAttachment(SceneCaptureComponent2D);

	bUseCaptureInterval = false;
	CaptureInterval = 1.f;
}

void AScreenActor::BeginPlay()
{
	Super::BeginPlay();

	if (bRenderEnabled)
	{
		EnableRender(bRenderEnabled);
	}
}

void AScreenActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRenderEnabled)
	{
		if (CheckSCCNeedsToUpdate())
		{
			if (bUseCaptureInterval)
			{
				GetWorldTimerManager().UnPauseTimer(TH_CaptureScene);
			}
			else
			{
				SceneCaptureComponent2D->CaptureScene();
			}
		}
		else
		{
			GetWorldTimerManager().PauseTimer(TH_CaptureScene);
		}
	}
}

void AScreenActor::EnableRender(bool bEnable)
{
	Super::EnableRender(bEnable);

	if (bEnable && bUseCaptureInterval)
	{
		FTimerDelegate TD_CaptureScene;
		TD_CaptureScene.BindUFunction(SceneCaptureComponent2D, FName("CaptureScene"));
		GetWorldTimerManager().SetTimer(TH_CaptureScene, TD_CaptureScene, CaptureInterval, true);
		GetWorldTimerManager().PauseTimer(TH_CaptureScene);
	}
}

#if WITH_EDITOR
void AScreenActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == TEXT("bUseCaptureInterval") || TEXT("CaptureInterval"))
	{
		CaptureInterval = FMath::Clamp(CaptureInterval, 0.001f, CaptureInterval);
	}
}
#endif
