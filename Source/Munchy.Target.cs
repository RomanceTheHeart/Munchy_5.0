// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MunchyTarget : TargetRules
{
	public MunchyTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Munchy");
	}
}