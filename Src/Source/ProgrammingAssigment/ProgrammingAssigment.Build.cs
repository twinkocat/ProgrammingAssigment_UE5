// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProgrammingAssigment : ModuleRules
{
	public ProgrammingAssigment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
		[
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayTags",
			"UMG",
			"Slate",
			"CommonUI",
			"LayeredUI"
		]);

		PrivateDependencyModuleNames.AddRange(
		[

		]);

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
