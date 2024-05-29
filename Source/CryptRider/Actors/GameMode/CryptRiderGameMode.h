// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CryptRiderGameMode.generated.h"

UCLASS(minimalapi)
class ACryptRiderGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACryptRiderGameMode();

protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;

private:
	UClass* VRPawnClass = nullptr;

};



