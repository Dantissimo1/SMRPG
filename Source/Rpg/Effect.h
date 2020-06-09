// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "UObject/NoExportTypes.h"
//#include "AbilityBase.h"

#include "Effect.generated.h"


class ABattlePawnBase;
class AEffectSource;
class UDamageLibary;
class UAbilityBase;
class AParticleHolder;


UENUM()
enum class EEffectType : uint8
{
    damage,
    buff,
    healing,
    shield,
};

UENUM()
enum class EEffectStyle : uint8
{
    Bleading,
    Poision,
    Burning,
    Petrified,
    Blind,
    Silence,
    Wet,
    Cold,
    Static,
    Holy,
    Void,
    Arcane,
    Healing,
    shield,
    Physical,

};

UENUM()
enum class EStatToBuff : uint8
{
	None,
	Strength,
	ArcaneStrength,
	ManaRegen,
	HealthRegen,
	RangedStrength,
	shield,
	Impact,
	SlashDamage,
	PunctureDamage,
	FireDamage,
	EarthDamage,
	WaterDamage,
	ColdDamage,
	ElectricityDamage ,
	HolyDamage ,
	VoidDamage,
	ArcaneDamage,
};


/**
 * 
 */
UCLASS()
class RPG_API AEffect : public AActor
{
	GENERATED_BODY()
	
public:

	AEffect();
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

	ABattlePawnBase* linkedPawn;

	AEffectSource* mySource;
	UAbilityBase* sourceAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		EEffectStyle effectProfile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		EEffectType effectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		bool bluprintOveride = false;


	////////buffs-----------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffs")
		bool buffActivated = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffs")
		EStatToBuff statToBuff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buffs")
		float statMultiplier = 1;
	float amountBuffed = 0;

	void RunBuffs();

	void BuffStrength();
	void BuffArcaneStrength();
	void BuffManaRegen();
	void BuffHealthRegen();
	void BuffRangedStrength();
	void BuffShield();
	void BuffImpact();
	void BuffSlashDamage();
	void BuffPunctureDamage();
	void BuffFireDamage();
	void BuffEarthDamage();
	void BuffWaterDamage();
	void BuffColdDamage();
	void BuffElectricityDamage();
	void BuffHolyDamage();
	void BuffVoidDamage();
	void BuffArcaneDamage();


	void DestructBuffs();

	void DeBuffStrength();
	void DeBuffArcaneStrength();
	void DeBuffManaRegen();
	void DeBuffHealthRegen();
	void DeBuffRangedStrength();
	void DeBuffShield();
	void DeBuffImpact();
	void DeBuffSlashDamage();
	void DeBuffPunctureDamage();
	void DeBuffFireDamage();
	void DeBuffEarthDamage();
	void DeBuffWaterDamage();
	void DeBuffColdDamage();
	void DeBuffElectricityDamage();
	void DeBuffHolyDamage();
	void DeBuffVoidDamage();
	void DeBuffArcaneDamage();



	

	//---------------Particles-------------------------------------------
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
       TSubclassOf<AParticleHolder> ParticleEffect;
    AParticleHolder* spawnedParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
		bool SpawnParticleEachRun = true;


	UFUNCTION(BlueprintImplementableEvent)
		void ActivationOverride();

	void SpawnParticle();



	void InitialRun(AEffectSource* inSource, ABattlePawnBase* inLinkedPawn, UAbilityBase* inSourceAbility);

	bool RunEffect();

};
