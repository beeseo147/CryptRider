// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Inventory/InventoryItemMaster.h"
#include "Data/Item/ItemData.h"

// Sets default values
AInventoryItemMaster::AInventoryItemMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AInventoryItemMaster::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();
	if (InventoryData.IsNull()) { return; }
	if (InventoryData.RowName == NAME_None) { return; }
	const FItemData* Data = InventoryData.GetRow<FItemData>(TEXT(""));
	ensure(Data);
	if (InventoryDataTableRow == Data) { return; }
	InventoryDataTableRow = Data;
}

void AInventoryItemMaster::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

}

void AInventoryItemMaster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AInventoryItemMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryItemMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

