#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Item/ItemData.h"
#include "Data/Item/InventoryItem.h"
#include "Actors/Inventory/ExaminationActor.h"
#include "Inventory.generated.h"
struct FItemData;
class UInventoryMenuUserWidget;
class AInventoryItemMaster;
class UExaminationWidget;
class ACryptRiderPlayerController;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRIDER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

	friend class UInventoryMenuUserWidget;
	friend class UExaminationWidget;

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

	UPROPERTY(BlueprintReadWrite)
	UExaminationWidget* ExaminationWidgetRef = nullptr;

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

	UPROPERTY(BlueprintReadOnly)
	class ACryptRiderPlayerController* PlayerControllerRef;

	/** Please add a variable what you made */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "DEfalut")
	TObjectPtr<AExaminationActor> ExaminationActor;

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
	UFUNCTION(BlueprintCallable)
	void CreateExaminationUI(int32 Index);

	UFUNCTION(BlueprintPure,BlueprintCallable)
	FItemData GetItemIndex(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool CheckForEmptySlot();
};
