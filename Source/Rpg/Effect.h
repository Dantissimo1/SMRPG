// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "Effect.generated.h"


class ABattlePawnBase;
class UEffectSource;
class UDamageLibary;



/**
 * 
 */
UCLASS()
class RPG_API UEffect : public UObject
{
	GENERATED_BODY()
	
public:

	UEffect();
	ABattlePawnBase* linkedPawn;

	UEffectSource* mySource;


	void InitialRun(UEffectSource* inSource, ABattlePawnBase* inLinkedPawn);

	bool RunEffect();

};
