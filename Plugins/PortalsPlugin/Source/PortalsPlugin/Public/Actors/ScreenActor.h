// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseRenderSurface.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ScreenActor.generated.h"

UCLASS()
class PORTALSPLUGIN_API AScreenActor : public ABaseRenderSurface
{
	GENERATED_BODY()

public:
	AScreenActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void EnableRender() override;

	UPROPERTY(EditDefaultsOnly)
		UCameraComponent* CameraPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SceneCapture)
		bool bUseCaptureInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SceneCapture)
		float CaptureInterval;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};