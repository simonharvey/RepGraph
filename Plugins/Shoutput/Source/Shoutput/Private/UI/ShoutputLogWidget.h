// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShoutputMessage.h"
#include "ShoutputSettings.h"
#include "Widgets/SCompoundWidget.h"

#include "Editor/PropertyEditor/Private/SDetailsView.h"
/**
 * 
 */

class SChannelListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SChannelListWidget)
	{
	}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, TSharedPtr<FShoutputSettings>)
	{
/*		ChildSlot
		[
			SAssignNew(DetailsView, SDetailsView)
		];*/
		//DetailsView->SetObject(InArgs._ShoutputSettings.Get());

		/*FOnGetPropertyTypeCustomizationInstance CustomColorPickerFactory = FOnGetPropertyTypeCustomizationInstance::CreateLambda(
					[PickerTarget]
				{
					return MakeShared<FComposureColorPickerCustomization>(PickerTarget);
				});*/

		/*DetailsView->RegisterInstancedCustomPropertyTypeLayout(
			GET_MEMBER_NAME_CHECKED(UShoutputSettings, Channels),
			FOnGetPropertyTypeCustomizationInstance::CreateLambda([=]
			{
				
			})
			);*/
	}

private:
	//TSharedPtr<SDetailsView> DetailsView;
};

class SHOUTPUT_API ShoutputLogWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(ShoutputLogWidget){}
		SLATE_ARGUMENT(TSharedPtr<FShoutputLogMessageSource>, Source)
	//SLATE_ARGUMENT(TSharedPtr<FShoutputSettings>, Settings)
	//SLATE_ATTRIBUTE(UShoutputSettings *, ShoutputSettings);

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void CreateChannel();
	
	TSharedRef<SWidget> MakeEditBar();
	//TSharedPtr<FShoutputSettings> Settings;
	//TSharedPtr<SListView<FShoutputChannel>> ListView;
	//TSharedPtr<SChannelListWidget> ChannelsWidget;
};
