// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataSubsystem.generated.h"

/**
 * 
 */
struct FItemData;
struct FInventoryItem;

UCLASS()
class CRYPTRIDER_API UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UDataSubsystem();

	const FItemData* FindItemData(const FName& InKey);
	const FInventoryItem* FindInventoryItem(const FName& InKey);

protected:
	UPROPERTY()
	UDataTable* FItemDataTable;
	UPROPERTY()
	UDataTable* FInventoryDataTable;

};
