// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PortalsPluginEditor.h"
#include "UnrealEd.h"
#include "ComponentVisualizers/PortalComponentVisualizer.h"
#include "Components/PortalComponent.h"

#define LOCTEXT_NAMESPACE "FPortalsPluginEditorModule"

DEFINE_LOG_CATEGORY(PortalsEditorLog);

void FPortalsPluginEditorModule::StartupModule()
{
	RegisterVisualizers();
}

void FPortalsPluginEditorModule::ShutdownModule()
{
	UnregisterVisualizers();
}

void FPortalsPluginEditorModule::RegisterVisualizers()
{
	if (GUnrealEd != nullptr)
	{
		TSharedPtr<FComponentVisualizer> Visualizer = MakeShareable(new FPortalComponentVisualizer());

		if (Visualizer.IsValid())
		{
			GUnrealEd->RegisterComponentVisualizer(UPortalComponent::StaticClass()->GetFName(), Visualizer);
			Visualizer->OnRegister();
		}

	}
}

void FPortalsPluginEditorModule::UnregisterVisualizers()
{
	if (GUnrealEd != nullptr)
	{
		GUnrealEd->UnregisterComponentVisualizer(UPortalComponent::StaticClass()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPortalsPluginEditorModule, PortalsPluginEditor)
