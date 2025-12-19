// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GoldieFunctions.generated.h"

UENUM(BlueprintType)
enum class ECustomLogVerbosity : uint8
{
	Display UMETA(ToolTip = "Prints a message to the console and log file. (Grey)"),
	Log UMETA(ToolTip = "Prints a message to the log file, however, it does not print to the console. (Grey)"),
	Warning UMETA(ToolTip = "Prints a warning to the console and log file. Commandlets and the editor collect and report warnings. (Yellow)"),
	Error UMETA(ToolTip = "Prints an error to the console and log file. Commandlets and the editor collect and report errors. Error messages result in a commandlet failure. (Red)"),
	Fatal UMETA(ToolTip = "Always prints a fatal error to the console and log file, then crashes even if logging is disabled."),
	Verbose UMETA(ToolTip = "Prints a verbose message to a log file if Verbose logging is enabled for the given category. This is usually used for detailed logging."),
	VeryVerbose UMETA(ToolTip = "Prints a verbose message to a log file. If VeryVerbose logging is enabled, then this is used for detailed logging that would otherwise spam output.")
};

UCLASS()
class GOLDIELIBRARY_API UGoldieFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Logs to the console (for Blueprint Usage)
	UFUNCTION(BlueprintCallable, Category = "Goldie Library|Debugging")
	static void UELog(const ECustomLogVerbosity DisplayType, const FString& Message);

	//------------------------------//
	//		Async Functions			//
	//------------------------------//

	// Gets the progress of an Async loaded asset
	UFUNCTION(BlueprintCallable, Category = "Goldie Library|Async")
	static const float GetAsyncAssetProgress(const FName AssetName = TEXT("/Game/"));
	
	// Gets the String assetname of the given Soft Object
	UFUNCTION(BlueprintPure, Category = "Goldie Library|Async")
	static const FString GetSoftAssetString(const TSoftObjectPtr<UObject> Asset);
	
	// Gets the Name assetname of the given Soft Object
	UFUNCTION(BlueprintPure, Category = "Goldie Library|Async")
	static const FName GetSoftAssetName(const TSoftObjectPtr<UObject> Asset);

	// Gets all the saves within the SaveGames folder
	UFUNCTION(BlueprintPure, Category = "Goldie Library|File Management")
	static const TArray<FString> GetAllSaves();
};
