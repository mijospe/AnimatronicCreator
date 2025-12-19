// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/FileHelper.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "GameFramework/SaveGame.h"
#include <Kismet/GameplayStatics.h>
#include "K2Node_Functions.h"

bool UK2Node_Functions::SaveGameCustomPath(USaveGame* SaveGameObject, const FString& Path)
{
    if (!SaveGameObject || Path.IsEmpty())
        return false;

    TArray<uint8> Data;
    if (!UGameplayStatics::SaveGameToMemory(SaveGameObject, Data))
        return false;

    return FFileHelper::SaveArrayToFile(Data, *Path);
}


USaveGame* UK2Node_Functions::LoadGameFromCustomPath(const FString& Path)
{
    if (Path.IsEmpty())
        return nullptr;

    TArray<uint8> Data;
    if (!FFileHelper::LoadFileToArray(Data, *Path))
        return nullptr;

    return UGameplayStatics::LoadGameFromMemory(Data);
}

