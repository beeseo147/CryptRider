#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Blueprint/UserWidget.h"
#include "UI/MySlotUserWidget.h"
#include "InventoryMenuUserWidget.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
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
	TArray<UMySlotUserWidget*> InventorySlots;

	UFUNCTION(BlueprintCallable)
	UMySlotUserWidget* GetChildAt(int32 Index);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SlotsPerRow = 8;

};

