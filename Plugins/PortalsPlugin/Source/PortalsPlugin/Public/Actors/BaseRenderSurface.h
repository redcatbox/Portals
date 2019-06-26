// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "Objects/PortalsFunctionLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "BaseRenderSurface.generated.h"

UCLASS(Abstract)
class PORTALSPLUGIN_API ABaseRenderSurface : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseRenderSurface();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USceneComponent* SceneSCC;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMesh* MeshAsset;

	UPROPERTY(EditAnywhere, Category = Mesh)
		UMaterialInterface* MaterialAsset;

	UPROPERTY()
		UStaticMesh* DefaultMesh;

	UPROPERTY()
		UMaterialInterface* DefaultMaterial;

	UPROPERTY()
		UMaterialInstanceDynamic* MID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USceneCaptureComponent2D* SceneCaptureComponent2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capture)
		bool bRenderEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capture)
		bool bRT_UseViewportSize;

	UPROPERTY()
		UTextureRenderTarget2D* RenderTargetTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capture)
		FVector2D RenderTargetResolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capture)
		TEnumAsByte<ETextureRenderTargetFormat> RenderTargetFormat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capture)
		bool bUseUpdateDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capture)
		float MaxCaptureUpdateDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Capture)
		bool bUseUpdateDirection;

	UFUNCTION(BlueprintCallable)
		virtual void AdjustValues();

	UFUNCTION(BlueprintCallable)
		virtual void InitSceneCapture();

	UFUNCTION(BlueprintCallable)
		virtual void EnableRender();

	UFUNCTION(BlueprintCallable)
		virtual bool CheckSCCNeedsToUpdate();

	UFUNCTION(BlueprintCallable)
		virtual void UpdateSCC2DTransform();

	//Override PostEditChangeProperty
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};