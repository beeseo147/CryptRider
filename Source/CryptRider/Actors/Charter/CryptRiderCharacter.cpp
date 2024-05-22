// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptRiderCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "CryptRider/Components/Grabber.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/LocalPlayer.h"
#include "Controller/CryptRiderPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/InventoryMenuUserWidget.h"
#include "UI/MainMenu.h"



////////////////////////////////////////////////////////////////////////

ACryptRiderCharacter::ACryptRiderCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	Grabber = CreateDefaultSubobject<UGrabber>(TEXT("Grabber"));
	Grabber->SetupAttachment(FirstPersonCameraComponent);


	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/FirstPerson/Input/IMC_Default.IMC_Default'") };
		check(Asset.Succeeded());
		DefaultMappingContext = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Jump.IA_Jump'") };
		check(Asset.Succeeded());
		JumpAction = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Move.IA_Move'") };
		check(Asset.Succeeded());
		MoveAction = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Look.IA_Look'") };
		check(Asset.Succeeded());
		LookAction = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Grab.IA_Grab'") };
		check(Asset.Succeeded());
		GrabAction = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_InventoryToggle.IA_InventoryToggle'") };
		check(Asset.Succeeded());
		InventoryAction = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Pick.IA_Pick'") };
		check(Asset.Succeeded());
		PickAction = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Return.IA_Return'") };
		check(Asset.Succeeded());
		ReturnAction = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Interface.IA_Interface'") };
		check(Asset.Succeeded());
		InteractAction = Asset.Object;
	}
}

void ACryptRiderCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////// Input

void ACryptRiderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACryptRiderCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACryptRiderCharacter::Look);

		//Grab
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this, &ACryptRiderCharacter::Grab);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Completed, this, &ACryptRiderCharacter::Grab);

		//Inventory
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ACryptRiderCharacter::InventoryOpen);

		//Pick
		EnhancedInputComponent->BindAction(PickAction, ETriggerEvent::Triggered, this, &ACryptRiderCharacter::Pick);

		//Return
		EnhancedInputComponent->BindAction(ReturnAction, ETriggerEvent::Triggered, this, &ACryptRiderCharacter::Return);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACryptRiderCharacter::Interact);
	}
	else
	{
		ensure(EnhancedInputComponent);
	}
}


void ACryptRiderCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ACryptRiderCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACryptRiderCharacter::Grab(const FInputActionValue& Value)
{
	bool Hold = Value.Get<bool>();

	if (Hold)
	{
		Grabber->Grab();
	}
	else
	{
		Grabber->Release();
	}
}

void ACryptRiderCharacter::InventoryOpen(const FInputActionValue& Value)
{
	bool InventoryOpen = Value.Get<bool>();
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
		ACryptRiderPlayerController* PlayerController = Cast<ACryptRiderPlayerController>(GetController());
		PlayerController->SetShowMouseCursor(true);

		//이후로는 위젯
		PlayerController->InventoryMenuWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		if (PlayerController->ExaminationWidget->IsInViewport())
		{
			PlayerController->ExaminationWidget->RemoveFromParent();
		}
		PlayerController->SetInputMode(FInputModeGameAndUI());
	}
	else 
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		ACryptRiderPlayerController* PlayerController = Cast<ACryptRiderPlayerController>(GetController());
		PlayerController->ResetIgnoreLookInput();
		PlayerController->SetShowMouseCursor(false);

		//이후로는 위젯
		PlayerController->InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void ACryptRiderCharacter::Pick(const FInputActionValue& Value)
{
}

void ACryptRiderCharacter::Return(const FInputActionValue& Value)
{
	bool CloseExamination = Value.Get<bool>();
	if (bInventoryOpen)
	{
		ACryptRiderPlayerController* PlayerController = Cast<ACryptRiderPlayerController>(GetController());
		PlayerController->ExaminationWidget->RemoveFromParent();
		InventoryOpen(true);
	}
}

void ACryptRiderCharacter::Interact(const FInputActionValue& Value)
{
	UCameraComponent* PlayerCamera = GetFirstPersonCameraComponent();
	FVector CameraLocation = PlayerCamera->GetComponentLocation();
	FVector CameraVector = PlayerCamera->GetForwardVector();
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(PlayerCamera, CameraLocation, CameraLocation + CameraVector * 200,
		ETraceTypeQuery::TraceTypeQuery12, false,
		TArray<class AActor*>(), EDrawDebugTrace::None, HitResult, true);

	AActor* HitActor = HitResult.GetActor();
	if (HitActor)
	{
		bool bIsImplemented = HitActor->GetClass()->ImplementsInterface(UPlayerInterFace::StaticClass());
		if (bIsImplemented)
		{
			// 인터페이스 함수 호출
			IPlayerInterFace::Execute_ReactToTrigger(HitActor);
		}
	}
}