// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Effect.h"




#include "EffectSource.generated.h"





/**
 * 
 */
UCLASS()
class RPG_API UEffectSource : public UObject
{
	GENERATED_BODY()

public:

    UEffectSource();

    int TurnsRemaning = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    TSubclassOf<UEffect>effectToPass;

    TArray<UEffect*> activeEffects;

    void InitialRun();
    void EndEffect();
};
