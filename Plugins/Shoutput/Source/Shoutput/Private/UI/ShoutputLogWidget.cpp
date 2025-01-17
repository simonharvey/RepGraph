// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoutputLogWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void ShoutputLogWidget::Construct(const FArguments& InArgs)
{
	//auto Settings = InArgs._Settings;//UShoutputSettings::Get();

	/*Settings->OnSettingChanged().AddLambda([](UObject* Obj, struct FPropertyChangedEvent& Evt)
	{
		UE_LOG(LogTemp, Warning, TEXT("Changed!"));
	});*/

	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		[
			MakeEditBar()
		]
	];
}

void ShoutputLogWidget::CreateChannel()
{
}

TSharedRef<SWidget> ShoutputLogWidget::MakeEditBar()
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		[
			SNew(SButton)
			.OnClicked_Lambda([&]()
			{
				//Settings->ChannelSettings.Add(nullptr);
				/*auto Sh = UShoutputSettings::Get();
				Sh->bEnableSearch = !Sh->bEnableSearch;
				//auto Ptr = UShoutputSettings::GetPtr();
				//Ptr->bEnableSearch = !Ptr->bEnableSearch;
				UE_LOG(LogTemp, Warning, TEXT("Should have changed?"));
				//Ptr->Modify();
				Sh->Modify();
				Sh->SaveConfig();*/
				
				return FReply::Handled();
			})
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
