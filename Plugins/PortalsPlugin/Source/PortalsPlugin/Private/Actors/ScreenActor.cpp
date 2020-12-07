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
		EnableRender();
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
				UKismetSystemLibrary::K2_UnPauseTimer(SceneCaptureComponent2D, FString(TEXT("CaptureScene")));
			}
			else
			{
				SceneCaptureComponent2D->CaptureScene();
			}
		}
		else
		{
			UKismetSystemLibrary::K2_PauseTimer(SceneCaptureComponent2D, FString(TEXT("CaptureScene")));
		}
	}
}

void AScreenActor::EnableRender()
{
	Super::EnableRender();

	if (bUseCaptureInterval)
	{
		UKismetSystemLibrary::K2_SetTimer(SceneCaptureComponent2D, FString(TEXT("CaptureScene")), CaptureInterval, true);
		UKismetSystemLibrary::K2_PauseTimer(SceneCaptureComponent2D, FString(TEXT("CaptureScene")));
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
		InitSceneCapture();
	}
}
#endif
