#include "DefaultWidgetLoadingScreen.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Widgets/Images/SThrobber.h"

#include "MoviePlayer.h"

void SDefaultWidgetLoadingScreen::Construct(const FArguments& InArgs)
{
	FSlateBrush *BGBrush = new FSlateBrush();
	BGBrush->TintColor = FLinearColor(0.012f, 0.012f, 0.5f, 1.0f);
	
	ChildSlot
		[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBorder)	
			.BorderImage(BGBrush)
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SHeader)
			.Content()
			[
				SNew(STextBlock)
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 32))
				.Text(FText::FromString(TEXT("Loading Creature Oasis")))
			]
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Padding(FMargin(10.0f))
			[
				SNew(SThrobber)
				.Visibility(this, &SDefaultWidgetLoadingScreen::GetLoadIndicatorVisibility)
			]
		]
	];
}

EVisibility SDefaultWidgetLoadingScreen::GetLoadIndicatorVisibility() const
{
	bool Vis = GetMoviePlayer()->IsLoadingFinished();
	return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
}
