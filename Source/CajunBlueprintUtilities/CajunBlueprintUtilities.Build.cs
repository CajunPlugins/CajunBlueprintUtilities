// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

using UnrealBuildTool;
// ReSharper disable UseCollectionExpression

public class CajunBlueprintUtilities : ModuleRules
{
	public CajunBlueprintUtilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Engine"
		});
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"DeveloperSettings",
			"Projects",
			"UMG"
		});
	}
}