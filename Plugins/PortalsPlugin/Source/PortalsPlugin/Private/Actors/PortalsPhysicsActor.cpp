// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/PortalsPhysicsActor.h"

APortalsPhysicsActor::APortalsPhysicsActor()
{
	PrimaryActorTick.bCanEverTick = true;

	GetStaticMeshComponent()->SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetCollisionProfileName(FName(TEXT("PhysicsActor")));
	GetStaticMeshComponent()->BodyInstance.bNotifyRigidBodyCollision = true;
	GetStaticMeshComponent()->BodyInstance.bSimulatePhysics = true;

	StaticMeshComponentCopy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentCopy"));
	StaticMeshComponentCopy->BodyInstance.SetCollisionProfileName(FName(TEXT("NoCollision")));
	StaticMeshComponentCopy->SetVisibility(false);

	OverlappingPortal = nullptr;
	TeleportationVelocityBefore = FVector::ZeroVector;
	TeleportationVelocityAfter = FVector::ZeroVector;
	bIsHeld = false;
	ProjectedDistance = 0.f;

	// Dynamic material instance
	MIParamNameUseClipPlane = FName(TEXT("UseClipPlane"));
	MIParamNameClipPlaneBase = FName(TEXT("ClipPlaneBase"));
	MIParamNameClipPlaneNormal = FName(TEXT("ClipPlaneNormal"));
}

void APortalsPhysicsActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetStaticMeshComponent() && GetStaticMeshComponent()->GetStaticMesh())
	{
		for (int32 i = 0; i < GetStaticMeshComponent()->GetNumMaterials(); ++i)
		{
			MIDs.Add(GetStaticMeshComponent()->CreateDynamicMaterialInstance(i, GetStaticMeshComponent()->GetMaterials()[i]));
		}

		if (StaticMeshComponentCopy)
		{
			StaticMeshComponentCopy->SetStaticMesh(GetStaticMeshComponent()->GetStaticMesh());
			for (int32 i = 0; i < MIDs.Num(); ++i)
			{
				UMaterialInstanceDynamic* MID = DuplicateObject<UMaterialInstanceDynamic>(MIDs[i], this);
				MIDsCopy.Add(MID);
				StaticMeshComponentCopy->SetMaterial(i, MID);
			}
		}
	}
}

void APortalsPhysicsActor::BeginPlay()
{
	Super::BeginPlay();
}

void APortalsPhysicsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OverlappingPortal)
	{
		TeleportationVisualization();
	}
}

void APortalsPhysicsActor::UpdateComponentsTransforms()
{

}

void APortalsPhysicsActor::TeleportationVisualization()
{
	UpdateComponentsTransforms();
}

void APortalsPhysicsActor::Teleportation()
{

}
