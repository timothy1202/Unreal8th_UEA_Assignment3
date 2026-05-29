// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEA : ModuleRules
{
	public UEA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Slate", "SlateCore" });

		// Private 폴더에서 모듈 루트(UEAGameMode.h 등)에 접근할 수 있도록 경로 추가
		PrivateIncludePaths.Add(ModuleDirectory);
	}
}
