#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DhumaStyle.h"

class FDhumaCommands : public TCommands<FDhumaCommands>
{
public:
	FDhumaCommands()
		: TCommands<FDhumaCommands>(TEXT("DhumaTools"), NSLOCTEXT("Contexts", "DhumaTools", "Dhuma Tools Plugin"), NAME_None, FDhumaStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> PluginAction;
};
