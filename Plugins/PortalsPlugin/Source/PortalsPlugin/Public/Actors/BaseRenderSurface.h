// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "UObject/NoExportTypes.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UObject/SoftObjectPtr.h"
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

	UPROPERTY(EditAnywhere, Category = Material)
	TSoftObjectPtr<UMaterial> RenderMaterial;

	UPROPERTY(EditAnywhere, Category = Material)
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

	UPROPERTY()
	bool bShouldClearRT;

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
