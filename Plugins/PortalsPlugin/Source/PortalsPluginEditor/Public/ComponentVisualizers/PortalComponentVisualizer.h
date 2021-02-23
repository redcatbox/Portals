// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"

class FPrimitiveDrawInterface;
class FSceneView;

class PORTALSPLUGINEDITOR_API FPortalComponentVisualizer : public FComponentVisualizer
{
public:
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;

	static void DrawTargetConnection(class FPrimitiveDrawInterface* PDI, const FVector& SourceLocation, const FVector& TargetLocation, const FLinearColor& Color, float Thickness = 1.0f, uint8 DepthPriority = SDPG_World, float DepthBias = 0.0f, bool bScreenSpace = false);
};
