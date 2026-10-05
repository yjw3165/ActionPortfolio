// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ActionPortfolio : ModuleRules
{
	public ActionPortfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ActionPortfolio",
			"ActionPortfolio/Variant_Platforming",
			"ActionPortfolio/Variant_Platforming/Animation",
			"ActionPortfolio/Variant_Combat",
			"ActionPortfolio/Variant_Combat/AI",
			"ActionPortfolio/Variant_Combat/Animation",
			"ActionPortfolio/Variant_Combat/Gameplay",
			"ActionPortfolio/Variant_Combat/Interfaces",
			"ActionPortfolio/Variant_Combat/UI",
			"ActionPortfolio/Variant_SideScrolling",
			"ActionPortfolio/Variant_SideScrolling/AI",
			"ActionPortfolio/Variant_SideScrolling/Gameplay",
			"ActionPortfolio/Variant_SideScrolling/Interfaces",
			"ActionPortfolio/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
