// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/FileHelper.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "GameFramework/SaveGame.h"
#include <Kismet/GameplayStatics.h>
#include "K2Node_Functions.h"

bool UK2Node_Functions::SaveGameCustomPath(USaveGame* SaveGameObject, const FString& Path)
{
    if (!SaveGameObject) return false;
    if (Path.IsEmpty()) return false;

    TArray<uint8> Data;
    FMemoryWriter Writer(Data, true);

    FObjectAndNameAsStringProxyArchive Ar(Writer, true);
    Ar.ArIsSaveGame = true;

    // Critical: use << instead of Serialize
    Ar << SaveGameObject;

    return FFileHelper::SaveArrayToFile(Data, *Path);
}

USaveGame* UK2Node_Functions::LoadGameFromCustomPath(const FString& Path)
{
    if (Path.IsEmpty()) return nullptr;

    TArray<uint8> Data;
    if (!FFileHelper::LoadFileToArray(Data, *Path))
    {
        return nullptr;
    }

    FMemoryReader Reader(Data, true);
    FObjectAndNameAsStringProxyArchive Ar(Reader, true);
    Ar.ArIsSaveGame = true;

    USaveGame* LoadedObject = nullptr;
    Ar << LoadedObject;   // reconstructs the correct subclass

    return LoadedObject;
}
