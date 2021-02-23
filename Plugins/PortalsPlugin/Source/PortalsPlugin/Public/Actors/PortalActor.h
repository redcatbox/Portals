// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseRenderSurface.h"
#include "PortalActor.generated.h"

class UPortalComponent;

UCLASS()
class PORTALSPLUGIN_API APortalActor : public ABaseRenderSurface
{
	GENERATED_BODY()

public:
	APortalActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void UpdateSCC2DTransform() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	bool bUseInnerReplacement;

	UPROPERTY(EditDefaultsOnly, NonTransactional, Category = Portal)
	UPortalComponent* PortalComponent;

	UPROPERTY(EditDefaultsOnly, NonTransactional, Category = BoxCollision)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoxCollision)
	FVector BoxExtent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = TargetPortal)
	AActor* TargetPortal;

	UPROPERTY(BlueprintReadWrite)
	FVector DestinationPoint;

	UFUNCTION(BlueprintCallable)
	virtual void UpdateReplacementRenderParams();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void EditorApplyScale(const FVector& DeltaScale, const FVector* PivotLocation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	virtual void EditorApplyMirror(const FVector& MirrorScale, const FVector& PivotLocation) override;
#endif
};
