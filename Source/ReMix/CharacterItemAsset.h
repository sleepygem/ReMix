// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterItemAsset.generated.h"

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

	/** Returns the logical name, equivalent to the primary asset id */
	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;

	/** Overridden to use saved type */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
