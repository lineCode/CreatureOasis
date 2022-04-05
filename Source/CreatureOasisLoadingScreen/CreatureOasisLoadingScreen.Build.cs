using UnrealBuildTool;

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

public class CreatureOasisLoadingScreen : ModuleRules
{
	public CreatureOasisLoadingScreen(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"MoviePlayer",
				"Slate",
				"SlateCore",
				"InputCore"
			}
		);
	}
}