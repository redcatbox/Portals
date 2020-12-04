// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "PortalsPhysicsActor.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class UStaticMesh;
class UMaterialInterface;
class APortalActor;

UCLASS()
class PORTALSPLUGIN_API APortalsPhysicsActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	APortalsPhysicsActor();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Teleportation)
		virtual void UpdateComponentsTransforms();

	UFUNCTION(BlueprintCallable, Category = Teleportation)
		virtual void TeleportationVisualization();

	UFUNCTION(BlueprintCallable, Category = Teleportation)
		virtual void Teleportation();

	static FName MIParamNameUseClipPlane;
	static FName MIParamNameClipPlaneBase;
	static FName MIParamNameClipPlaneNormal;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
		UStaticMeshComponent* StaticMeshComponentCopy;

	UPROPERTY()
		TArray<UMaterialInstanceDynamic*> MIDs;

	UPROPERTY()
		TArray<UMaterialInstanceDynamic*> MIDsCopy;

	UPROPERTY()
		APortalActor* OverlappingPortal;

	UPROPERTY()
		FVector TeleportationVelocityBefore;

	UPROPERTY()
		FVector TeleportationVelocityAfter;

	UPROPERTY()
		bool bIsHeld;

	UPROPERTY()
		float ProjectedDistance;
};
