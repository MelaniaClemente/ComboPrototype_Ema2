#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;

class FMenuBuilder;

class FDhumaToolsModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void PluginButtonClicked();

private:
	void RegisterMenus();

	static TSharedRef<SDockTab> CreateTab(const FSpawnTabArgs& SpawnTabArgs, class UWidgetBlueprint* WidgetBlueprint);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
