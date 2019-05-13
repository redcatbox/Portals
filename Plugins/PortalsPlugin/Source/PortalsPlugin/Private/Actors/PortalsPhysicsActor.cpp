// Fill out your copyright notice in the Description page of Project Settings.

#include "PortalsPhysicsActor.h"

APortalsPhysicsActor::APortalsPhysicsActor()
{
	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMeshCopy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshCopy"));
	//RootComponent = StaticMesh;
	//StaticMesh->CreationMethod = EComponentCreationMethod::Native;
	//auto& __Local__0 = (*(AccessPrivateProperty<UStaticMesh* >((StaticMesh), UStaticMeshComponent::__PPO__StaticMesh() )));
	//__Local__0 = CastChecked<UStaticMesh>(CastChecked<UDynamicClass>(APortalsPhysicsActor::StaticClass())->UsedAssets[0], ECastCheckedType::NullAllowed);
	//StaticMesh->BodyInstance.SetCollisionProfileName(FName(TEXT("PhysicsActor")));
	//StaticMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	//StaticMesh->BodyInstance.bSimulatePhysics = true;
	//if(!StaticMesh->IsTemplate())
	//{
	//	StaticMesh->BodyInstance.FixupData(StaticMesh);
	//}
	//StaticMeshCopy->CreationMethod = EComponentCreationMethod::Native;
	//StaticMeshCopy->AttachToComponent(StaticMesh, FAttachmentTransformRules::KeepRelativeTransform );
	//auto& __Local__1 = (*(AccessPrivateProperty<UStaticMesh* >((StaticMeshCopy), UStaticMeshComponent::__PPO__StaticMesh() )));
	//__Local__1 = CastChecked<UStaticMesh>(CastChecked<UDynamicClass>(APortalsPhysicsActor::StaticClass())->UsedAssets[0], ECastCheckedType::NullAllowed);
	//StaticMeshCopy->BodyInstance.SetCollisionProfileName(FName(TEXT("NoCollision")));
	//StaticMeshCopy->bVisible = false;
	//if(!StaticMeshCopy->IsTemplate())
	//{
	//	StaticMeshCopy->BodyInstance.FixupData(StaticMeshCopy);
	//}
	//MID1 = nullptr;
	//MID2 = nullptr;
	//MeshAsset = CastChecked<UStaticMesh>(CastChecked<UDynamicClass>(APortalsPhysicsActor::StaticClass())->UsedAssets[0], ECastCheckedType::NullAllowed);
	//MaterialAsset = CastChecked<UMaterialInterface>(CastChecked<UDynamicClass>(APortalsPhysicsActor::StaticClass())->UsedAssets[1], ECastCheckedType::NullAllowed);
	//CurrentPortal = nullptr;
	//IsOverlappingPortal = false;
	//VelocityPrev = FVector(0.000000, 0.000000, 0.000000);
	//VelocityNew = FVector(0.000000, 0.000000, 0.000000);
	//IsHeld = false;
	//ProjectedDistance = 0.000000f;
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APortalsPhysicsActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APortalsPhysicsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void APortalsPhysicsActor::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
//{
//	Super::PostLoadSubobjects(OuterInstanceGraph);
//	if(StaticMesh)
//	{
//		StaticMesh->CreationMethod = EComponentCreationMethod::Native;
//	}
//	if(StaticMeshCopy)
//	{
//		StaticMeshCopy->CreationMethod = EComponentCreationMethod::Native;
//	}
//}
//
//void APortalsPhysicsActor::__CustomDynamicClassInitialization(UDynamicClass* InDynamicClass)
//{
//	ensure(0 == InDynamicClass->ReferencedConvertedFields.Num());
//	ensure(0 == InDynamicClass->MiscConvertedSubobjects.Num());
//	ensure(0 == InDynamicClass->DynamicBindingObjects.Num());
//	ensure(0 == InDynamicClass->ComponentTemplates.Num());
//	ensure(0 == InDynamicClass->Timelines.Num());
//	ensure(nullptr == InDynamicClass->AnimClassImplementation);
//	InDynamicClass->AssembleReferenceTokenStream();
//	// List of all referenced converted classes
//	InDynamicClass->ReferencedConvertedFields.Add(ABP_Portal_C3609834151::StaticClass());
//	InDynamicClass->ReferencedConvertedFields.Add(UBP_PortalsFunctions_C3748030278::StaticClass());
//	FConvertedBlueprintsDependencies::FillUsedAssetsInDynamicClass(InDynamicClass, &__StaticDependencies_DirectlyUsedAssets);
//	auto __Local__2 = NewObject<USceneComponent>(InDynamicClass, USceneComponent::StaticClass(), TEXT("DefaultSceneRoot_GEN_VARIABLE"));
//	InDynamicClass->ComponentTemplates.Add(__Local__2);
//	auto __Local__3 = NewObject<UComponentDelegateBinding>(InDynamicClass, UComponentDelegateBinding::StaticClass(), TEXT("ComponentDelegateBinding_3"));
//	InDynamicClass->DynamicBindingObjects.Add(__Local__3);
//	__Local__3->ComponentDelegateBindings = TArray<FBlueprintComponentDelegateBinding> ();
//	__Local__3->ComponentDelegateBindings.AddUninitialized(2);
//	FBlueprintComponentDelegateBinding::StaticStruct()->InitializeStruct(__Local__3->ComponentDelegateBindings.GetData(), 2);
//	auto& __Local__4 = __Local__3->ComponentDelegateBindings[0];
//	__Local__4.ComponentPropertyName = FName(TEXT("StaticMesh"));
//	__Local__4.DelegatePropertyName = FName(TEXT("OnComponentBeginOverlap"));
//	__Local__4.FunctionNameToBind = FName(TEXT("BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature"));
//	auto& __Local__5 = __Local__3->ComponentDelegateBindings[1];
//	__Local__5.ComponentPropertyName = FName(TEXT("StaticMesh"));
//	__Local__5.DelegatePropertyName = FName(TEXT("OnComponentEndOverlap"));
//	__Local__5.FunctionNameToBind = FName(TEXT("BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_6_ComponentEndOverlapSignature__DelegateSignature"));
//}
//
//void APortalsPhysicsActor::ExecuteUbergraph_BP_PhysActor_0(int32 bpp__EntryPoint)
//{
//	check(bpp__EntryPoint == 18);
//	// optimized KCST_UnconditionalGoto
//	b0l__K2Node_DynamicCast_AsBP_Portal1 = Cast<ABP_Portal_C3609834151>(b0l__K2Node_ComponentBoundEvent_OtherActor);
//	b0l__K2Node_DynamicCast_bSuccess1 = (b0l__K2Node_DynamicCast_AsBP_Portal1 != nullptr);;
//	if (!b0l__K2Node_DynamicCast_bSuccess1)
//	{
//		return; //KCST_GotoReturnIfNot
//	}
//	CurrentPortal = b0l__K2Node_DynamicCast_AsBP_Portal1;
//	// optimized KCST_UnconditionalGoto
//	IsOverlappingPortal = true;
//	// optimized KCST_UnconditionalGoto
//	ToggleComponent(StaticMeshCopy, true);
//	if(::IsValid(CurrentPortal))
//	{
//		CurrentPortal->ToggleFrameCollision(ECollisionEnabled::NoCollision);
//	}
//	if(::IsValid(CurrentPortal) && ::IsValid(CurrentPortal->TargetPortal))
//	{
//		CurrentPortal->TargetPortal->ToggleFrameCollision(ECollisionEnabled::NoCollision);
//	}
//	if(::IsValid(MID1))
//	{
//		MID1->UMaterialInstanceDynamic::SetScalarParameterValue(FName(TEXT("UseClipPlane")), 1.000000);
//	}
//	if(::IsValid(MID2))
//	{
//		MID2->UMaterialInstanceDynamic::SetScalarParameterValue(FName(TEXT("UseClipPlane")), 1.000000);
//	}
//	return; // KCST_GotoReturn
//}
//
//void APortalsPhysicsActor::ExecuteUbergraph_BP_PhysActor_1(int32 bpp__EntryPoint)
//{
//	check(bpp__EntryPoint == 21);
//	// optimized KCST_UnconditionalGoto
//	if (!IsOverlappingPortal)
//	{
//		return; //KCST_GotoReturnIfNot
//	}
//	TeleportationVisualization();
//	return; // KCST_GotoReturn
//}
//
//void APortalsPhysicsActor::ExecuteUbergraph_BP_PhysActor_2(int32 bpp__EntryPoint)
//{
//	check(bpp__EntryPoint == 1);
//	// optimized KCST_UnconditionalGoto
//	b0l__K2Node_DynamicCast_AsBP_Portal = Cast<ABP_Portal_C3609834151>(b0l__K2Node_ComponentBoundEvent_OtherActor1);
//	b0l__K2Node_DynamicCast_bSuccess = (b0l__K2Node_DynamicCast_AsBP_Portal != nullptr);;
//	if (!b0l__K2Node_DynamicCast_bSuccess)
//	{
//		return; //KCST_GotoReturnIfNot
//	}
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
//	if(::IsValid(MID1))
//	{
//		MID1->UMaterialInstanceDynamic::SetScalarParameterValue(FName(TEXT("UseClipPlane")), 0.000000);
//	}
//	if(::IsValid(MID2))
//	{
//		MID2->UMaterialInstanceDynamic::SetScalarParameterValue(FName(TEXT("UseClipPlane")), 0.000000);
//	}
//	CurrentPortal = ((ABP_Portal_C3609834151*)nullptr);
//	return; // KCST_GotoReturn
//}
//
//void APortalsPhysicsActor::ReceiveTick(float bpp__DeltaSeconds)
//{
//	b0l__K2Node_Event_DeltaSeconds = bpp__DeltaSeconds;
//	ExecuteUbergraph_BP_PhysActor_1(21);
//}
//
//void APortalsPhysicsActor::BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(UPrimitiveComponent* bpp__OverlappedComponent, AActor* bpp__OtherActor, UPrimitiveComponent* bpp__OtherComp, int32 bpp__OtherBodyIndex, bool bpp__bFromSweep, FHitResult const& bpp__SweepResult__const)
//{
//	typedef FHitResult  T__Local__6;
//	T__Local__6& bpp__SweepResult = *const_cast<T__Local__6 *>(&bpp__SweepResult__const);
//	b0l__K2Node_ComponentBoundEvent_OverlappedComponent = bpp__OverlappedComponent;
//	b0l__K2Node_ComponentBoundEvent_OtherActor = bpp__OtherActor;
//	b0l__K2Node_ComponentBoundEvent_OtherComp = bpp__OtherComp;
//	b0l__K2Node_ComponentBoundEvent_OtherBodyIndex = bpp__OtherBodyIndex;
//	b0l__K2Node_ComponentBoundEvent_bFromSweep = bpp__bFromSweep;
//	b0l__K2Node_ComponentBoundEvent_SweepResult = bpp__SweepResult;
//	ExecuteUbergraph_BP_PhysActor_0(18);
//}
//
//void APortalsPhysicsActor::BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_6_ComponentEndOverlapSignature__DelegateSignature(UPrimitiveComponent* bpp__OverlappedComponent, AActor* bpp__OtherActor, UPrimitiveComponent* bpp__OtherComp, int32 bpp__OtherBodyIndex)
//{
//	b0l__K2Node_ComponentBoundEvent_OverlappedComponent1 = bpp__OverlappedComponent;
//	b0l__K2Node_ComponentBoundEvent_OtherActor1 = bpp__OtherActor;
//	b0l__K2Node_ComponentBoundEvent_OtherComp1 = bpp__OtherComp;
//	b0l__K2Node_ComponentBoundEvent_OtherBodyIndex1 = bpp__OtherBodyIndex;
//	ExecuteUbergraph_BP_PhysActor_2(1);
//}
//
//void APortalsPhysicsActor::UserConstructionScript()
//{
//	UMaterialInstanceDynamic* CreateDynamicMaterialInstance_ReturnValue{};
//	UMaterialInstanceDynamic* CreateDynamicMaterialInstance_ReturnValue1{};
//	bool SetStaticMesh_ReturnValue{};
//	bool SetStaticMesh_ReturnValue1{};
//	TArray< int32, TInlineAllocator<8> > __StateStack;
//
//	int32 __CurrentState = 1;
//	do
//	{
//		switch( __CurrentState )
//		{
//		case 1:
//			{
//				__StateStack.Push(6);
//			}
//		case 2:
//			{
//				if(::IsValid(StaticMesh))
//				{
//					SetStaticMesh_ReturnValue1 = StaticMesh->SetStaticMesh(MeshAsset);
//				}
//			}
//		case 3:
//			{
//				CreateDynamicMaterialInstance_ReturnValue1 = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, MaterialAsset);
//			}
//		case 4:
//			{
//				MID1 = CreateDynamicMaterialInstance_ReturnValue1;
//			}
//		case 5:
//			{
//				if(::IsValid(StaticMesh))
//				{
//					StaticMesh->SetMaterial(0, MID1);
//				}
//				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
//				break;
//			}
//		case 6:
//			{
//				if(::IsValid(StaticMeshCopy))
//				{
//					SetStaticMesh_ReturnValue = StaticMeshCopy->SetStaticMesh(MeshAsset);
//				}
//			}
//		case 7:
//			{
//				CreateDynamicMaterialInstance_ReturnValue = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, MaterialAsset);
//			}
//		case 8:
//			{
//				MID2 = CreateDynamicMaterialInstance_ReturnValue;
//			}
//		case 9:
//			{
//				if(::IsValid(StaticMeshCopy))
//				{
//					StaticMeshCopy->SetMaterial(0, MID2);
//				}
//				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
//				break;
//			}
//		default:
//			check(false); // Invalid state
//			break;
//		}
//	} while( __CurrentState != -1 );
//}
//void APortalsPhysicsActor::ToggleComponent(UPrimitiveComponent* bpp__Component, bool bpp__On)
//{
//	int32 __CurrentState = 1;
//	do
//	{
//		switch( __CurrentState )
//		{
//		case 1:
//			{
//				if (!bpp__On)
//				{
//					__CurrentState = 3;
//					break;
//				}
//			}
//		case 2:
//			{
//				if(::IsValid(bpp__Component))
//				{
//					bpp__Component->USceneComponent::SetVisibility(true, false);
//				}
//				__CurrentState = -1;
//				break;
//			}
//		case 3:
//			{
//				if(::IsValid(bpp__Component))
//				{
//					bpp__Component->USceneComponent::SetVisibility(false, false);
//				}
//				__CurrentState = -1;
//				break;
//			}
//		default:
//			break;
//		}
//	} while( __CurrentState != -1 );
//}
//
//void APortalsPhysicsActor::UpdateComponents()
//{
//	FRotator K2_GetComponentRotation_ReturnValue(EForceInit::ForceInit);
//	FVector K2_GetComponentLocation_ReturnValue(EForceInit::ForceInit);
//	FVector GetActorScale3D_ReturnValue(EForceInit::ForceInit);
//	FVector GetActorScale3D_ReturnValue1(EForceInit::ForceInit);
//	FVector GetActorScale3D_ReturnValue2(EForceInit::ForceInit);
//	FVector GetActorScale3D_ReturnValue3(EForceInit::ForceInit);
//	FVector Divide_VectorVector_ReturnValue(EForceInit::ForceInit);
//	bool EqualEqual_VectorVector_ReturnValue{};
//	FVector GetActorForwardVector_ReturnValue(EForceInit::ForceInit);
//	FLinearColor Conv_VectorToLinearColor_ReturnValue(EForceInit::ForceInit);
//	FRotator PortalConvertRotation_NewRotation(EForceInit::ForceInit);
//	FVector K2_GetActorLocation_ReturnValue(EForceInit::ForceInit);
//	FLinearColor Conv_VectorToLinearColor_ReturnValue1(EForceInit::ForceInit);
//	FVector PortalConvertLocation_NewLocation(EForceInit::ForceInit);
//	FHitResult K2_SetWorldRotation_SweepHitResult{};
//	FHitResult K2_SetWorldLocation_SweepHitResult{};
//	FVector GetActorForwardVector_ReturnValue1(EForceInit::ForceInit);
//	FVector K2_GetActorLocation_ReturnValue1(EForceInit::ForceInit);
//	FLinearColor Conv_VectorToLinearColor_ReturnValue2(EForceInit::ForceInit);
//	FLinearColor Conv_VectorToLinearColor_ReturnValue3(EForceInit::ForceInit);
//	int32 __CurrentState = 1;
//	do
//	{
//		switch( __CurrentState )
//		{
//		case 1:
//			{
//				if(::IsValid(CurrentPortal))
//				{
//					K2_GetActorLocation_ReturnValue1 = CurrentPortal->AActor::K2_GetActorLocation();
//				}
//				Conv_VectorToLinearColor_ReturnValue3 = UKismetMathLibrary::Conv_VectorToLinearColor(K2_GetActorLocation_ReturnValue1);
//				if(::IsValid(MID1))
//				{
//					MID1->UMaterialInstanceDynamic::SetVectorParameterValue(FName(TEXT("ClipPlaneBase")), Conv_VectorToLinearColor_ReturnValue3);
//				}
//			}
//		case 2:
//			{
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
//				__CurrentState = 8;
//				break;
//			}
//		default:
//			break;
//		}
//	} while( __CurrentState != -1 );
//}
//void APortalsPhysicsActor::TeleportationVisualization()
//{
//	bool Less_FloatFloat_ReturnValue{};
//	FVector GetActorForwardVector_ReturnValue(EForceInit::ForceInit);
//	FVector K2_GetActorLocation_ReturnValue(EForceInit::ForceInit);
//	FVector K2_GetActorLocation_ReturnValue1(EForceInit::ForceInit);
//	FVector ProjectPointOnToPlane_ReturnValue(EForceInit::ForceInit);
//	FVector Subtract_VectorVector_ReturnValue(EForceInit::ForceInit);
//	float Dot_VectorVector_ReturnValue{};
//	int32 __CurrentState = 1;
//	do
//	{
//		switch( __CurrentState )
//		{
//		case 1:
//			{
//				if (!IsHeld)
//				{
//					__CurrentState = 3;
//					break;
//				}
//			}
//		case 2:
//			{
//				UpdateComponents();
//				__CurrentState = -1;
//				break;
//			}
//		case 3:
//			{
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
//		default:
//			break;
//		}
//	} while( __CurrentState != -1 );
//}
//void APortalsPhysicsActor::Teleportation()
//{
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
//				__CurrentState = 10;
//				break;
//			}
//		default:
//			break;
//		}
//	} while( __CurrentState != -1 );
//}
//PRAGMA_DISABLE_OPTIMIZATION
//void APortalsPhysicsActor::__StaticDependencies_DirectlyUsedAssets(TArray<FBlueprintDependencyData>& AssetsToLoad)
//{
//	const FCompactBlueprintDependencyData LocCompactBlueprintDependencyData[] =
//	{
//		{66, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  StaticMesh /Engine/BasicShapes/Cylinder.Cylinder 
//		{1, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Material /Game/Physics/M_PActorBase.M_PActorBase 
//	};
//	for(const FCompactBlueprintDependencyData& CompactData : LocCompactBlueprintDependencyData)
//	{
//		AssetsToLoad.Add(FBlueprintDependencyData(F__NativeDependencies::Get(CompactData.ObjectRefIndex), CompactData));
//	}
//}
//PRAGMA_ENABLE_OPTIMIZATION
//PRAGMA_DISABLE_OPTIMIZATION
//void APortalsPhysicsActor::__StaticDependenciesAssets(TArray<FBlueprintDependencyData>& AssetsToLoad)
//{
//	__StaticDependencies_DirectlyUsedAssets(AssetsToLoad);
//	const FCompactBlueprintDependencyData LocCompactBlueprintDependencyData[] =
//	{
//		{55, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Class /Script/Engine.StaticMeshComponent 
//		{5, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Class /Script/Engine.SceneComponent 
//		{6, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  ScriptStruct /Script/Engine.PointerToUberGraphFrame 
//		{13, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.PrimitiveComponent 
//		{8, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.Actor 
//		{11, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  ScriptStruct /Script/Engine.HitResult 
//		{22, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.MaterialInstanceDynamic 
//		{17, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.KismetMathLibrary 
//		{67, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.StaticMesh 
//		{26, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.KismetMaterialLibrary 
//		{61, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.MaterialInterface 
//		{33, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  BlueprintGeneratedClass /Game/Portals/BP_Portal.BP_Portal_C 
//		{34, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  BlueprintGeneratedClass /Game/Base/BP/BP_PortalsFunctions.BP_PortalsFunctions_C 
//	};
//	for(const FCompactBlueprintDependencyData& CompactData : LocCompactBlueprintDependencyData)
//	{
//		AssetsToLoad.Add(FBlueprintDependencyData(F__NativeDependencies::Get(CompactData.ObjectRefIndex), CompactData));
//	}
//}
//PRAGMA_ENABLE_OPTIMIZATION
//struct FRegisterHelper__APortalsPhysicsActor
//{
//	FRegisterHelper__APortalsPhysicsActor()
//	{
//		FConvertedBlueprintsDependencies::Get().RegisterConvertedClass(TEXT("/Game/Physics/BP_PhysActor"), &APortalsPhysicsActor::__StaticDependenciesAssets);
//	}
//	static FRegisterHelper__APortalsPhysicsActor Instance;
//};
//FRegisterHelper__APortalsPhysicsActor FRegisterHelper__APortalsPhysicsActor::Instance;
//PRAGMA_ENABLE_DEPRECATION_WARNINGS
//#ifdef _MSC_VER
//#pragma warning (pop)
//#endif
