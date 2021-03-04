#include "DhumaStyle.h"
#include "DhumaTools.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<FSlateStyleSet> FDhumaStyle::StyleInstance = NULL;

void FDhumaStyle::Initialize()
{
	if (StyleInstance.IsValid()) return;

	StyleInstance = Create();
	FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
}

void FDhumaStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FDhumaStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("DhumaStyle"));

	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon128x128(128.0f, 128.0f);
const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef<FSlateStyleSet> FDhumaStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("DhumaStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("DhumaTools")->GetBaseDir() / TEXT("Resources"));
	Style->Set("DhumaTools.PluginAction", new IMAGE_BRUSH(TEXT("DhumaIcon40x40"), Icon40x40));

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FDhumaStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FDhumaStyle::Get()
{
	return *StyleInstance;
}
