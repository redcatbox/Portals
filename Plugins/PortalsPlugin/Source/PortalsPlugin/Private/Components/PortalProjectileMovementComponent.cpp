// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PortalProjectileMovementComponent.h"
#include "Objects/PortalFunctionLibrary.h"

void UPortalProjectileMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
