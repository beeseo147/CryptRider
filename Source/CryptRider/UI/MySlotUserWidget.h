// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MySlotUserWidget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CRYPTRIDER_API UMySlotUserWidget : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintImplementableEvent ,meta = (DisplayName = "UpdateSlot"))
	void UpdateSlot(const int32 Index);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "CloesDropDownMenu"))
	void CloesDropDownMenu(const int32 Index);


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 MyIndex;
};
