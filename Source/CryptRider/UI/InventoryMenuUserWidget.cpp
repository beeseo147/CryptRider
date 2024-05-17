// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryMenuUserWidget.h"

void UInventoryMenuUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UInventoryMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/UI_InventorySlot.UI_InventorySlot_C'"),
		nullptr, LOAD_None, nullptr);
	UClass* InventoryItemWidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/UI_InventorySlot.UI_InventorySlot_C'"));
	if (!GetValid(InventoryItemWidgetClass))
	{
		ensure(false);
	}
	int32 Col = 4;
	int32 Row = SlotsPerRow / Col;
	int32 Index=0;
	for (int32 i = 0; i < 2; i++)
	{
		for (int32 k = 0; k < Col; ++k)
		{
			UMySlotUserWidget * Widget = Cast<UMySlotUserWidget>(CreateWidget(this, InventoryItemWidgetClass));
			Widget->MyIndex = Index;
			InventoryGrid->AddChildToUniformGrid(Widget,i, k);
			InventorySlots.Add(Widget);
			
		}
	}
}

UMySlotUserWidget* UInventoryMenuUserWidget::GetChildAt(int32 Index)
{
	return InventorySlots[Index];
}
