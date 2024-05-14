// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.generated.h"
/**
 * 
 */
class AInventoryItemMaster;

USTRUCT()
struct CRYPTRIDER_API FInventoryItem : public FTableRowBase
{

	GENERATED_BODY()

	FInventoryItem() {}
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Item"))
	AInventoryItemMaster* Item;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Amount", MakeStructureDefaultValue = "0"))
	int32 Amount;
};
