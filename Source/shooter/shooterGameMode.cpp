// Copyright Epic Games, Inc. All Rights Reserved.

#include "shooterGameMode.h"
#include "shooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AshooterGameMode::AshooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
