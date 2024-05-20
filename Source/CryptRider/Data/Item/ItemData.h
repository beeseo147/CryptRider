// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"
/**
 * 
 */
class AInventoryItemMaster;
USTRUCT()
struct CRYPTRIDER_API FItemData : public FTableRowBase
{
	GENERATED_BODY()

	FItemData() {}
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemName"))
	FName ItemName;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Icon"))
	UTexture2D* Icon = nullptr;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxStackAmount"))
	int32 MaxStackAmount = 0;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BUsed"))
	bool BUsed = false;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BDrop"))
	bool BDrop = false;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Description"))
	FText Description;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ExaminationMesh"))
	UStaticMesh* ExaminationMesh = nullptr;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ExaminationMesh_Offset"))
	double ExaminationMesh_Offset = 0.0;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BExaminationMesh"))
	bool BExaminationMesh = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Amount"))
	int32 Amount = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemMasterClass"))
	TSubclassOf<AInventoryItemMaster> ItemMasterClass = nullptr;
};
