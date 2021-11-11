// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "BaseRenderSurface.generated.h"

UCLASS(Abstract)
class PORTALSPLUGIN_API ABaseRenderSurface : public AActor
{
	GENERATED_BODY()

public:
	ABaseRenderSurface();

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = MID)
	FName RenderTargetParameterName;

protected:
	UPROPERTY()
	UMaterialInstanceDynamic* MID;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SceneCapture)
	USceneComponent* SceneCaptureRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SceneCapture)
	USceneCaptureComponent2D* SceneCaptureComponent2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SceneCapture)
	bool bRenderEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SceneCapture)
	bool bRenderTargetEqualsViewportSize;

protected:
	UPROPERTY()
	UTextureRenderTarget2D* RenderTargetTexture;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SceneCapture)
	FIntPoint RenderTargetResolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SceneCapture)
	TEnumAsByte<ETextureRenderTargetFormat> RenderTargetFormat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SceneCapture)
	bool bUseUpdateDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SceneCapture)
	float MaxCaptureUpdateDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SceneCapture)
	bool bUseUpdateDirection;

	UFUNCTION(BlueprintCallable, Category = SceneCapture)
	virtual void EnableRender(bool bEnable);

	UFUNCTION(BlueprintCallable)
	virtual bool CheckSCCNeedsToUpdate();

	UFUNCTION(BlueprintCallable)
	virtual void UpdateSCC2DTransform();

//#if WITH_EDITOR
//	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
//#endif
};
