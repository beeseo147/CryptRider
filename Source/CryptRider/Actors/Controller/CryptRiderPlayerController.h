// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "CryptRiderPlayerController.generated.h"

class UInventoryMenuUserWidget;
class UMainMenu;
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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMainMenu* UMainMenuWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UInventoryMenuUserWidget* InventoryMenuWidget;
};
