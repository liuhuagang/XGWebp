// Copyright Xiao Gang. All Rights Reserved.
using UnrealBuildTool;

public class XGWebp : ModuleRules
{
	public XGWebp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
	
		
		PrivateIncludePaths.AddRange(
			new string[] {

			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
		


			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
            {       "Core",
                "CoreUObject",
				"Engine",
                "RenderCore",

                "XGWebpLibrary",
                "Projects"

            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

			}
			);
	}
}
