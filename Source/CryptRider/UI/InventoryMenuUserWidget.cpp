// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryMenuUserWidget.h"

void UInventoryMenuUserWidget::NativePreConstruct()
{
	Super::NativeConstruct();

}

void UInventoryMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/UI_InventorySlot.UI_InventorySlot_C'"),
		nullptr, LOAD_None, nullptr);
	UClass* InventoryItemWidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/UI_InventorySlot.UI_InventorySlot_C'"));
	int32 Col = 4;
	int32 Row = SlotsPerRow / Col;
	
	for (int32 i = 0; i < 2; i++)
	{
		for (int32 k = 0; k < Col; ++k)
		{
			InventorySlot = Cast< UUserWidget>(CreateWidget(this, InventoryItemWidgetClass));
			InventoryGrid->AddChildToUniformGrid(InventorySlot,i, k);
		}
	}
}
