// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlueGravityTestGameMode.h"
#include "BlueGravityTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlueGravityTestGameMode::ABlueGravityTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
