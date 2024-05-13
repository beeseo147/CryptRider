// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryMenuUserWidget.h"

void UInventoryMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LoadClass<UUniformGridPanel>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/UI/Inventory/InventoryGrid.InventoryGrid'"),
		nullptr, LOAD_None, nullptr);
	InventoryGrid = FindObject<UUniformGridPanel>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/UI/Inventory/InventoryGrid.InventoryGrid'"));
	// Grid위젯 찾고 할당하기
	//InventoryGrid에 InventorySlots을 추가하기
	LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/UI_InventorySlot.UI_InventorySlot_C'"),
		nullptr, LOAD_None, nullptr);
	UUserWidget* InventorySlots = FindObject<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/UI_InventorySlot.UI_InventorySlot_C'"));
	// Grid위젯 안에 들어갈
	// InventorySlot찾기
	InventoryDropDown = FindObject<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/UI_InventoryDropDown.UI_InventoryDropDown_C'"));

	int32 Col = 4;
	int32 Row = SlotsPerRow / Col;
	UUserWidget* Widget = CreateWidget(InventorySlots);
	for (int32 i = 0; i < Row; ++i)
	{
		for (int32 k = 0; k < Col; ++k)
		{
			InventoryGrid->AddChildToUniformGrid(Widget,i, k);
		}
	}

}
