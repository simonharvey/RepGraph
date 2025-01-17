// Fill out your copyright notice in the Description page of Project Settings.

// https://dev.epicgames.com/documentation/en-us/unreal-engine/umg-viewmodel?application_version=5.2
// https://forums.unrealengine.com/t/extending-an-editor-with-slate-how-to-show-a-struct-property/338057
#pragma once
#include "ShoutputSettings.generated.h"

USTRUCT(BlueprintType)
struct FShoutputChannel
	//: public FStructOnScope// : public TSharedFromThis<FShoutputChannel, ESPMode::ThreadSafe>
{

	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere)
	FString Name;

	UPROPERTY(Config, EditAnywhere)
	TSet<FName> VisibleCategories;
};

/**
 * 
 */
//UCLASS(Config=EditorPerProjectUserSettings
	//meta=(DisplayName="Shoutput - normal output is just terrible"),
//	/*MinimalAPI*/)
USTRUCT(BlueprintType)
struct FShoutputSettings
	//:public UObject
//: public TSharedFromThis<FShoutputSettings>

//, public INotifyFieldValueChanged
{
	GENERATED_BODY()
public:

	/*virtual FName GetContainerName() const override { return FName("Editor"); }
	virtual FName GetCategoryName() const override { return FName("Plugins"); }
	virtual FName GetSectionName() const override { return FName("Shoutput"); }*/

	UPROPERTY(Config)
	TArray<FShoutputChannel> Channels;
	
};
