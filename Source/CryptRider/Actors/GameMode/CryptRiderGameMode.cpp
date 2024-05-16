// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptRiderGameMode.h"
#include "CryptRider/Actors/Charter/CryptRiderCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACryptRiderGameMode::ACryptRiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}