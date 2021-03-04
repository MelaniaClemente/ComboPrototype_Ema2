#include "DhumaCommands.h"

#define LOCTEXT_NAMESPACE "FDhumaToolsModule"

void FDhumaCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "DhumaTools", "Execute DhumaTools", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
