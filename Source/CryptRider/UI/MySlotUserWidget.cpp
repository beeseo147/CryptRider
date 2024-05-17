// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MySlotUserWidget.h"

void UMySlotUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateSlot(MyIndex);
}
