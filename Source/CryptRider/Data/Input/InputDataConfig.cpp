// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Input/InputDataConfig.h"

// Add default functionality here for any IInputDataConfig functions that are not pure virtual.

UInputDataConfig::UInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/FirstPerson/Input/IMC_Default.IMC_Default'") };
		check(Asset.Succeeded());
		InputMappingContext = Asset.Object;
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
