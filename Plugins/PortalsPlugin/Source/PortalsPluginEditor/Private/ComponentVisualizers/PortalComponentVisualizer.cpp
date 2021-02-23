// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ComponentVisualizers/PortalComponentVisualizer.h"
#include "SceneManagement.h"
#include "Components/PortalComponent.h"
#include "Actors/PortalActor.h"

void FPortalComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	if (const UPortalComponent* PortalComponent = Cast<const UPortalComponent>(Component))
	{
		if (const APortalActor* PortalActor = Cast<APortalActor>(PortalComponent->GetOwner()))
		{
			const FVector SrcLoc = PortalActor->GetActorLocation();
			const FVector TrgLoc = PortalActor->TargetPortal->GetActorLocation();
			DrawTargetConnection(PDI, SrcLoc, TrgLoc, FColor(255, 0, 255, 255));
		}
	}
}

void FPortalComponentVisualizer::DrawTargetConnection(class FPrimitiveDrawInterface* PDI, const FVector& SourceLocation, const FVector& TargetLocation, const FLinearColor& Color, float Thickness, uint8 DepthPriority, float DepthBias, bool bScreenSpace)
{
	PDI->DrawLine(SourceLocation, TargetLocation, Color, DepthPriority, Thickness, DepthBias, bScreenSpace);
}
