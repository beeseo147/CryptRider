// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptRiderGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "VR/VRCharacter.h"
ACryptRiderGameMode::ACryptRiderGameMode()
	: Super()
{
	{
		ConstructorHelpers::FClassFinder<APawn> Asset(TEXT("/Script/Engine.Blueprint'/Game/VR/BP_VRPawn.BP_VRPawn_C'"));
		check(Asset.Class);
		VRPawnClass = Asset.Class;
	}
	{
		ConstructorHelpers::FClassFinder<APlayerController> Asset(TEXT("/Script/Engine.Blueprint'/Game/VR/BP_VRPlayerController.BP_VRPlayerController_C'"));
		check(Asset.Class);
		VRPawnClass = Asset.Class;
	}
}
APlayerController* ACryptRiderGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	const bool bVR = UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled();
	if (bVR)
	{
		DefaultPawnClass = VRPawnClass;
		PlayerControllerClass = VRPlayerControllerClass;
	}
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}
