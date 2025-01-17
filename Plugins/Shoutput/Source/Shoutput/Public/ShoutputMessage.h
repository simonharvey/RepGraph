// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Internationalization/Regex.h"

/**
 * 
 */
struct SHOUTPUT_API FShoutputLogMessage//: public TSharedFromThis<FShoutputLogMessage>
{
	TSharedRef<FString> Message;
	const ELogVerbosity::Type Verbosity;
	const FName Category;

	FShoutputLogMessage(TSharedRef<FString> InMessage, ELogVerbosity::Type InVerbosity, const FName InCategory)
		: Message(InMessage)
		, Verbosity(InVerbosity)
		, Category(InCategory)
	{
		
	}
};

inline bool CompareNames(const FName& A, const FName& B)
{
	return A.ToString() < B.ToString();
}

struct SHOUTPUT_API FShoutputLogMessageSource
	: public TSharedFromThis<FShoutputLogMessageSource>
	, public FOutputDevice
{
	virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override
	{
		if (Category != "LogBlueprintUserMessages")
			return;

		FRegexPattern Pattern(TEXT("\\[(.+)\\]\\s(.+):\\s(.+)"));
		FRegexMatcher Matcher(Pattern, V);
		if (Matcher.FindNext())
		{
			auto BP = Matcher.GetCaptureGroup(1);
			auto Role = Matcher.GetCaptureGroup(2);
			auto Message = Matcher.GetCaptureGroup(3);
		}
		
		Messages.Add(MakeShared<FShoutputLogMessage>(MakeShared<FString>(V), Verbosity, Category));
		Categories.Add(Category);
		//Cats.Add(Category);

		KnownCategories.AddUnique(Category);
		KnownCategories.Sort(CompareNames);
	}

	TArray<TSharedPtr<FShoutputLogMessage>> Messages;
	TSet<FName> Categories;
	TArray<FName> KnownCategories;
	//UE::Slate::Containers::TObservableArray<FName> Cats;

	TArray<FName> GetCategoriesArray() const { return Categories.Array(); }
};