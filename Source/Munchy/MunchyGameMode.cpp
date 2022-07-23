// Copyright Epic Games, Inc. All Rights Reserved.

#include "MunchyGameMode.h"
#include "MunchyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMunchyGameMode::AMunchyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
