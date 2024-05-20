// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UI/ExaminationWidget.h"
#include "CryptRiderPlayerController.generated.h"

class UInventoryMenuUserWidget;
class UMainMenu;
class UExaminationWidget;
/**
 *
 */
UCLASS()
class CRYPTRIDER_API ACryptRiderPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	// End Actor interface
public:
	UPROPERTY(BlueprintReadWrite)
	UMainMenu* UMainMenuWidget;

	UPROPERTY(BlueprintReadWrite)
	UInventoryMenuUserWidget* InventoryMenuWidget;

	UPROPERTY(BlueprintReadWrite)
	UExaminationWidget* ExaminationWidget;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool IsInventoryOpen = false;
};
