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
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UUniformGridPanel* InventoryGrid;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UUserWidget* InventoryDropDown;
protected:
	int32 SlotsPerRow = 4;

};

