// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamageLibary.h"


#include "AbilityBase.generated.h"

class UEffectSource;
class ABattlePawnBase;

/**
 * 
 */
UCLASS(Blueprintable)
class RPG_API UAbilityBase : public UObject
{
	GENERATED_BODY()
	

public:
	UAbilityBase();
	void AbilitysInstructions();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		FDamageTypesToCause DamageTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		TSubclassOf<UEffectSource> AbilitysEffect;



	void passOnEffects(ABattlePawnBase* inPawn, ABattlePawnBase* causeingPawn);
	void passOnEffects(TArray<ABattlePawnBase*>inPawns, ABattlePawnBase* causeingPawn);
	void passOnEffects(FVector* Location, ABattlePawnBase* causeingPawn);
};
