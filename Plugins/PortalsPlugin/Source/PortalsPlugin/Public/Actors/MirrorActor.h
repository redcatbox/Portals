// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseRenderSurface.h"
#include "MirrorActor.generated.h"

UCLASS()
class PORTALSPLUGIN_API AMirrorActor : public ABaseRenderSurface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMirrorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UpdateSCC2DTransform() override;

	//Override PostEditChangeProperty
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
