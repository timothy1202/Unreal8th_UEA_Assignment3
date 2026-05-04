// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEAGameMode.h"
#include "UEACharacter.h"
#include "UObject/ConstructorHelpers.h"

AUEAGameMode::AUEAGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
