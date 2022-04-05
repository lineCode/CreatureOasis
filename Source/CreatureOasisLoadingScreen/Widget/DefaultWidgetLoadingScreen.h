#pragma once

class SDefaultWidgetLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDefaultWidgetLoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	/** Rather to show the ... indicator */
	EVisibility GetLoadIndicatorVisibility() const;
	
	/** Loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};
