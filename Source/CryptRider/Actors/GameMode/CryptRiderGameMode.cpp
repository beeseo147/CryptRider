// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptRiderGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "HeadMountedDisplayFunctionLibrary.h"

ACryptRiderGameMode::ACryptRiderGameMode()
	: Super()
{
	{
		ConstructorHelpers::FClassFinder<APawn> Asset(TEXT("/Script/Engine.Blueprint'/Game/VR/BP_VRPawn.BP_VRPawn'_C"));
		check(Asset.Class);
		VRPawnClass = Asset.Class;
	}
}

FString ACryptRiderGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	const bool bVR = UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled();
	if (bVR)
	{
		DefaultPawnClass = VRPawnClass;
	}
	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}
