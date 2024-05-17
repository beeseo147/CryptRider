// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Item/ItemData.h"
#include "Data/Item/InventoryItem.h"
#include "Inventory.generated.h"


struct FItemData;
class UInventoryMenuUserWidget;
class AInventoryItemMaster;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRIDER_API UInventory : public UActorComponent
{
	GENERATED_BODY()
	friend class UInventoryMenuUserWidget;
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
	TArray<FItemData> InventorySlots;

	UPROPERTY(BlueprintReadWrite)
	UInventoryMenuUserWidget* InventoryMenuWidgetRef = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FItemData LocalItem;

	UPROPERTY(BlueprintReadOnly)
	int32 LocalAmount{ 0 };

	UPROPERTY(BlueprintReadOnly)
	int32 LocalMaxAmountStack{ 0 };

	UPROPERTY(BlueprintReadOnly)
	int32 LocalIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 ReMainder = 0;

	UPROPERTY(BlueprintReadOnly)
	class ACryptRiderCharacter* PlayerRef;

protected:
	UFUNCTION(BlueprintCallable)
	bool AddItem(UPARAM(ref) FItemData&InItem);
	UFUNCTION(BlueprintCallable)
	bool CheckFreeSlot(FItemData& InItem);
	UFUNCTION(BlueprintCallable)
	void UpdateInventorySlot(int32 Index);
	UFUNCTION(BlueprintCallable)
	void UseItem(int32 Index);
	UFUNCTION(BlueprintCallable)
	void DropItem(int32 Index);

	UFUNCTION(BlueprintPure,BlueprintCallable)
	FItemData GetItemIndex(int32 Index);

	/*UFUNCTION(BlueprintPure, BlueprintCallable)
	void SetItemMastData(FItemData* InItemData);*/

	UFUNCTION(BlueprintCallable)
	bool CheckForEmptySlot();
};
