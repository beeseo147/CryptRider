// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VR/VRCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/VRGrabber.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Data/Input/InputDataConfig.h"
#include "GameFramework/Controller.h"
#include "HandGraph.h"
#include "Components/WidgetComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/VRHandSkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/VRInventoryMenuUserWidget.h"
#include "UI/ExaminationWidget.h"
#include "UI/MainMenu.h"
#include "GameFramework/CharacterMovementComponent.h"
#include"GameFramework/PlayerController.h"
#include "Components/VRInventory.h"

AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCollisionProfileName(Player);

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(GetRootComponent());
	VRCamera->SetRelativeLocation(FVector(0, 0, 50));
	{
		//motionController
		MotionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeft"));
		MotionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRight"));
		MotionControllerLeft->SetTrackingMotionSource(LeftGrip);
		MotionControllerRight->SetTrackingMotionSource(RightGrip);
		MotionControllerLeft->SetupAttachment(GetRootComponent());
		MotionControllerRight->SetupAttachment(GetRootComponent());
	}
	{
		//MotionControllerAim
		MotionControllerLeftAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeftAim"));
		MotionControllerRightAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRightAim"));
		MotionControllerLeftAim->SetTrackingMotionSource(LeftAim);
		MotionControllerRightAim->SetTrackingMotionSource(RightAim);
		MotionControllerLeftAim->SetupAttachment(GetRootComponent());
		MotionControllerRightAim->SetupAttachment(GetRootComponent());
	}
	{
		//WidgetInteraction
		WidgetInteractionLeft = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionLeft"));
		WidgetInteractionRight = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionRight"));
		WidgetInteractionLeft->SetupAttachment(MotionControllerLeftAim);
		WidgetInteractionLeft->PointerIndex = 1;
		WidgetInteractionLeft->InteractionDistance = 1000.f;
		WidgetInteractionLeft->bShowDebug = true;
		WidgetInteractionLeft->TraceChannel = ECollisionChannel::ECC_GameTraceChannel6;
		WidgetInteractionRight->SetupAttachment(MotionControllerRightAim);
		WidgetInteractionRight->PointerIndex = 2;
		WidgetInteractionRight->InteractionDistance = 1000.f;
		WidgetInteractionRight->bShowDebug = true;
		WidgetInteractionRight->TraceChannel = ECollisionChannel::ECC_GameTraceChannel6;
	}
	HandGraphLeft = CreateDefaultSubobject<UHandGraph>(TEXT("HandGraphLeft"));
	HandGraphRight = CreateDefaultSubobject<UHandGraph>(TEXT("HandGraphRight"));
	
	GetMesh()->DestroyComponent();
	
	LeftHand = CreateDefaultSubobject<UVRHandSkeletalMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(MotionControllerLeft);

	RightHand = CreateDefaultSubobject<UVRHandSkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(MotionControllerRight);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/VR/Hands/BPA_Hand.BPA_Hand_C'"));
	check(AnimClass.Class);

	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
		RightHand->SetSkeletalMeshAsset(Asset.Object);

		const FTransform Transform = FTransform(FRotator(25.0, 0.0, 90.0), FVector(-2.98, 3.5, 4.56));
		RightHand->SetRelativeTransform(Transform);
		RightHand->SetAnimClass(AnimClass.Class);
	}
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));
		LeftHand->SetSkeletalMeshAsset(Asset.Object);

		const FTransform Transform = FTransform(FRotator(-25.0, 180.0, 90.0), FVector(-2.98, -3.5, 4.56));
		LeftHand->SetRelativeTransform(Transform);
		LeftHand->bMirror = true;
		LeftHand->SetAnimClass(AnimClass.Class);
	}
	{
		//UVRInventory
		VRInventoryComponents = CreateDefaultSubobject<UVRInventory>(TEXT("VRInventory"));
	}
	//UI
	{
		LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/VR/BP_VRMainUIC++.BP_VRMainUIC++_C'"),
			nullptr, LOAD_None, nullptr);
		LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/VR/UI_VRInventoryMenu.UI_VRInventoryMenu_C'"),
			nullptr, LOAD_None, nullptr);
		
		{
			//UClass* WidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/VR/BP_VRMainUIC++.BP_VRMainUIC++_C'"));
			//if (WidgetClass)
			//{
			//	//UMainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), WidgetClass);
			//	//UMainMenuWidget->AddToViewport();
			//}
			//else
			//{
			//	ensure(WidgetClass);
			//}
		}
		{
			/*static ConstructorHelpers::FClassFinder<UVRInventoryMenuUserWidget>FindClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/VR/UI_VRInventoryMenu.UI_VRInventoryMenu_C'"));
			check(FindClass.Class);*/

			UClass* WidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/VR/UI_VRInventoryMenu.UI_VRInventoryMenu_C'"));
			check(WidgetClass);
			//InventoryMenuWidget = CreateWidget<UVRInventoryMenuUserWidget>(GetWorld(), WidgetClass);
			/*if (InventoryMenuWidget)
			{
				InventoryMenuWidget->SetVisibility(ESlateVisibility::Visible);
			}*/
			InventoryHUD = CreateDefaultSubobject<UWidgetComponent>(TEXT("InventoryHUD"));
			//InventoryHUD->InitWidget();
			InventoryHUD->SetupAttachment(VRCamera);
			//if (InventoryMenuWidget)
			{
				InventoryHUD->SetWidgetClass(WidgetClass);
				//InventoryHUD->SetWidget(InventoryMenuWidget);
			}
			InventoryHUD->SetRelativeLocation(FVector(300,0,0));
			InventoryHUD->SetRelativeRotation(FRotator(0, -180., 0));
			InventoryHUD->SetWidgetSpace(EWidgetSpace::World);
			InventoryHUD->SetDrawSize(FVector2D(256, 256));
			InventoryHUD->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel6);
			InventoryHUD->SetBlendMode(EWidgetBlendMode::Transparent);
			InventoryHUD->SetGeometryMode(EWidgetGeometryMode::Cylinder);
			InventoryHUD->SetCylinderArcAngle(90);
			InventoryHUD->SetVisibility(false);
			
		}
		{
			//UClass* WidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/VR/UI_VRInventoryMenu.UI_VRInventoryMenu_C'"));
			//check(WidgetClass);
			//InventoryMenuWidget = CreateWidget<UVRInventoryMenuUserWidget>(GetWorld(), WidgetClass);
			
		}
		{
			LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/VR/UI_VRExamination.UI_VRExamination_C'"),
				nullptr, LOAD_None, nullptr);
			UClass* WidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/VR/UI_VRExamination.UI_VRExamination_C'"));

			ExaminationWidget = CreateWidget<UExaminationWidget>(GetWorld(), WidgetClass);
		}
	}
	ensure(InventoryHUD);
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

		const UInputDataConfig* BasicInputDataConfig = GetDefault<UInputDataConfig>();
		Subsystem->AddMappingContext(BasicInputDataConfig->InputMappingContext, 0);

		const UVRHandsInputDataConfig* VRHandsInputDataConfig = GetDefault<UVRHandsInputDataConfig>();
		Subsystem->AddMappingContext(VRHandsInputDataConfig->InputMappingContext, 0);

		// HandGraphLeft, HandGraphRight
		const UVRHandsAnimationInputDataConfig* VRHandsAnimationInputDataConfig = GetDefault<UVRHandsAnimationInputDataConfig>();
		Subsystem->AddMappingContext(VRHandsAnimationInputDataConfig->InputMappingContext, 1);
	}
	else { check(false); }
	ensure(InventoryHUD);

	if (!InventoryMenuWidget)
	{
		InventoryMenuWidget = Cast<UVRInventoryMenuUserWidget>(InventoryHUD->GetWidget());
	}
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ensure(EnhancedInputComponent);

	{
		const UInputDataConfig* BasicInputDataConfig = GetDefault<UInputDataConfig>();
		EnhancedInputComponent->BindAction(BasicInputDataConfig->MoveAction, ETriggerEvent::Triggered, this, &AVRCharacter::OnMove);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->InventoryAction, ETriggerEvent::Started, this, &AVRCharacter::InventoryOpen);
		
		//Pick
		EnhancedInputComponent->BindAction(BasicInputDataConfig->PickAction, ETriggerEvent::Started, this, &AVRCharacter::Pick);

		//Interact
		EnhancedInputComponent->BindAction(BasicInputDataConfig->InteractAction, ETriggerEvent::Started, this, &AVRCharacter::Interact);
	}
	{
		const UVRHandsInputDataConfig* VRHandsInputDataConfig = GetDefault<UVRHandsInputDataConfig>();
		EnhancedInputComponent->BindAction(VRHandsInputDataConfig->IA_Grab_Left, ETriggerEvent::Started, this, &AVRCharacter::OnGrabLeftStarted);
		EnhancedInputComponent->BindAction(VRHandsInputDataConfig->IA_Grab_Left, ETriggerEvent::Completed, this, &AVRCharacter::OnGrabLeftCompleted);

		EnhancedInputComponent->BindAction(VRHandsInputDataConfig->IA_Grab_Right, ETriggerEvent::Started, this, &AVRCharacter::OnGrabRightStarted);
		EnhancedInputComponent->BindAction(VRHandsInputDataConfig->IA_Grab_Right, ETriggerEvent::Completed, this, &AVRCharacter::OnGrabRightCompleted);
	}
	{
		HandGraphLeft->SetupPlayerInputComponent(MotionControllerLeft, EnhancedInputComponent);
		HandGraphRight->SetupPlayerInputComponent(MotionControllerRight, EnhancedInputComponent);
	}
}

void AVRCharacter::OnMove(const FInputActionValue& InputActionValue)
{
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();

	const FRotator CameraRotator = VRCamera->GetRelativeRotation();
	const FRotator CameraYawRotator = FRotator(0., CameraRotator.Yaw, 0.);

	if (!FMath::IsNearlyZero(ActionValue.Y))
	{
		const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(CameraYawRotator);
		AddMovementInput(ForwardVector, ActionValue.Y);
	}

	if (!FMath::IsNearlyZero(ActionValue.X))
	{
		const FVector RightVector = UKismetMathLibrary::GetRightVector(CameraYawRotator);
		AddMovementInput(RightVector, ActionValue.X);
	}
}



void AVRCharacter::OnGrabStarted(UMotionControllerComponent* MotionControllerComponent, const bool bLeft, const FInputActionValue& InputActionValue)
{
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Red, TEXT("OnGrabStarted"));
	const FVector WorldLocation = MotionControllerComponent->GetComponentLocation();
	const float Radius = 60.f;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_EngineTraceChannel2) };
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMultiForObjects(this, WorldLocation, WorldLocation,
		Radius, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true);

	for (FHitResult& It : HitResults)
	{
		AActor* HitActor = It.HitObjectHandle.GetManagingActor();
		if (!HitActor) { continue; }

		UVRGrabber* GrabComponent = HitActor->GetComponentByClass<UVRGrabber>();
		if (!GrabComponent) { continue; }

		GrabComponent->Grab(MotionControllerComponent);

		/*UGrabComponent** TargetGrabComponent = bLeft ? &LeftHandAttachedGrabComponent : &RightHandAttachedGrabComponent;
		*TargetGrabComponent = GrabComponent;*/

		//// Wrong code
		//UGrabComponent* TargetGrabComponent2 = bLeft ? LeftHandAttachedGrabComponent : RightHandAttachedGrabComponent;
		//TargetGrabComponent2 = GrabComponent;

		bLeft ? LeftHandAttachedGrabComponent = GrabComponent : RightHandAttachedGrabComponent = GrabComponent;

		// HitActor->Destroy();
		return;
	}

	if (bLeft)
	{
		WidgetInteractionLeft->PressPointerKey(FKey(TEXT("LeftMouseButton")));
	}
	else
	{
		WidgetInteractionRight->PressPointerKey(FKey(TEXT("LeftMouseButton")));
	}
}

void AVRCharacter::OnGrabCompleted(UMotionControllerComponent* MotionControllerComponent, const bool bLeft, const FInputActionValue& InputActionValue)
{
	UVRGrabber** TargetGrabComponentPointer = bLeft ? &LeftHandAttachedGrabComponent : &RightHandAttachedGrabComponent;
	UVRGrabber* TargetGrabComponent = *TargetGrabComponentPointer;
	if (!IsValid(TargetGrabComponent))
	{
		if (bLeft)
		{
			WidgetInteractionLeft->ReleasePointerKey(FKey(TEXT("LeftMouseButton")));
		}
		else
		{
			WidgetInteractionRight->ReleasePointerKey(FKey(TEXT("LeftMouseButton")));
		}
		return;
	}

	TargetGrabComponent->ReleaseGrab();

	*TargetGrabComponentPointer = nullptr;
}
void AVRCharacter::InventoryOpen(const FInputActionValue& InputActionValue)
{
	bool InventoryOpen = InputActionValue.Get<bool>();
	if (!bInventoryOpen)
	{
		bInventoryOpen = true;
	}
	else
	{
		bInventoryOpen = false;
	}
	if (bInventoryOpen)
	{
		GetCharacterMovement()->DisableMovement();
		//이후로는 위젯
		InventoryHUD->SetVisibility(true);
		
		//InventoryMenuWidget->SetVisibility(ESlateVisibility::Visible);
		/*if (ExaminationWidget->IsInViewport())
		{
			ExaminationWidget->RemoveFromParent();
		}*/
		//SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

		//이후로는 위젯
		InventoryHUD->SetVisibility(false);
	}
}

void AVRCharacter::Pick(const FInputActionValue& InputActionValue)
{
	
}

void AVRCharacter::Interact(const FInputActionValue& InputActionValue)
{
	UCameraComponent* PlayerCamera = GetVRCameraComponent();
	FVector CameraLocation = PlayerCamera->GetComponentLocation();
	FVector CameraVector = PlayerCamera->GetForwardVector();
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(PlayerCamera, CameraLocation, CameraLocation + CameraVector * 200,
		ETraceTypeQuery::TraceTypeQuery13, false,
		TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true);

	AActor* HitActor = HitResult.GetActor();
	if (HitActor)
	{
		FString MyString = HitActor->GetName();
		UE_LOG(LogTemp, Display, TEXT("Now : %s"), *MyString);
		bool bIsImplemented = HitActor->GetClass()->ImplementsInterface(UPlayerInterFace::StaticClass());
		if (bIsImplemented)
		{
			// 인터페이스 함수 호출
			IPlayerInterFace::Execute_ReactToTrigger(HitActor);
		}
	}

}
