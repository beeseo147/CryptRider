// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItemMaster.generated.h"

struct FItemData;

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
protected:
	UPROPERTY(VisibleAnywhere, meta = (AllowAbstract = true), Category = "BaseMesh")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, meta = (AllowAbstract = true), Category = "Prompt")
	class UWidgetComponent* Prompt;

	UPROPERTY(VisibleAnywhere, meta = (AllowAbstract = true), Category = "Sphere")
	class USphereComponent* Sphere;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FDataTableRowHandle InventoryData;

	const FItemData* InventoryDataTableRow;
};
