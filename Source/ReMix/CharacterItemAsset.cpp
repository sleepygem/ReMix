// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterItemAsset.h"

FString UCharacterItemAsset::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId UCharacterItemAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
	/*
	UClass* ThisClass = GetClass();

	// If this is a native class use the raw name if it's a blueprint use the package name as it will be missing _C
	FName PrimaryAssetName = ThisClass->HasAnyClassFlags(CLASS_Native | CLASS_Intrinsic) ? GetFName() : ThisClass->GetOutermost()->GetFName();

	return FPrimaryAssetId(ItemType, ThisClass->GetOutermost()->GetFName());*/
}
