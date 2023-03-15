// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ReMixTarget : TargetRules
{
	public ReMixTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IOSPlatform.bGeneratedSYM = true;
		bDisableDebugInfo = true;
		ExtraModuleNames.AddRange( new string[] { "ReMix" } );

	}
}
