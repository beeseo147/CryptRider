// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InventoryMenuUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Blueprint/UserWidget.h"
#include "UI/MySlotUserWidget.h"
#include "VRInventoryMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CRYPTRIDER_API UVRInventoryMenuUserWidget : public UInventoryMenuUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;


};
