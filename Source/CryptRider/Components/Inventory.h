// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Item/ItemData.h"
#include "Data/Item/ItemInventory.h"
#include "Inventory.generated.h"


struct FItemData;
class UInventoryMenuUserWidget;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRIDER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	int InventoryCount = 8;
	
	UPROPERTY(EditAnywhere)
	TArray<FInventoryItem> InventorySlots;

	UPROPERTY(BlueprintReadWrite)
	UInventoryMenuUserWidget* InventoryMenuWidgetRef = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FInventoryItem LocalItem;

	UPROPERTY(BlueprintReadOnly)
	int32 LocalAmount;

	UPROPERTY(BlueprintReadOnly)
	int32 LocalMaxAmountStack;

	UPROPERTY(BlueprintReadOnly)
	int32 LocalIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 ReMainder = 0;

protected:
	bool AddItem(FInventoryItem &InItem);
	bool CheckFreeSlot(FInventoryItem& InItem);
	void UpdateInventorySlot(int32 Index);
};
