// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldieFunctions.h"

// Logs to the console (for Blueprint Usage)
void UGoldieFunctions::UELog(const ECustomLogVerbosity DisplayType, const FString& Message)
{
	switch (DisplayType)
	{
	case ECustomLogVerbosity::Display:
		UE_LOG(LogTemp, Display, TEXT("%s"), *Message);
		break;
	case ECustomLogVerbosity::Log:
		UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
		break;
	case ECustomLogVerbosity::Warning:
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		break;
	case ECustomLogVerbosity::Error:
		UE_LOG(LogTemp, Error, TEXT("%s"), *Message);
		break;
	case ECustomLogVerbosity::Fatal:
		UE_LOG(LogTemp, Fatal, TEXT("%s"), *Message);
		break;
	case ECustomLogVerbosity::Verbose:
		UE_LOG(LogTemp, Verbose, TEXT("%s"), *Message);
		break;
	case ECustomLogVerbosity::VeryVerbose:
		UE_LOG(LogTemp, VeryVerbose, TEXT("%s"), *Message);
		break;
	}
}

// Gets the progress of an Async loaded asset
const float UGoldieFunctions::GetAsyncAssetProgress(const FName AssetName)
{
	return GetAsyncLoadPercentage(AssetName);
}

// Gets the String assetname of the given Soft Object
const FString UGoldieFunctions::GetSoftAssetString(const TSoftObjectPtr<UObject> Asset)
{
	FString Path = Asset.ToString();
	FString AssetName = FPackageName::GetShortName(FName(*Path));
	return AssetName.Left(AssetName.Find(".", ESearchCase::IgnoreCase, ESearchDir::FromStart));
}

// Gets the Name assetname of the given Soft Object
const FName UGoldieFunctions::GetSoftAssetName(const TSoftObjectPtr<UObject> Asset)
{
	FString Path = Asset.ToString();
	FString AssetName = FPackageName::GetShortName(FName(*Path));
	return FName(AssetName.Left(AssetName.Find(".", ESearchCase::IgnoreCase, ESearchDir::FromStart)));
}

// Gets all the saves within the SaveGames folder
const TArray<FString> UGoldieFunctions::GetAllSaves()
{
	//////////////////////////////////////////////////////////////////////////////
	class FFindSavesVisitor : public IPlatformFile::FDirectoryVisitor
	{
	public:
		FFindSavesVisitor() {}

		virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
		{
			if (!bIsDirectory)
			{
				FString FullFilePath(FilenameOrDirectory);
				if (FPaths::GetExtension(FullFilePath) == TEXT("sav"))
				{
					FString CleanFilename = FPaths::GetBaseFilename(FullFilePath);
					CleanFilename = CleanFilename.Replace(TEXT(".sav"), TEXT(""));
					SavesFound.Add(CleanFilename);
				}
			}
			return true;
		}
		TArray<FString> SavesFound;
	};
	//////////////////////////////////////////////////////////////////////////////

	TArray<FString> Saves;
	const FString SavesFolder = FPaths::ProjectSavedDir() + TEXT("SaveGames");

	if (!SavesFolder.IsEmpty())
	{
		FFindSavesVisitor Visitor;
		FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*SavesFolder, Visitor);
		Saves = Visitor.SavesFound;
	}

	return Saves;
}