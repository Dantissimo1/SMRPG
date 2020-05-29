// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamageLibary.h"


#include "AbilityBase.generated.h"

class UEffectSource;
class ABattlePawnBase;
class USphereComponent;
class AParticleHolder;


UENUM()
enum class EAttackType : uint8
{
	NONE,
	singleTarget,
	aoeMed,
	aoePartywide,
};
UENUM()
enum class EABuffType : uint8
{
	NONE,
	singleTarget,
	aoeMed,
	aoePartywide,
	selfBuff,
	selfAOEBuff,
	selfPartyBuff,
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

	TArray< ABattlePawnBase*> AbilitysInstructions(ABattlePawnBase* sourcePawn, ABattlePawnBase* inAtTarg, float inDamageModifier, FDamageTypesToCause inDamageToAdd);

	void DoDamage(ABattlePawnBase* inCause ,ABattlePawnBase* inAtTarg);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		FString Name = "Tits";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		EAttackType attackType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		EABuffType buffType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		TSubclassOf<AParticleHolder> dammgeEffect;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		bool targetsHostile = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		bool chargedAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		int chargeTime = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		bool isHealing = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		float healPercent = 36;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		float shieldPercent = 60;

	USphereComponent* DamageSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float DamageSphereSize = 350;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		FDamageTypesToCause DamageTypes;

	FDamageTypesToCause WorkOutDamage(float inModifier, FDamageTypesToCause inDamageToAdd);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		TSubclassOf<UEffectSource> AbilitysEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		EAttackStyle AttackStyle = EAttackStyle::Melee;

	void passOnEffects(TArray<ABattlePawnBase*>inPawns, ABattlePawnBase* causeingPawn);

};
