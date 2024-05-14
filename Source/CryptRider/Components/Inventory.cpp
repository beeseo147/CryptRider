// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory.h"
#include "Kismet/KismetArrayLibrary.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Data/Item/InventoryItem.h"
#include "Actors/Controller/CryptRiderPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "UI/InventoryMenuUserWidget.h"
#include "Data/Item/ItemData.h"
#include "Data/Item/InventoryItem.h"
#include "Actors/Inventory/InventoryItemMaster.h"
// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InventorySlots.SetNum(InventoryCount);
	//ACryptRiderPlayerController ThisController;
	//InventoryMenuWidgetRef = Cast< ACryptRiderPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->InventoryMenuWidget;

}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventory::AddItem(FItemData&InItem)
{
	LocalItem = InItem;
	LocalAmount = InItem.Amount;
	
	//LocalMaxAmountStack = InItem.Item.GetClass()->

	if (LocalMaxAmountStack > 1)
	{
		CheckFreeSlot(InItem);

	}
	else
	{
		if (CheckFreeSlot(InItem))
		{
			InventorySlots.Insert(InItem, LocalIndex);
			UpdateInventorySlot(LocalIndex);

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NoFreeSlot {}"));
			ReMainder = 0;
			return false;
		}
	}
	return false;
}

bool UInventory::CheckFreeSlot(FItemData& InItem)
{
	bool LocalSucess = false;
	for (int i=0;i<InventorySlots.Num();i++)
	{
		if (InventorySlots[i].ItemName!=TEXT(""))
		{
			LocalIndex = i;
			LocalSucess = true;
		}
	}

	return LocalSucess;
}

void UInventory::UpdateInventorySlot(int32 Index)
{
	InventoryMenuWidgetRef;
	//일단 해당 번호의 인덱스에 접근으로..

}

FItemData UInventory::GetItemIndex(int32 Index)
{
	LocalIndex = Index;
	

	return InventorySlots[Index];
}

