// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class PortalsPluginEditor : ModuleRules
{
	public PortalsPluginEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"PhysicsCore",
				"PortalsPlugin"
				// ... add private dependencies that you statically link with here ...	
			}
			);

        if (Target.Type == TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "UnrealEd",
                    "LevelEditor",
                    "EditorStyle",
                    "Slate",
                    "SlateCore",
                    "PropertyEditor"
                }
            );
        }

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
