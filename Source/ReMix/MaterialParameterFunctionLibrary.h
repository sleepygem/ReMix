// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterItemAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MaterialParameterFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FColourParameterSerializable
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ParameterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor Color;

	FColourParameterSerializable()
	{

	}

	FColourParameterSerializable(FName InParamName, FLinearColor InColor)
	{
		ParameterName = InParamName;
		Color = InColor;
	}
};

USTRUCT(BlueprintType)
struct FItemMaterialSettingsSerializable
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName MaterialSlot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface* Material;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FColourParameterSerializable> ColourParameters;

	FItemMaterialSettingsSerializable()
	{

	}
};

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

	UFUNCTION(BlueprintCallable)
	static TArray<FItemMaterialSettingsSerializable> MakeMaterialSettingsSerializable(UPARAM(ref) TMap<FName, FItemMaterialSettings>& MaterialSettings);

	UFUNCTION(BlueprintCallable)
	static TMap<FName, FItemMaterialSettings> MakeInstancedMaterialSettings(UObject* WorldContextObject, UPARAM(ref) TArray<FItemMaterialSettingsSerializable>& SerializedSettings);

	UFUNCTION(BLueprintCallable, BlueprintPure, meta=(CompactNodeTitle = "FindRef"))
	static bool FindItemMaterialSettings(FName Name, UPARAM(ref) TMap<FName, FItemMaterialSettings>& MaterialSettings, FItemMaterialSettings& OutSettings);
};
