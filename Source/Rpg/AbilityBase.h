// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamageLibary.h"


#include "AbilityBase.generated.h"

class UEffectSource;
class ABattlePawnBase;
class USphereComponent;



UENUM()
enum class EAttackType : uint8
{
	singleTarget,
	aoeMed,
	aoePartywide,
	AttackselfBuff,
};

UENUM()
enum class EAttackStyle : uint8
{
	Melee,
	Rganged,
	Magic,
};


/**
 * 
 */
UCLASS(Blueprintable)
class RPG_API UAbilityBase : public UObject
{
	GENERATED_BODY()
	

public:
	UAbilityBase();

	TArray< ABattlePawnBase*> AbilitysInstructions(ABattlePawnBase* sourcePawn, ABattlePawnBase* inAtTarg);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		FString Name = "Tits";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		EAttackType attackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		bool targetsHostile = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		bool isHealing = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		float healPercent = 36;

	USphereComponent* DamageSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float DamageSphereSize = 350;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		FDamageTypesToCause DamageTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		TSubclassOf<UEffectSource> AbilitysEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		EAttackStyle AttackStyle = EAttackStyle::Melee;

	void passOnEffects(TArray<ABattlePawnBase*>inPawns, ABattlePawnBase* causeingPawn);

};
