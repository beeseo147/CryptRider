// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "InventoryItemMaster.generated.h"

struct FItemData;

UCLASS(BlueprintType)
class CRYPTRIDER_API UPickUpPrompt : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable ,meta = (DisplayName = "PickUp"))
	void TogglePrompt(bool CanPickUp);
};

UCLASS()
class CRYPTRIDER_API AInventoryItemMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItemMaster();

protected:
	virtual void PreRegisterAllComponents() override;
	virtual void PostRegisterAllComponents() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetInventoryDataTableRow(FItemData* InItemData);

	UFUNCTION()
	void OnGrab();
	UFUNCTION()
	void OnReleaseGrab();
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowAbstract = true), Category = "BaseMesh")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowAbstract = true), Category = "Prompt")
	class UWidgetComponent* Prompt;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (AllowAbstract = true), Category = "Sphere")
	class USphereComponent* Sphere;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "ItemDataLocation")
	float PickUpDistance = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDataLocation")
	float WidgetDistanceAboutMesh = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDataLocation")
	bool UpdateActor = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FDataTableRowHandle InventoryData;

	const FItemData* InventoryDataTableRow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ACharacter* Player;
	UPROPERTY()
	int32 ItemAmount{ 0 };
};
