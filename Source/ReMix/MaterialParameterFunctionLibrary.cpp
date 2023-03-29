// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialParameterFunctionLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"

void UMaterialParameterFunctionLibrary::AddColourParameter(UPARAM(ref) FItemMaterialSettings& MaterialSettings, FName ParameterName, FLinearColor NewColourValue)
{
	MaterialSettings.AddColourParameter(ParameterName, NewColourValue);
}

bool UMaterialParameterFunctionLibrary::GetAssociatedParameters(UObject* WorldContextObject, UCharacterItemAsset* ItemAsset, FName MaterialSlot, UMaterialInterface* Material, bool bRandomizeValues, 
	FItemMaterialSettings& MaterialSettings)
{
	FItemMaterialSettings NewMaterialSettings = FItemMaterialSettings();
	bool bHasAnyParameters = false;

	if (IsValid(WorldContextObject))
	{
		TArray<FColourParameter>& ColourParameters = ItemAsset->ColourParameters;
		
		for (FColourParameter ColourParam : ColourParameters)
		{
			if (ColourParam.MaterialSlot == MaterialSlot)
			{
				

				if (!bHasAnyParameters)
				{
					UMaterialInstanceDynamic* DynamicMat = UKismetMaterialLibrary::CreateDynamicMaterialInstance(WorldContextObject, Material);
					NewMaterialSettings.Material = DynamicMat;
					bHasAnyParameters = true;
				}

				const FLinearColor NewColour = bRandomizeValues ? ColourParam.GetRandomColour() : FLinearColor(0.f, 0.f, 0.f, 0.f);

				if (bRandomizeValues)
				{
					NewMaterialSettings.Material->SetVectorParameterValue(ColourParam.ParameterName, NewColour);
				}

				AddColourParameter(NewMaterialSettings, ColourParam.ParameterName, NewColour);
			}
		}
	}

	MaterialSettings = NewMaterialSettings;

	return bHasAnyParameters;
}
