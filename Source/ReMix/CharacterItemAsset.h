// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterItemAsset.generated.h"

/**
* Defines an exposed colour parameter for a material used by a CharacterItemAsset
*/
USTRUCT(BlueprintType)
struct FColourParameter
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText DisplayName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName MaterialSlot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName ParameterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bUseStandardColourSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FLinearColor> AdditionalColourOptions;

	FLinearColor GetRandomColour()
	{
		const int32 ColourNum = AdditionalColourOptions.Num();
		if (ColourNum > 0)
		{
			return AdditionalColourOptions[FMath::RandRange(0, ColourNum - 1)];
		}
		return FLinearColor();
	}

	FColourParameter()
	{
		bUseStandardColourSet = true;
	}
};
/**
 * 
 */
UCLASS(BlueprintType)
class REMIX_API UCharacterItemAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Type of this item, set in native parent class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "User Parameters")
	TArray<FColourParameter> ColourParameters;

	/** Returns the logical name, equivalent to the primary asset id */
	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;

	/** Overridden to use saved type */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
