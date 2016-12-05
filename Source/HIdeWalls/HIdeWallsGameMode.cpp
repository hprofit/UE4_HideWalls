// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HIdeWalls.h"
#include "HIdeWallsGameMode.h"
#include "HIdeWallsPlayerController.h"
#include "HIdeWallsCharacter.h"

AHIdeWallsGameMode::AHIdeWallsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AHIdeWallsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}