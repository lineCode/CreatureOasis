// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CreatureOasis : ModuleRules
{
	public CreatureOasis(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "NavigationSystem", "Json", "JsonUtilities", "CreatureOasisLoadingScreen", "GameplayAbilities", "GameplayTags", "GameplayTasks", "DeveloperSettings"  });
	}
}
