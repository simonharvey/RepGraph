// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShoutputMessage.h"
#include "Modules/ModuleManager.h"
//#include "Shoutput.generated.h"

class FOutputLogHistory;
class FToolBarBuilder;
class FMenuBuilder;

class FShoutputModule : public IModuleInterface, public FOutputDevice
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

protected:
	virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category) override;

public:
	virtual void SerializeRecord(const UE::FLogRecord& Record) override;

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	TArray<TSharedPtr<FShoutputLogMessage>> Messages;

	// test
	TSharedPtr<FShoutputLogMessageSource> MessageSource;
	//TSharedPtr<FOutputLogHistory> OutputLogHistory;

	/** All log messsges since this module has been started */
	//TArray< TSharedPtr<FOutputLogMessage> > Messages;
};
