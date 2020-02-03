// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class UStaticMesh;
class UMaterialInterface;
#include "PortalsPhysicsActor.generated.h"

/**
*
*/
UCLASS()
class PORTALSPLUGIN_API APortalsPhysicsActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APortalsPhysicsActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

/*
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="StaticMesh"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="StaticMeshCopy"))
	UStaticMeshComponent* StaticMeshCopy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="MID1", Category="Default", OverrideNativeName="MID1"))
	UMaterialInstanceDynamic* MID1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="MID2", Category="Default", OverrideNativeName="MID2"))
	UMaterialInstanceDynamic* MID2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Mesh Asset", Category="Default", OverrideNativeName="MeshAsset"))
	UStaticMesh* MeshAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Material Asset", Category="Default", OverrideNativeName="MaterialAsset"))
	UMaterialInterface* MaterialAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Current Portal", Category="Teleportation", OverrideNativeName="CurrentPortal"))
	ABP_Portal_C3609834151* CurrentPortal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Is Overlapping Portal", Category="Teleportation", OverrideNativeName="IsOverlappingPortal"))
	bool IsOverlappingPortal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Velocity Prev", Category="KineticEnergy", OverrideNativeName="VelocityPrev"))
	FVector VelocityPrev;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Velocity New", Category="KineticEnergy", OverrideNativeName="VelocityNew"))
	FVector VelocityNew;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Is Held", Category="Default", OverrideNativeName="IsHeld"))
	bool IsHeld;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Projected Distance", Category="Teleportation", OverrideNativeName="ProjectedDistance"))
	float ProjectedDistance;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_OverlappedComponent1"))
	UPrimitiveComponent* ComponentBoundEvent_OverlappedComponent1;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_OtherActor1"))
	AActor* ComponentBoundEvent_OtherActor1;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_OtherComp1"))
	UPrimitiveComponent* ComponentBoundEvent_OtherComp1;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_OtherBodyIndex1"))
	int32 ComponentBoundEvent_OtherBodyIndex1;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_DynamicCast_AsBP_Portal"))
	ABP_Portal_C3609834151* DynamicCast_AsBP_Portal;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_DynamicCast_bSuccess"))
	bool DynamicCast_bSuccess;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_OverlappedComponent"))
	UPrimitiveComponent* ComponentBoundEvent_OverlappedComponent;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_OtherActor"))
	AActor* ComponentBoundEvent_OtherActor;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_OtherComp"))
	UPrimitiveComponent* ComponentBoundEvent_OtherComp;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_OtherBodyIndex"))
	int32 ComponentBoundEvent_OtherBodyIndex;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_bFromSweep"))
	bool ComponentBoundEvent_bFromSweep;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_SweepResult"))
	FHitResult ComponentBoundEvent_SweepResult;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_Event_DeltaSeconds"))
	float Event_DeltaSeconds;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_DynamicCast_AsBP_Portal1"))
	ABP_Portal_C3609834151* DynamicCast_AsBP_Portal1;

	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_DynamicCast_bSuccess1"))
	bool DynamicCast_bSuccess1;


	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	static void __CustomDynamicClassInitialization(UDynamicClass* InDynamicClass);
	static void __StaticDependenciesAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	static void __StaticDependencies_DirectlyUsedAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	void ExecuteUbergraph_BP_PhysActor_0(int32 EntryPoint);
	void ExecuteUbergraph_BP_PhysActor_1(int32 EntryPoint);
	void ExecuteUbergraph_BP_PhysActor_2(int32 EntryPoint);
	
	UFUNCTION(meta=(DisplayName="Tick", ToolTip="Event called every frame", CppFromBpEvent, OverrideNativeName="ReceiveTick"))
	void ReceiveTick(float DeltaSeconds);
	
	UFUNCTION(meta=(OverrideNativeName="BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature"))
	virtual void BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, FHitResult const& SweepResult__const);
	
	UFUNCTION(meta=(OverrideNativeName="BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_6_ComponentEndOverlapSignature__DelegateSignature"))
	virtual void BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_6_ComponentEndOverlapSignature__DelegateSignature(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", DisplayName="Construction Script", ToolTip="Construction script, the place to spawn components and do other setup.@note Name used in CreateBlueprint function@param       Location        The location.@param       Rotation        The rotation.", Category, CppFromBpEvent, OverrideNativeName="UserConstructionScript"))
	void UserConstructionScript();

	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="ToggleComponent"))
	virtual void ToggleComponent(UPrimitiveComponent* Component, bool On);

	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="UpdateComponents"))
	virtual void UpdateComponents();

	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="TeleportationVisualization"))
	virtual void TeleportationVisualization();

	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Teleportation"))
	virtual void Teleportation();*/
};
