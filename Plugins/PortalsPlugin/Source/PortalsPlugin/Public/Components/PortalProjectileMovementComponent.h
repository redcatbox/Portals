// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "PortalProjectileMovementComponent.generated.h"

/**
 * Projectile that can move through portals
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTALSPLUGIN_API UPortalProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
