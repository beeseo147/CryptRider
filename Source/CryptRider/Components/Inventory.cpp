// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory.h"
#include "Kismet/KismetArrayLibrary.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Data/Item/InventoryItem.h"
#include "Actors/Controller/CryptRiderPlayerController.h"
#include "Actors/Charter/CryptRiderCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "UI/InventoryMenuUserWidget.h"
#include "UI/ExaminationWidget.h"
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
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	PlayerRef = Cast<ACryptRiderCharacter>(OwningPawn);
	check(PlayerRef);
	
	AController* Controller = OwningPawn->GetController();
	PlayerControllerRef = Cast<ACryptRiderPlayerController>(Controller);
	InventoryMenuWidgetRef = PlayerControllerRef->InventoryMenuWidget;
	ExaminationWidgetRef = PlayerControllerRef->ExaminationWidget;
	
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AExaminationActor::StaticClass());
	if (FoundActor)
	{
		ExaminationActor = Cast<AExaminationActor>(FoundActor);
	}
	check(InventoryMenuWidgetRef);
	check(ExaminationWidgetRef);
	check(ExaminationActor);
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventory::AddItem(UPARAM(ref) FItemData&InItem)
{
	LocalItem = InItem;
	LocalAmount = InItem.Amount;
	LocalMaxAmountStack = InItem.MaxStackAmount;
	//Max 값이 1이상일때 고려
	//왜냐면 1이면 그냥 채움됨

	//CheckFreeSlot을 통해 아이템을 가진 InvetorySlot을 찾는다
	//만약 InvetorySlot에 동일한 아이템을 가진 MaxCount에 빈자리가 있다면?
		// 만약 LocalMaxAmount가 기존의 InventorySlots에 갯수 + 새로들어온 아이템에 갯수 보다 적으면
		// 현재 빈자리인 아이템 슬롯을 채운다
		// 만약 LocalMaxAmount가 기존의 InventorySlots에 갯수 + 새로들어온 아이템에 갯수 보다 크면?
		// 현재 빈자리인 아이템 슬롯을 채우고 다시 한번 남은 갯수로 재귀
	//만약 InvetorySlot에 동일한 아이템을 가진 MaxCount에 빈자리가 없다면?
	//CheckForEmptySlot을 통해 아에 빈자리를 찾는다
		// 만약 LocalMaxAmount가 기존의 InventorySlots에 갯수 + 새로들어온 아이템에 갯수 보다 적으면
		// 현재 빈자리인 아이템 슬롯을 채운다
		// 만약 LocalMaxAmount가 기존의 InventorySlots에 갯수 + 새로들어온 아이템에 갯수 보다 크면?
		// 현재 빈자리인 아이템 슬롯을 채우고 다시 한번 남은 갯수로 재귀

	if (LocalMaxAmountStack > 1)
	{
		if (CheckFreeSlot(LocalItem))
		{
			if (LocalMaxAmountStack >= (InventorySlots[LocalIndex].Amount + LocalItem.Amount))
			{
				InventorySlots[LocalIndex].Amount += LocalItem.Amount;
				UpdateInventorySlot(LocalIndex);
			}
			else
			{
				LocalItem.Amount -= InventorySlots[LocalIndex].MaxStackAmount -InventorySlots[LocalIndex].Amount;
				InventorySlots[LocalIndex].Amount = LocalMaxAmountStack;
				UpdateInventorySlot(LocalIndex);
				AddItem(LocalItem);
			}
			
		}
		else
		{
			if (CheckForEmptySlot())
			{
				if (LocalMaxAmountStack >=LocalItem.Amount)
				{
					InventorySlots[LocalIndex] = LocalItem;
					UpdateInventorySlot(LocalIndex);
				}
				else
				{
					InventorySlots[LocalIndex] = LocalItem;
					InventorySlots[LocalIndex].Amount = InventorySlots[LocalIndex].MaxStackAmount;
					UpdateInventorySlot(LocalIndex);
					LocalItem.Amount -= LocalMaxAmountStack;
					AddItem(LocalItem);
				}
			}
			else
			{
				ReMainder = LocalAmount;
				return false;
			}
		}
	}
	else
	{
		if (CheckForEmptySlot())
		{
			InventorySlots[LocalIndex] = LocalItem;
			InventorySlots[LocalIndex].Amount = 1;
			LocalItem.Amount -= 1;
			UpdateInventorySlot(LocalIndex);
			ReMainder = LocalItem.Amount;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NoFreeSlot {}"));
			ReMainder = LocalItem.Amount;
			return false;
		}
	}
	
	return true;
}

bool UInventory::CheckFreeSlot(FItemData& InItem)
{
	//동일한 이름을 가진 슬롯에 남은자리
	bool LocalSucess = false;
	for (int i=0;i<InventorySlots.Num();i++)
	{
		if (InventorySlots[i].ItemName == InItem.ItemName && InventorySlots[i].Amount != InventorySlots[i].MaxStackAmount)
		{
			LocalIndex = i;
			LocalSucess = true;
		}
	}
	return LocalSucess;
}

void UInventory::UpdateInventorySlot(int32 Index)
{
	UMySlotUserWidget* T = InventoryMenuWidgetRef->GetChildAt(Index);
	//일단 해당 번호의 인덱스에 접근으로..
	T->UpdateSlot(Index);
}

void UInventory::UseItem(int32 Index)
{
	if (InventorySlots[Index].Amount > 1) {
		InventorySlots[Index].Amount -= 1;
		UpdateInventorySlot(Index);
	}
	else
	{
		InventorySlots[Index].Amount -= 1;
		InventorySlots[Index].ItemName = NAME_None;
		UpdateInventorySlot(Index);
	}
}

void UInventory::DropItem(int32 Index)
{
	if (!PlayerRef) { return; }
	UCameraComponent* PlayerCamera = PlayerRef->GetFirstPersonCameraComponent();
	FVector CameraLocation = PlayerCamera->GetComponentLocation();
	FVector CameraVector = PlayerCamera->GetForwardVector();
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(PlayerCamera, CameraLocation, CameraLocation+CameraVector*200,
		ETraceTypeQuery::TraceTypeQuery12, false,
		TArray<class AActor*>(), EDrawDebugTrace::None, HitResult, true);

	FTransform SpawnTransform = HitResult.bBlockingHit ?  FTransform(HitResult.Location): FTransform(HitResult.TraceEnd);

	AInventoryItemMaster * SpawnedItem = GetWorld()->SpawnActorDeferred<AInventoryItemMaster>(LocalItem.ItemMasterClass.Get(),
		SpawnTransform);
	
	SpawnedItem->ItemAmount = InventorySlots[Index].Amount;
	SpawnedItem->FinishSpawning(SpawnTransform, true);

	if (InventorySlots[Index].Amount > 0)
	{
		InventorySlots[Index] = FItemData(); //Null 값으로 초기화
		InventorySlots[Index].Amount = 0;
		UpdateInventorySlot(Index);
	}
}

FItemData UInventory::GetItemIndex(int32 Index)
{
	LocalIndex = Index;
	//GetItemIndex는 인덱스 값을 주면 해당 인덱스에 있는
	//InventorySlots에 아이템 주는것이다
	if (InventorySlots.IsEmpty())
	{
		return FItemData();
	}
	return InventorySlots[Index];
}
bool UInventory::CheckForEmptySlot()
{
	int32 FoundIndex = INDEX_NONE;
	for (int32 Index = 0; Index < InventorySlots.Num(); Index++)
	{
		if (InventorySlots[Index].ItemName.IsNone())
		{
			FoundIndex = Index;
			LocalIndex = Index;
			break;
		}
	}

	if (FoundIndex == INDEX_NONE)
	{
		return false;
	}
	return true;
}
void UInventory::CreateExaminationUI(int32 Index)
{
	if (InventorySlots[Index].BExaminationMesh)
	{
		ExaminationWidgetRef->UpdateWidget(Index);
		InventoryMenuWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
		InventoryMenuWidgetRef->GetChildAt(Index)->CloesDropDownMenu(Index);
		ExaminationWidgetRef->AddToViewport();
		PlayerRef->bInventoryOpen = true;
	}
	else
	{
		ensure(InventorySlots[Index].BExaminationMesh);

	}
}