// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Animation/VRHandAnimInstance.h"
#include "HandGraph.h"
#include "VRCharacter.generated.h"

static inline const FName Player = TEXT("Player");
static inline const FName LeftGrip = TEXT("LeftGrip");
static inline const FName LeftAim = TEXT("LeftAim");
static inline const FName RightGrip = TEXT("RightGrip");
static inline const FName RightAim = TEXT("RightAim");

class UVRGrabber;
class UInputComponent;
class UHandGraph;
class UCameraComponent;
class UVRHandSkeletalMeshComponent;
class UWidgetInteractionComponent;
class UInventoryMenuUserWidget;
class UMainMenu;
class UExaminationWidget;

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

	void OnGrabLeftStarted(const FInputActionValue& InputActionValue) { OnGrabStarted(MotionControllerLeft, true, InputActionValue); }
	void OnGrabRightStarted(const FInputActionValue& InputActionValue) { OnGrabStarted(MotionControllerRight, false, InputActionValue); }
	void OnGrabStarted(UMotionControllerComponent* MotionControllerComponent, const bool bLeft, const FInputActionValue& InputActionValue);

	void OnGrabLeftCompleted(const FInputActionValue& InputActionValue) { OnGrabCompleted(MotionControllerLeft, true, InputActionValue); }
	void OnGrabRightCompleted(const FInputActionValue& InputActionValue) { OnGrabCompleted(MotionControllerRight, false, InputActionValue); }
	void OnGrabCompleted(UMotionControllerComponent* MotionControllerComponent, const bool bLeft, const FInputActionValue& InputActionValue);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerLeftAim;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerRightAim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetInteractionComponent* WidgetInteractionLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetInteractionComponent* WidgetInteractionRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UVRHandSkeletalMeshComponent* LeftHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UVRHandSkeletalMeshComponent* RightHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHandGraph* HandGraphLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHandGraph* HandGraphRight;

protected:
	UPROPERTY(Transient)
	class UVRGrabber* LeftHandAttachedGrabComponent = nullptr;

	UPROPERTY(Transient)
	class UVRGrabber* RightHandAttachedGrabComponent = nullptr;

//protected:
//	UPROPERTY(BlueprintReadWrite)
//	UMainMenu* UMainMenuWidget;
//
//	UPROPERTY(BlueprintReadWrite)
//	UInventoryMenuUserWidget* InventoryMenuWidget;
//
//	UPROPERTY(BlueprintReadWrite)
//	UExaminationWidget* ExaminationWidget;
//
//	UPROPERTY(BlueprintReadWrite, EditAnywhere)
//	bool IsInventoryOpen = false;
};
