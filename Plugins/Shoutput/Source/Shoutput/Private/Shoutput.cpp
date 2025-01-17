// Copyright Epic Games, Inc. All Rights Reserved.

#include "Shoutput.h"
#include "ShoutputStyle.h"
#include "ShoutputCommands.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "UI/ShoutputLogWidget.h"

static const FName ShoutputTabName("Shoutput");

#define LOCTEXT_NAMESPACE "FShoutputModule"

void FShoutputModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FShoutputStyle::Initialize();
	FShoutputStyle::ReloadTextures();

	FShoutputCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FShoutputCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FShoutputModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FShoutputModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ShoutputTabName, FOnSpawnTab::CreateRaw(this, &FShoutputModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FShoutputTabTitle", "Shoutput"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	//OutputLogHistory = MakeShareable(new FOutputLogHistory);

	MessageSource = MakeShared<FShoutputLogMessageSource>();

	GLog->AddOutputDevice(MessageSource.Get());
	GLog->SerializeBacklog(MessageSource.Get());
	//GLog->AddOutputDevice(this);
	//GLog->SerializeBacklog(this);
}

void FShoutputModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	GLog->RemoveOutputDevice(MessageSource.Get());
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FShoutputStyle::Shutdown();
	FShoutputCommands::Unregister();
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ShoutputTabName);
}

TSharedRef<SDockTab> FShoutputModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FShoutputModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("Shoutput.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(ShoutputLogWidget)
			
			
		];
	/*return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(ShoutputWidget)
			.Messages(Messages)
			.MessageSource(MessageSource)
			
		];*/
}

void FShoutputModule::Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category)
{
	// Capture all incoming messages and store them in history
	//SOutputLog::CreateLogMessages(V, Verbosity, Category, Messages);
	//Messages.Add(MakeShared<FShoutputLogMessage>(MakeShared<FString>(V), Verbosity)); // todo delete
	MessageSource->Messages.Add(MakeShared<FShoutputLogMessage>(MakeShared<FString>(V), Verbosity, Category));
}

void FShoutputModule::SerializeRecord(const UE::FLogRecord& Record)
{
	FOutputDevice::SerializeRecord(Record);
}

void FShoutputModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ShoutputTabName);
}

void FShoutputModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FShoutputCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FShoutputCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShoutputModule, Shoutput)