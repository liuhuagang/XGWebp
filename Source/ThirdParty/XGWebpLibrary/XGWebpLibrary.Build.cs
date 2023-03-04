// Copyright 2023 XiaoGang 

using System.IO;
using UnrealBuildTool;

public class XGWebpLibrary : ModuleRules
{
    public XGWebpLibrary(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;


        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
           

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "libwebp.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "libwebpdemux.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "libwebpmux.lib"));

        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {

        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {

        }
    }
}
