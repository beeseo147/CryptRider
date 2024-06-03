// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/DataSubsystem.h"
#include "Data/Item/ItemData.h"
#include "Data/Item/InventoryItem.h"

UDataSubsystem::UDataSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/Actors/Inventory/DT_ItemData.DT_ItemData'") };
		ensure(Asset.Object);
		FItemDataTable = Asset.Object;
	}
}

const FItemData* UDataSubsystem::FindItemData(const FName& InKey)
{
	FItemData* Row = FItemDataTable->FindRow<FItemData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}
