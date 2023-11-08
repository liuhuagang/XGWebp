// Copyright Xiao Gang. All Rights Reserved.
using UnrealBuildTool;

public class XGWebp : ModuleRules
{
    public XGWebp(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;



        PrivateIncludePaths.AddRange(
            new string[] {
                "XGWebp/Public/Core",
                "XGWebp/Public/Log",
                "XGWebp/Public/Subsystem",
                "XGWebp/Public/Type",
            }
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Engine"

            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",

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
