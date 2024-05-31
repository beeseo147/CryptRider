// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VR/VRCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MotionControllerComponent.h"
#include "Components/VRHandSkeletalMeshComponent.h"

// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCollisionProfileName(TEXT("Player"));

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);

	MotionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeft"));
	MotionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRight"));

	MotionControllerLeft->SetTrackingMotionSource(TEXT("LeftGrip"));
	MotionControllerRight->SetTrackingMotionSource(TEXT("RightGrip"));
	MotionControllerLeft->SetupAttachment(RootComponent);
	MotionControllerRight->SetupAttachment(RootComponent);

	GetMesh()->DestroyComponent();

	LeftHand = CreateDefaultSubobject<UVRHandSkeletalMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(MotionControllerLeft);
	RightHand = CreateDefaultSubobject<UVRHandSkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(MotionControllerRight);

	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
		RightHand->SetSkeletalMeshAsset(Asset.Object);

		const FTransform Transform = FTransform(FRotator(25.0, 0.0, 90.0), FVector(-2.98, 3.5, 4.56));
		RightHand->SetRelativeTransform(Transform);
	}
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));
		LeftHand->SetSkeletalMeshAsset(Asset.Object);

		const FTransform Transform = FTransform(FRotator(-25.0, 180.0, 90.0), FVector(-2.98, -3.5, 4.56));
		LeftHand->SetRelativeTransform(Transform);
		LeftHand->bMirror = true;
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

}

