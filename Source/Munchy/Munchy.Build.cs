// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Munchy : ModuleRules
{
	public Munchy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}