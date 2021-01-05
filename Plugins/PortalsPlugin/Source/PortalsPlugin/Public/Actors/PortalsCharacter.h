// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PortalsCharacter.generated.h"

UCLASS()
class PORTALSPLUGIN_API APortalsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void Teleport();
};
