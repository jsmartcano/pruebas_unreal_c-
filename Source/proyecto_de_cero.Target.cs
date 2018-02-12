// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class proyecto_de_ceroTarget : TargetRules
{
	public proyecto_de_ceroTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "proyecto_de_cero" } );
	}
}
