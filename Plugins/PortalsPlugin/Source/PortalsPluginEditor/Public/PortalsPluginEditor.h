// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(PortalsEditorLog, Log, All);

class FPortalsPluginEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	virtual void RegisterVisualizers();
	virtual void UnregisterVisualizers();
};
