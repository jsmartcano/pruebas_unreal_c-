// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class proyecto_de_ceroEditorTarget : TargetRules
{
	public proyecto_de_ceroEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "proyecto_de_cero" } );
	}
}
