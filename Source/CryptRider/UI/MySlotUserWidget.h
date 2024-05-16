// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MySlotUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRIDER_API UMySlotUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UpdateSlot"))
	void UpdateSlot(int Index);
};
