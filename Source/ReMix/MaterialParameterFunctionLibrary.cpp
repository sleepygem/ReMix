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

TArray<FItemMaterialSettingsSerializable> UMaterialParameterFunctionLibrary::MakeMaterialSettingsSerializable(UPARAM(ref) TMap<FName, FItemMaterialSettings>& MaterialSettings)
{
	TArray<FItemMaterialSettingsSerializable> ConvertedMaterialSettings;

	for (const TPair<FName, FItemMaterialSettings>& CurrentMaterialSettings : MaterialSettings)
	{
		FItemMaterialSettingsSerializable NewSerializableSettings;

		NewSerializableSettings.Material = CurrentMaterialSettings.Value.Material->GetBaseMaterial();
		NewSerializableSettings.MaterialSlot = CurrentMaterialSettings.Key;
		TArray<FColourParameterSerializable> NewColourParameters;

		for (const TPair<FName, FLinearColor>& pair : CurrentMaterialSettings.Value.ColourParameters)
		{
			NewColourParameters.Add(FColourParameterSerializable(pair.Key, pair.Value));
			UE_LOG(LogTemp, Warning, TEXT("Added colour parameter of value %s"), *pair.Value.ToString());
		}
		NewSerializableSettings.ColourParameters = NewColourParameters;
		ConvertedMaterialSettings.Add(NewSerializableSettings);
	}
	
	return ConvertedMaterialSettings;
}


/*
* Converting material settings from file to a version used at runtime
*/
TMap<FName, FItemMaterialSettings> UMaterialParameterFunctionLibrary::MakeInstancedMaterialSettings(UObject* WorldContextObject, UPARAM(ref)TArray<FItemMaterialSettingsSerializable>& SerializedSettings)
{
	TMap<FName, FItemMaterialSettings> InstancedMaterialSettings;
	
	for (FItemMaterialSettingsSerializable CurrentSettings : SerializedSettings)
	{
		FItemMaterialSettings NewMaterialSettings;

		if (CurrentSettings.Material != nullptr)
		{
			NewMaterialSettings.Material = UKismetMaterialLibrary::CreateDynamicMaterialInstance(WorldContextObject, CurrentSettings.Material);
		}
		else
		{
			NewMaterialSettings.Material = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Serialized Material is nullptr, unable to create dynamic material instance."))
		}

		for (FColourParameterSerializable ColourParam : CurrentSettings.ColourParameters)
		{
			NewMaterialSettings.AddColourParameter(ColourParam.ParameterName, ColourParam.Color);
			NewMaterialSettings.Material->SetVectorParameterValue(ColourParam.ParameterName, ColourParam.Color);
		}

		InstancedMaterialSettings.Add(CurrentSettings.MaterialSlot, NewMaterialSettings);
	}
	
	return InstancedMaterialSettings;
}

bool UMaterialParameterFunctionLibrary::FindItemMaterialSettings(FName Name, UPARAM(ref)TMap<FName, FItemMaterialSettings>& MaterialSettings, FItemMaterialSettings& OutSettings)
{
	OutSettings = MaterialSettings.FindRef(Name);
	return true;
}
