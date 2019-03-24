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
	// Sets default values for this actor's properties
	AScreenActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void AdjustValues() override;
	virtual void EnableRender() override;

	UPROPERTY(EditDefaultsOnly)
		UCameraComponent* CameraPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Capture"))
		bool bUseCaptureInterval;

	UPROPERTY(EditAnywhere, meta=(Category="Capture"))
		float CaptureInterval;

	//Override PostEditChangeProperty
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};