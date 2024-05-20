// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExaminationWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRIDER_API UExaminationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UpdateWidget"))
	void UpdateWidget(const int32 Index);

};
