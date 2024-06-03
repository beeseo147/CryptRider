// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VR/VRCharacter.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"


AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCollisionProfileName(TEXT("Player"));

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(GetRootComponent());

	MotionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeft"));
	MotionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRight"));

	MotionControllerLeft->SetTrackingMotionSource(LeftGrip);
	MotionControllerRight->SetTrackingMotionSource(RightGrip);
	MotionControllerLeft->SetupAttachment(GetRootComponent());
	MotionControllerRight->SetupAttachment(GetRootComponent());

	HandGraphLeft = CreateDefaultSubobject<UHandGraph>(TEXT("HandGraphLeft"));
	HandGraphRight = CreateDefaultSubobject<UHandGraph>(TEXT("HandGraphRight"));

	GetMesh()->DestroyComponent();

	LeftHand = CreateDefaultSubobject<UVRHandSkeletalMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(MotionControllerLeft);
	RightHand = CreateDefaultSubobject<UVRHandSkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(MotionControllerRight);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/KDT2/Blueprint/VR/Hands/BPA_Hand.BPA_Hand_C'"));
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
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	/*UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ensure(EnhancedInputComponent);

	const UBasicInputDataConfig* BasicInputDataConfig = GetDefault<UBasicInputDataConfig>();
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);*/
}

void AVRCharacter::OnMove(const FInputActionValue& InputActionValue)
{

}


