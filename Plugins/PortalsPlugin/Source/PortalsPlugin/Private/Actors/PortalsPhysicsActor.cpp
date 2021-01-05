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

	// MI params names
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

//void APortalsPhysicsActor::ExecuteUbergraph_BP_PhysActor_0(int32 bpp__EntryPoint)
//{

//	CurrentPortal = b0l__K2Node_DynamicCast_AsBP_Portal1;
//	IsOverlappingPortal = true;
//	ToggleComponent(StaticMeshCopy, true);
//	if(::IsValid(CurrentPortal))
//	{
//		CuentPortal->TargetPortal->ToggleFrameCollision(ECollisionEnabled::NoCollision);
//	}rrentPortal->ToggleFrameCollision(ECollisionEnabled::NoCollision);
//	}
//	if(::IsValid(CurrentPortal) && ::IsValid(CurrentPortal->TargetPortal))
//	{
//		Curr
//	if(::IsValid(MID1))
//	{
//		MID->UMaterialInstanceDynamic::SetScalarParameterValue(FName(TEXT("UseClipPlane")), 1.f);
//	}
//	if(::IsValid(MID2))
//	{
//		MIDCopy->UMaterialInstanceDynamic::SetScalarParameterValue(FName(TEXT("UseClipPlane")), 1.f);
//	}
//	return;
//}


//void APortalsPhysicsActor::ExecuteUbergraph_BP_PhysActor_2(int32 bpp__EntryPoint)
//{

//	IsOverlappingPortal = false;
//	ToggleComponent(StaticMeshCopy, false);

//	if(::IsValid(CurrentPortal))
//	{
//		CurrentPortal->ToggleFrameCollision(ECollisionEnabled::NoCollision);
//	}
//	if(::IsValid(CurrentPortal) && ::IsValid(CurrentPortal->TargetPortal))
//	{
//		CurrentPortal->TargetPortal->ToggleFrameCollision(ECollisionEnabled::NoCollision);
//	}

//	if(MID)
//	{
//		MID->UMaterialInstanceDynamic::SetScalarParameterValue(FName(TEXT("UseClipPlane")), 0.f);
//	}

//	if(MIDCopy)
//	{
//		MIDCopy->UMaterialInstanceDynamic::SetScalarParameterValue(FName(TEXT("UseClipPlane")), 0.f);
//	}

//	CurrentPortal = ((ABP_Portal_C3609834151*)nullptr);

//}

void APortalsPhysicsActor::UpdateComponentsTransforms()
{
	//				if(::IsValid(CurrentPortal))
	//				{
	//					K2_GetActorLocation_ReturnValue1 = CurrentPortal->GetActorLocation();
	//				}
	//				Conv_VectorToLinearColor_ReturnValue3 = UKismetMathLibrary::Conv_VectorToLinearColor(K2_GetActorLocation_ReturnValue1);
	//				if(::IsValid(MID))
	//				{
	//					MID1->UMaterialInstanceDynamic::SetVectorParameterValue(FName(TEXT("ClipPlaneBase")), Conv_VectorToLinearColor_ReturnValue3);
	//				}

	//				if(::IsValid(CurrentPortal))
	//				{
	//					GetActorForwardVector_ReturnValue1 = CurrentPortal->AActor::GetActorForwardVector();
	//				}
	//				Conv_VectorToLinearColor_ReturnValue2 = UKismetMathLibrary::Conv_VectorToLinearColor(GetActorForwardVector_ReturnValue1);
	//				if(::IsValid(MID1))
	//				{
	//					MID1->UMaterialInstanceDynamic::SetVectorParameterValue(FName(TEXT("ClipPlaneNormal")), Conv_VectorToLinearColor_ReturnValue2);
	//				}
	//			}
	//		case 3:
	//			{
	//				if(::IsValid(StaticMesh))
	//				{
	//					K2_GetComponentLocation_ReturnValue = StaticMesh->USceneComponent::K2_GetComponentLocation();
	//				}
	//				ABP_Portal_C3609834151*  __Local__7 = ((ABP_Portal_C3609834151*)nullptr);
	//				UBP_PortalsFunctions_C3748030278::PortalConvertLocation(CurrentPortal, ((::IsValid(CurrentPortal)) ? (CurrentPortal->TargetPortal) : (__Local__7)), K2_GetComponentLocation_ReturnValue, this, /*out*/ PortalConvertLocation_NewLocation);
	//			}
	//		case 4:
	//			{
	//				if(::IsValid(StaticMeshCopy))
	//				{
	//					StaticMeshCopy->USceneComponent::K2_SetWorldLocation(PortalConvertLocation_NewLocation, false, /*out*/ K2_SetWorldLocation_SweepHitResult, false);
	//				}
	//			}
	//		case 5:
	//			{
	//				if(::IsValid(StaticMesh))
	//				{
	//					K2_GetComponentRotation_ReturnValue = StaticMesh->USceneComponent::K2_GetComponentRotation();
	//				}
	//				ABP_Portal_C3609834151*  __Local__8 = ((ABP_Portal_C3609834151*)nullptr);
	//				UBP_PortalsFunctions_C3748030278::PortalConvertRotation(CurrentPortal, ((::IsValid(CurrentPortal)) ? (CurrentPortal->TargetPortal) : (__Local__8)), K2_GetComponentRotation_ReturnValue, this, /*out*/ PortalConvertRotation_NewRotation);
	//			}
	//		case 6:
	//			{
	//				if(::IsValid(StaticMeshCopy))
	//				{
	//					StaticMeshCopy->USceneComponent::K2_SetWorldRotation(PortalConvertRotation_NewRotation, false, /*out*/ K2_SetWorldRotation_SweepHitResult, false);
	//				}
	//			}
	//		case 7:
	//			{
	//				if(::IsValid(CurrentPortal))
	//				{
	//					GetActorScale3D_ReturnValue1 = CurrentPortal->AActor::GetActorScale3D();
	//				}
	//				if(::IsValid(CurrentPortal) && ::IsValid(CurrentPortal->TargetPortal))
	//				{
	//					GetActorScale3D_ReturnValue3 = CurrentPortal->TargetPortal->AActor::GetActorScale3D();
	//				}
	//				EqualEqual_VectorVector_ReturnValue = UKismetMathLibrary::EqualEqual_VectorVector(GetActorScale3D_ReturnValue1, GetActorScale3D_ReturnValue3, 0.000100);
	//				if (!EqualEqual_VectorVector_ReturnValue)
	//				{
	//					__CurrentState = 10;
	//					break;
	//				}
	//			}
	//		case 8:
	//			{
	//				if(::IsValid(CurrentPortal) && ::IsValid(CurrentPortal->TargetPortal))
	//				{
	//					K2_GetActorLocation_ReturnValue = CurrentPortal->TargetPortal->AActor::K2_GetActorLocation();
	//				}
	//				Conv_VectorToLinearColor_ReturnValue1 = UKismetMathLibrary::Conv_VectorToLinearColor(K2_GetActorLocation_ReturnValue);
	//				if(::IsValid(MID2))
	//				{
	//					MID2->UMaterialInstanceDynamic::SetVectorParameterValue(FName(TEXT("ClipPlaneBase")), Conv_VectorToLinearColor_ReturnValue1);
	//				}
	//			}
	//		case 9:
	//			{
	//				if(::IsValid(CurrentPortal) && ::IsValid(CurrentPortal->TargetPortal))
	//				{
	//					GetActorForwardVector_ReturnValue = CurrentPortal->TargetPortal->AActor::GetActorForwardVector();
	//				}
	//				Conv_VectorToLinearColor_ReturnValue = UKismetMathLibrary::Conv_VectorToLinearColor(GetActorForwardVector_ReturnValue);
	//				if(::IsValid(MID2))
	//				{
	//					MID2->UMaterialInstanceDynamic::SetVectorParameterValue(FName(TEXT("ClipPlaneNormal")), Conv_VectorToLinearColor_ReturnValue);
	//				}
	//				__CurrentState = -1;
	//				break;
	//			}
	//		case 10:
	//			{
	//				if(::IsValid(CurrentPortal))
	//				{
	//					GetActorScale3D_ReturnValue = CurrentPortal->AActor::GetActorScale3D();
	//				}
	//				if(::IsValid(CurrentPortal) && ::IsValid(CurrentPortal->TargetPortal))
	//				{
	//					GetActorScale3D_ReturnValue2 = CurrentPortal->TargetPortal->AActor::GetActorScale3D();
	//				}
	//				Divide_VectorVector_ReturnValue = UKismetMathLibrary::Divide_VectorVector(GetActorScale3D_ReturnValue2, GetActorScale3D_ReturnValue);
	//				if(::IsValid(StaticMeshCopy))
	//				{
	//					StaticMeshCopy->USceneComponent::SetWorldScale3D(Divide_VectorVector_ReturnValue);
	//				}
}

void APortalsPhysicsActor::TeleportationVisualization()
{
	UpdateComponentsTransforms();

	//				if(::IsValid(CurrentPortal))
	//				{
	//					GetActorForwardVector_ReturnValue = CurrentPortal->AActor::GetActorForwardVector();
	//				}
	//				if(::IsValid(CurrentPortal))
	//				{
	//					K2_GetActorLocation_ReturnValue = CurrentPortal->AActor::K2_GetActorLocation();
	//				}
	//				K2_GetActorLocation_ReturnValue1 = AActor::K2_GetActorLocation();
	//				ProjectPointOnToPlane_ReturnValue = UKismetMathLibrary::ProjectPointOnToPlane(K2_GetActorLocation_ReturnValue1, K2_GetActorLocation_ReturnValue, GetActorForwardVector_ReturnValue);
	//				Subtract_VectorVector_ReturnValue = UKismetMathLibrary::Subtract_VectorVector(K2_GetActorLocation_ReturnValue1, ProjectPointOnToPlane_ReturnValue);
	//				Dot_VectorVector_ReturnValue = UKismetMathLibrary::Dot_VectorVector(Subtract_VectorVector_ReturnValue, GetActorForwardVector_ReturnValue);
	//				ProjectedDistance = Dot_VectorVector_ReturnValue;
	//			}
	//		case 4:
	//			{
	//				Less_FloatFloat_ReturnValue = UKismetMathLibrary::Less_FloatFloat(ProjectedDistance, 0.000000);
	//				if (!Less_FloatFloat_ReturnValue)
	//				{
	//					__CurrentState = 2;
	//					break;
	//				}
	//			}
	//		case 5:
	//			{
	//				Teleportation();
	//				__CurrentState = -1;
	//				break;
	//			}
}

void APortalsPhysicsActor::Teleportation()
{
	//	FVector bpfv__TargetScale(EForceInit::ForceInit);
	//	FRotator bpfv__TargetRotation(EForceInit::ForceInit);
	//	FVector bpfv__TargetLocation(EForceInit::ForceInit);
	//	FVector GetActorScale3D_ReturnValue(EForceInit::ForceInit);
	//	FHitResult K2_SetWorldRotation_SweepHitResult{};
	//	FRotator K2_GetComponentRotation_ReturnValue(EForceInit::ForceInit);
	//	FVector GetActorScale3D_ReturnValue1(EForceInit::ForceInit);
	//	FHitResult K2_SetWorldLocation_SweepHitResult{};
	//	FVector Divide_VectorVector_ReturnValue(EForceInit::ForceInit);
	//	FVector K2_GetComponentLocation_ReturnValue(EForceInit::ForceInit);
	//	FRotator PortalConvertRotation_NewRotation(EForceInit::ForceInit);
	//	FVector PortalConvertLocationMirrored_NewLocation(EForceInit::ForceInit);
	//	FVector GetActorForwardVector_ReturnValue(EForceInit::ForceInit);
	//	FVector Multiply_VectorFloat_ReturnValue(EForceInit::ForceInit);
	//	bool EqualEqual_VectorVector_ReturnValue{};
	//	FVector Add_VectorVector_ReturnValue(EForceInit::ForceInit);
	//	FVector PortalConvertVelocity_NewVelocity(EForceInit::ForceInit);
	//	FVector GetPhysicsLinearVelocity_ReturnValue(EForceInit::ForceInit);
	//	int32 __CurrentState = 1;
	//	do
	//	{
	//		switch( __CurrentState )
	//		{
	//		case 1:
	//			{
	//				bpfv__TargetScale = FVector(1.000000,1.000000,1.000000);
	//			}
	//		case 2:
	//			{
	//				if(::IsValid(StaticMesh))
	//				{
	//					K2_GetComponentLocation_ReturnValue = StaticMesh->USceneComponent::K2_GetComponentLocation();
	//				}
	//				ABP_Portal_C3609834151*  __Local__9 = ((ABP_Portal_C3609834151*)nullptr);
	//				UBP_PortalsFunctions_C3748030278::PortalConvertLocationMirrored(CurrentPortal, ((::IsValid(CurrentPortal)) ? (CurrentPortal->TargetPortal) : (__Local__9)), K2_GetComponentLocation_ReturnValue, this, /*out*/ PortalConvertLocationMirrored_NewLocation);
	//			}
	//		case 3:
	//			{
	//				if(::IsValid(CurrentPortal) && ::IsValid(CurrentPortal->TargetPortal))
	//				{
	//					GetActorForwardVector_ReturnValue = CurrentPortal->TargetPortal->AActor::GetActorForwardVector();
	//				}
	//				Multiply_VectorFloat_ReturnValue = UKismetMathLibrary::Multiply_VectorFloat(GetActorForwardVector_ReturnValue, 10.000000);
	//				Add_VectorVector_ReturnValue = UKismetMathLibrary::Add_VectorVector(PortalConvertLocationMirrored_NewLocation, Multiply_VectorFloat_ReturnValue);
	//				bpfv__TargetLocation = Add_VectorVector_ReturnValue;
	//			}
	//		case 4:
	//			{
	//				if(::IsValid(StaticMesh))
	//				{
	//					StaticMesh->USceneComponent::K2_SetWorldLocation(bpfv__TargetLocation, false, /*out*/ K2_SetWorldLocation_SweepHitResult, true);
	//				}
	//			}
	//		case 5:
	//			{
	//				if(::IsValid(StaticMesh))
	//				{
	//					K2_GetComponentRotation_ReturnValue = StaticMesh->USceneComponent::K2_GetComponentRotation();
	//				}
	//				ABP_Portal_C3609834151*  __Local__10 = ((ABP_Portal_C3609834151*)nullptr);
	//				UBP_PortalsFunctions_C3748030278::PortalConvertRotation(CurrentPortal, ((::IsValid(CurrentPortal)) ? (CurrentPortal->TargetPortal) : (__Local__10)), K2_GetComponentRotation_ReturnValue, this, /*out*/ PortalConvertRotation_NewRotation);
	//			}
	//		case 6:
	//			{
	//				bpfv__TargetRotation = PortalConvertRotation_NewRotation;
	//			}
	//		case 7:
	//			{
	//				if(::IsValid(StaticMesh))
	//				{
	//					StaticMesh->USceneComponent::K2_SetWorldRotation(bpfv__TargetRotation, false, /*out*/ K2_SetWorldRotation_SweepHitResult, false);
	//				}
	//			}
	//		case 8:
	//			{
	//				if(::IsValid(CurrentPortal))
	//				{
	//					GetActorScale3D_ReturnValue = CurrentPortal->AActor::GetActorScale3D();
	//				}
	//				if(::IsValid(CurrentPortal) && ::IsValid(CurrentPortal->TargetPortal))
	//				{
	//					GetActorScale3D_ReturnValue1 = CurrentPortal->TargetPortal->AActor::GetActorScale3D();
	//				}
	//				Divide_VectorVector_ReturnValue = UKismetMathLibrary::Divide_VectorVector(GetActorScale3D_ReturnValue1, GetActorScale3D_ReturnValue);
	//				bpfv__TargetScale = Divide_VectorVector_ReturnValue;
	//			}
	//		case 9:
	//			{
	//				EqualEqual_VectorVector_ReturnValue = UKismetMathLibrary::EqualEqual_VectorVector(bpfv__TargetScale, FVector(1.000000,1.000000,1.000000), 0.000100);
	//				if (!EqualEqual_VectorVector_ReturnValue)
	//				{
	//					__CurrentState = 15;
	//					break;
	//				}
	//			}
	//		case 10:
	//			{
	//				if(::IsValid(StaticMesh))
	//				{
	//					GetPhysicsLinearVelocity_ReturnValue = StaticMesh->UPrimitiveComponent::GetPhysicsLinearVelocity(FName(TEXT("None")));
	//				}
	//			}
	//		case 11:
	//			{
	//				VelocityPrev = GetPhysicsLinearVelocity_ReturnValue;
	//			}
	//		case 12:
	//			{
	//				ABP_Portal_C3609834151*  __Local__11 = ((ABP_Portal_C3609834151*)nullptr);
	//				UBP_PortalsFunctions_C3748030278::PortalConvertVelocity(CurrentPortal, ((::IsValid(CurrentPortal)) ? (CurrentPortal->TargetPortal) : (__Local__11)), VelocityPrev, this, /*out*/ PortalConvertVelocity_NewVelocity);
	//			}
	//		case 13:
	//			{
	//				VelocityNew = PortalConvertVelocity_NewVelocity;
	//			}
	//		case 14:
	//			{
	//				if(::IsValid(StaticMesh))
	//				{
	//					StaticMesh->UPrimitiveComponent::SetPhysicsLinearVelocity(VelocityNew, false, FName(TEXT("None")));
	//				}
	//				__CurrentState = -1;
	//				break;
	//			}
	//		case 15:
	//			{
	//				if(::IsValid(StaticMesh))
	//				{
	//					StaticMesh->USceneComponent::SetWorldScale3D(bpfv__TargetScale);
	//				}
}
