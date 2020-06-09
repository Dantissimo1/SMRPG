// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/ActorComponent.h"




#include "EffectSource.generated.h"


class AEffect;
class ABattlePawnBase;
class UDamageLibary;
class UAbilityBase;


/**
 * 
 */
UCLASS(Blueprintable)
class RPG_API AEffectSource : public AActor
{
	GENERATED_BODY()



public:
    AEffectSource();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:

    

    UAbilityBase* sourceAbility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
         TSubclassOf<AEffect> EfectToUse;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
        int lifeInTurns = 3;

    int TurnsRemaning = 3;

    bool CheckIfEffectsRemain();

    TArray<AEffect*> activeEffects;

    ABattlePawnBase* myOwner;

    bool isDead = false;

    void InitialRun(ABattlePawnBase* inOwner, UAbilityBase* inSourceAbility);
    void TriggeredRun();
    void decrementTurnCounter();
    void activateEffect();
    void EndEffect();
};
