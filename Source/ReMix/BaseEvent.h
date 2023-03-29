// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseEvent.generated.h"

/**
 * 
 */
UCLASS(abstract, Blueprintable)
class REMIX_API UBaseEvent : public UObject
{
	GENERATED_BODY()

public:


#if WITH_ENGINE
	virtual class UWorld* GetWorld() const override;

#endif
};
