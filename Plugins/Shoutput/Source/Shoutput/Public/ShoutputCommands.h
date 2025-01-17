// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ShoutputStyle.h"

class FShoutputCommands : public TCommands<FShoutputCommands>
{
public:

	FShoutputCommands()
		: TCommands<FShoutputCommands>(TEXT("Shoutput"), NSLOCTEXT("Contexts", "Shoutput", "Shoutput Plugin"), NAME_None, FShoutputStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};