// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseRenderSurface.h"
#include "PortalActor.generated.h"

UCLASS()
class PORTALSPLUGIN_API APortalActor : public ABaseRenderSurface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APortalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void AdjustValues() override;
	virtual void UpdateSCC2DTransform() override;

	UPROPERTY(EditAnywhere, meta = (Category = "Portal"))
		FVector PortalSurfaceSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Portal"))
		bool bUseInnerReplacement;

	UPROPERTY(EditDefaultsOnly, NonTransactional)
		UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="BoxCollision"))
		FVector BoxExtent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (Category = "TargetPortal"))
		AActor* TargetPortal;

	UPROPERTY()
		UArrowComponent* ArrowComponent;

	UPROPERTY(BlueprintReadWrite)
		FVector DestinationPoint;

	UFUNCTION(BlueprintCallable)
		virtual void UpdateReplacementRenderParams();

	UFUNCTION(BlueprintCallable)
		virtual void UpdateArrowPointer();

	//Override PostEditChangeProperty
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
