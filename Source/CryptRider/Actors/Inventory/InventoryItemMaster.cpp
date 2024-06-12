// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Inventory/InventoryItemMaster.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Data/Item/ItemData.h"

// Sets default values
AInventoryItemMaster::AInventoryItemMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	Prompt = CreateDefaultSubobject<UWidgetComponent>(TEXT("Prompt"));
	Prompt->SetupAttachment(BaseMesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(BaseMesh);

}

void AInventoryItemMaster::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();

	if (InventoryData.IsNull()) { return; }
	if (InventoryData.RowName == NAME_None) { return; }
	FItemData* Data = InventoryData.GetRow<FItemData>(TEXT(""));
	ensure(Data);
	if (InventoryDataTableRow == Data) { return; }
	InventoryDataTableRow = Data;
	ItemAmount = InventoryDataTableRow->Amount;
}

void AInventoryItemMaster::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

}

void AInventoryItemMaster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Prompt->SetRelativeLocation(FVector(0, 0, WidgetDistanceAboutMesh), false);
}

// Called when the game starts or when spawned
void AInventoryItemMaster::BeginPlay()
{
	Super::BeginPlay();
}

void AInventoryItemMaster::SetInventoryDataTableRow(FItemData* InItemData)
{
	InventoryDataTableRow = InItemData;
}

void AInventoryItemMaster::OnGrab()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn);

	APlayerController* PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
	check(PlayerController);

	bool bBindAction = false;
	if (!InputComponent)
	{
		bBindAction = true;
	}
}

void AInventoryItemMaster::OnReleaseGrab()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn);

	APlayerController* PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
	check(PlayerController);

	DisableInput(PlayerController);
}

// Called every frame
void AInventoryItemMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

