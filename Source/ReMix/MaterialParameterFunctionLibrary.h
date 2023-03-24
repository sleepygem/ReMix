// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterItemAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MaterialParameterFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FItemMaterialSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInstanceDynamic* Material;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FName, FLinearColor> ColourParameters;

	void AddColourParameter(FName ParameterName, FLinearColor NewColour)
	{
		ColourParameters.Add(ParameterName, NewColour);
	}

	FItemMaterialSettings()
	{
		Material = nullptr;
	}

	FItemMaterialSettings(UMaterialInstanceDynamic* InMaterial)
	{
		Material = InMaterial;
	}
};
/**
 * 
 */
UCLASS()
class REMIX_API UMaterialParameterFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void AddColourParameter(UPARAM(ref) FItemMaterialSettings& MaterialSettings, FName ParameterName, FLinearColor NewColourValue);

	UFUNCTION(BlueprintCallable)
	static bool GetAssociatedParameters(UObject* WorldContextObject, UCharacterItemAsset* ItemAsset, FName MaterialSlot, UMaterialInterface* Material, bool bRandomizeValues, 
		FItemMaterialSettings& MaterialSettings);
};
