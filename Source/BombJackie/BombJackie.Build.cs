// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BombJackie : ModuleRules
{
	public BombJackie(ReadOnlyTargetRules Target) : base(Target)
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
			"BombJackie",
			"BombJackie/Variant_Platforming",
			"BombJackie/Variant_Platforming/Animation",
			"BombJackie/Variant_Combat",
			"BombJackie/Variant_Combat/AI",
			"BombJackie/Variant_Combat/Animation",
			"BombJackie/Variant_Combat/Gameplay",
			"BombJackie/Variant_Combat/Interfaces",
			"BombJackie/Variant_Combat/UI",
			"BombJackie/Variant_SideScrolling",
			"BombJackie/Variant_SideScrolling/AI",
			"BombJackie/Variant_SideScrolling/Gameplay",
			"BombJackie/Variant_SideScrolling/Interfaces",
			"BombJackie/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
