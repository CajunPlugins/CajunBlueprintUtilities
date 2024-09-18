// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

using UnrealBuildTool;
// ReSharper disable UseCollectionExpression

public class CajunBlueprintUtilitiesDeveloper : ModuleRules
{
	public CajunBlueprintUtilitiesDeveloper(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.AddRange(new[]
		{
			"CajunBlueprintUtilities/Private",
			"CajunBlueprintUtilitiesDeveloper/Private"
		});

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Engine",
			"KismetCompiler",
			"SlateCore",
			"UnrealEd"
		});
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"BlueprintGraph",
			"Core",
			"CoreUObject",
			"GraphEditor",
			"Kismet",
			"Slate",
			"ToolMenus",
			"ToolWidgets",
			"CajunBlueprintUtilities"
		});
	}
}