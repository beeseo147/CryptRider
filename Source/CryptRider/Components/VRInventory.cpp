// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VRInventory.h"
#include "Actors/VR/VRCharacter.h"
#include "Actors/Controller/CryptRiderPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Inventory/InventoryItemMaster.h"
#include "UI/VRInventoryMenuUserWidget.h"
UVRInventory::UVRInventory()
{

}

void UVRInventory::BeginPlay()
{
	Super::Super::BeginPlay();

	InventorySlots.SetNum(InventoryCount);
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	VRPlayerRef = Cast<AVRCharacter>(OwningPawn);
	check(VRPlayerRef);

	AController* Controller = OwningPawn->GetController();
	PlayerControllerRef = Cast<ACryptRiderPlayerController>(Controller);
	//VRInventoryMenuWidgetRef = VRPlayerRef->InventoryMenuWidget;
	ExaminationWidgetRef = VRPlayerRef->ExaminationWidget;

	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AExaminationActor::StaticClass());
	if (FoundActor)
	{
		ExaminationActor = Cast<AExaminationActor>(FoundActor);
	}
	//check(VRInventoryMenuWidgetRef);
	check(ExaminationWidgetRef);
	check(ExaminationActor);
}

void UVRInventory::DropItem(int32 Index)
{
	Super::DropItem(Index);
	UCameraComponent* PlayerCamera = VRPlayerRef->GetVRCameraComponent();
	FVector CameraLocation = PlayerCamera->GetComponentLocation();
	FVector CameraVector = PlayerCamera->GetForwardVector();
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(PlayerCamera, CameraLocation, CameraLocation + CameraVector * 200,
		ETraceTypeQuery::TraceTypeQuery12, false,
		TArray<class AActor*>(), EDrawDebugTrace::None, HitResult, true);

	FTransform SpawnTransform = HitResult.bBlockingHit ? FTransform(HitResult.Location) : FTransform(HitResult.TraceEnd);

	AInventoryItemMaster* SpawnedItem = GetWorld()->SpawnActorDeferred<AInventoryItemMaster>(LocalItem.ItemMasterClass.Get(),
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

bool UVRInventory::AddItem(UPARAM(ref)FItemData& InItem)
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
				LocalItem.Amount -= InventorySlots[LocalIndex].MaxStackAmount - InventorySlots[LocalIndex].Amount;
				InventorySlots[LocalIndex].Amount = LocalMaxAmountStack;
				UpdateInventorySlot(LocalIndex);
				AddItem(LocalItem);
			}

		}
		else
		{
			if (CheckForEmptySlot())
			{
				if (LocalMaxAmountStack >= LocalItem.Amount)
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

void UVRInventory::UpdateInventorySlot(int32 Index)
{
	check(VRPlayerRef->InventoryMenuWidget);
	UMySlotUserWidget* T = VRPlayerRef->InventoryMenuWidget->GetChildAt(Index);
	//일단 해당 번호의 인덱스에 접근으로..
	T->UpdateSlot(Index);
}
