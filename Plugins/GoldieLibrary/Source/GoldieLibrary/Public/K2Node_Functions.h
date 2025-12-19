// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "K2Node_Functions.generated.h"

/**
 * 
 */
UCLASS()
class GOLDIELIBRARY_API UK2Node_Functions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Goldie Library|SaveGame")
	static bool SaveGameCustomPath(USaveGame* SaveGameObject, const FString& Path);

	UFUNCTION(BlueprintCallable, Category = "Goldie Library|SaveGame")
	static USaveGame* LoadGameFromCustomPath(const FString& Path);
};
