#include "DhumaTools.h"
#include "DhumaStyle.h"
#include "DhumaCommands.h"
#include "Misc/MessageDialog.h"
#include "WidgetBlueprint.h"
#include "ToolMenus.h"
#include "LevelEditor.h"
#include "Blueprint/UserWidget.h"
#include "EditorUtilityWidget.h"

static const FName DhumaToolTabName("Dhuma Tools");

#define LOCTEXT_NAMESPACE "FDhumaToolsModule"

void FDhumaToolsModule::StartupModule()
{
	FDhumaStyle::Initialize();
	FDhumaStyle::ReloadTextures();

	FDhumaCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDhumaCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FDhumaToolsModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDhumaToolsModule::RegisterMenus));
}

void FDhumaToolsModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDhumaStyle::Shutdown();

	FDhumaCommands::Unregister();
}

void FDhumaToolsModule::PluginButtonClicked()
{
	const FName TabName = "Dhuma Tools";

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	TSharedPtr<FTabManager> TabManager = LevelEditorModule.GetLevelEditorTabManager();

	if (!TabManager->HasTabSpawner(TabName))
	{
		UWidgetBlueprint* WidgetBlueprint = LoadObject<UWidgetBlueprint>(nullptr, TEXT("/DhumaTools/EditorWidget/DhumaToolsWidget.DhumaToolsWidget"));
		if (!WidgetBlueprint)
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to open Dhuma Tools"));
			return;
		}

		TabManager->RegisterTabSpawner(TabName, FOnSpawnTab::CreateStatic(&FDhumaToolsModule::CreateTab, WidgetBlueprint))
			.SetDisplayName(FText::FromString(TabName.ToString()))
			.SetMenuType(ETabSpawnerMenuType::Hidden);
	}

	TabManager->InvokeTab(TabName);
}

TSharedRef<SDockTab> FDhumaToolsModule::CreateTab(const FSpawnTabArgs& SpawnTabArgs, UWidgetBlueprint* WidgetBlueprint)
{
	UWorld* World = GEditor->GetEditorWorldContext().World();

	TSharedRef<SDockTab> NewDockTab = SNew(SDockTab);

	if (WidgetBlueprint->GeneratedClass->IsChildOf<UUserWidget>())
	{
		TSubclassOf<UUserWidget> WidgetClass = WidgetBlueprint->GeneratedClass;
		UEditorUtilityWidget* NewWidget = CreateWidget<UEditorUtilityWidget>(World, WidgetClass);
		if (NewWidget)
			NewDockTab->SetContent(NewWidget->TakeWidget());
	}

	return NewDockTab;
}

void FDhumaToolsModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDhumaCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDhumaCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDhumaToolsModule, DhumaTools)
