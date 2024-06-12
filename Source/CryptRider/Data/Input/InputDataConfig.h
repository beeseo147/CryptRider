// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputDataConfig.generated.h"


UCLASS()
class UInputDataConfig : public UObject
{
	GENERATED_BODY()

public:
	UInputDataConfig();
	UInputMappingContext* InputMappingContext = nullptr;

public:
	UInputAction* MoveAction = nullptr;
	UInputAction* LookAction = nullptr;
	UInputAction* JumpAction = nullptr;
	UInputAction* GrabAction = nullptr;
	UInputAction* InventoryAction = nullptr;
	UInputAction* PickAction=nullptr;
	UInputAction* ReturnAction = nullptr;
	UInputAction* InteractAction = nullptr;
};