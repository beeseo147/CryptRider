// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/VRHandSkeletalMeshComponent.h"
#include "Animation/VRHandAnimInstance.h"
#include "HandGraph.h"
#include "VRCharacter.generated.h"

static inline const FName LeftGrip = TEXT("LeftGrip");
static inline const FName RightGrip = TEXT("RightGrip");

UCLASS()
class CRYPTRIDER_API AVRCharacter : public ACharacter
{
	friend class UHandGraph;
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void OnMove(const FInputActionValue& InputActionValue);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UVRHandSkeletalMeshComponent* LeftHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UVRHandSkeletalMeshComponent* RightHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHandGraph* HandGraphLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHandGraph* HandGraphRight;
};
