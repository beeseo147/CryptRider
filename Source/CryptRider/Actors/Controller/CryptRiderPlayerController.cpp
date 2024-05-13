// Copyright Epic Games, Inc. All Rights Reserved.


#include "CryptRiderPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "UI/InventoryMenuUserWidget.h"
#include "UI/MainMenu.h"
void ACryptRiderPlayerController::BeginPlay()
{
	Super::BeginPlay();
	LoadClass<UClass>(ANY_PACKAGE, TEXT("/Game/UI/BP_MainUIC++.BP_MainUIC++_C"), nullptr, LOAD_None, nullptr);
	LoadClass<UClass>(ANY_PACKAGE, TEXT("/Game/UI/Inventory/UI_InventoryMenu.UI_InventoryMenu_C"), nullptr, LOAD_None, nullptr);

	{
		UClass* WidgetClass = FindObject<UClass>(UClass::StaticClass(), TEXT("/Game/UI/BP_MainUIC++.BP_MainUIC++_C"));
		if (WidgetClass)
		{
			CreateWidget<UMainMenu>(GetWorld(), WidgetClass)->AddToViewport();
		}
		else
		{
			ensure(WidgetClass);
		}
	}
	{
		UClass* WidgetClass = FindObject<UClass>(UClass::StaticClass(), TEXT("/Game/UI/Inventory/UI_InventoryMenu.UI_InventoryMenu_C"));
		InventoryMenuWidget = CreateWidget<UInventoryMenuUserWidget>(GetWorld(), WidgetClass);
		InventoryMenuWidget->AddToViewport();
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
