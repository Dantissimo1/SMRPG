// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"





#include "EffectSource.generated.h"


class UEffect;
class ABattlePawnBase;
class UDamageLibary;
class UAbilityBase;

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

/**
 * 
 */
UCLASS(Blueprintable)
class RPG_API UEffectSource : public UObject
{
	GENERATED_BODY()

public:

    UEffectSource();

    UAbilityBase* sourceAbility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
        EEffectType effectType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
        int lifeInTurns = 3;

    int TurnsRemaning = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
        EEffectStyle EffectProfile;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
        EEffectType EfectType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
        bool bluprintOveride = false;

    UFUNCTION(BlueprintImplementableEvent)
        void ActivationOverride();

    TArray<UEffect*> activeEffects;

    ABattlePawnBase* myOwner;



    void InitialRun(ABattlePawnBase* inOwner, UAbilityBase* inSourceAbility);
    void TriggeredRun();
    void decrementTurnCounter();
    void activateEffect();
    bool runEffect(UEffect* affectChild);
    void EndEffect();
};
