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
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<APawn> VRPawnClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APlayerController> VRPlayerControllerClass = nullptr;
};



