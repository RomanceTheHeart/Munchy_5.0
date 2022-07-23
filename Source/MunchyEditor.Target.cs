// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MunchyEditorTarget : TargetRules
{
	public MunchyEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Munchy");
	}
}