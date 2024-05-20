// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CryptRider : ModuleRules
{
	public CryptRider(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine",
			"InputCore", "EnhancedInput", "UMG",
            "Paper2D","GameplayTasks"
            });

        PublicIncludePaths.Add("CryptRider");
        PublicIncludePaths.Add("CryptRider/Actors");
    }
}
