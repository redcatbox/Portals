// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseRenderSurface.h"
#include "MirrorActor.generated.h"

UCLASS()
class PORTALSPLUGIN_API AMirrorActor : public ABaseRenderSurface
{
	GENERATED_BODY()

public:
	AMirrorActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void UpdateSCC2DTransform() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
