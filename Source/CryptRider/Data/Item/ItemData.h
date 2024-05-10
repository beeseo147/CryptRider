// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"
/**
 * 
 */

USTRUCT()
struct CRYPTRIDER_API FItemData : public FTableRowBase
{
	GENERATED_BODY()

	FItemData() {}
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemName", MakeStructureDefaultValue = "None"))
	FName ItemName;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Icon", MakeStructureDefaultValue = "None"))
	UTexture2D* Icon;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxStackAmount", MakeStructureDefaultValue = "0"))
	int32 MaxStackAmount;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BUsed", MakeStructureDefaultValue = "False"))
	bool BUsed;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BDrop", MakeStructureDefaultValue = "False"))
	bool BDrop;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BPickUp", MakeStructureDefaultValue = "None"))
	TObjectPtr<UClass> BPickUp;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Description"))
	FText Description;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ExaminationMesh", MakeStructureDefaultValue = "None"))
	UStaticMesh* ExaminationMesh;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ExaminationMesh_Offset", MakeStructureDefaultValue = "0.000000"))
	double ExaminationMesh_Offset;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BExaminationMesh"))
	bool BExaminationMesh;
};