using UnrealBuildTool;

public class GoldieLibraryEditor : ModuleRules
{
    public GoldieLibraryEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "BlueprintGraph",
            "KismetCompiler",
            "UnrealEd",
            "Slate",
            "SlateCore"
        });

        PrivateDependencyModuleNames.Add("GoldieLibrary");
    }
}