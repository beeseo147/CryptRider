// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Inventory.h"
#include "VRInventory.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRIDER_API UVRInventory : public UInventory
{
	GENERATED_BODY()
	
	UVRInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	class AVRCharacter* VRPlayerRef;

	//UPROPERTY(BlueprintReadOnly)
	//class UVRInventoryMenuUserWidget* VRInventoryMenuWidgetRef;


	virtual void DropItem(int32 Index) override;
	UFUNCTION(BlueprintCallable)
	bool AddItem2(UPARAM(ref) FItemData& InItem);
	//UFUNCTION()
	void UpdateInventorySlot(int32 Index);
protected:
};
