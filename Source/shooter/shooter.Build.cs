// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class shooter : ModuleRules
{
	public shooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "EnhancedInput", "Niagara", "GameplayTasks" });
	}
}
