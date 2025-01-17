// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShoutputCommands.h"

#define LOCTEXT_NAMESPACE "FShoutputModule"

void FShoutputCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Shoutput", "Bring up Shoutput window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
