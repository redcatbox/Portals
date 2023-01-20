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

	UPROPERTY(EditDefaultsOnly, NonTransactional, Category = Portal)
	class UPortalComponent* PortalComponent;

	UPROPERTY(EditDefaultsOnly, NonTransactional, Category = BoxCollision)
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoxCollision)
	FVector BoxExtent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = TargetPortal)
	AActor* TargetPortal;

	UPROPERTY(BlueprintReadWrite)
	FVector DestinationPoint;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void EditorApplyScale(const FVector& DeltaScale, const FVector* PivotLocation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	virtual void EditorApplyMirror(const FVector& MirrorScale, const FVector& PivotLocation) override;
#endif

protected:
	UPROPERTY()
	class UProceduralMeshComponent* ProceduralMesh;
};
