#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenuUserWidget.generated.h"

/**
 *
 */
UCLASS()
class CRYPTRIDER_API UInventoryMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UUniformGridPanel* InventoryGrid;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* InventorySlot;

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UUserWidget* InventoryDropDown;*/


protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SlotsPerRow = 8;

};

