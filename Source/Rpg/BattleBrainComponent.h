// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine.h"

#include "BattleBrainComponent.generated.h"


class ABattleZoneBase;
class ABattlePawnBase;
class UBattleHUD;
class UDungeonHUD;
class ADungeonControllerBase;
class UTurnInfo;
class UAbilityBase;




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UBattleBrainComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBattleBrainComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool isLoaded = false;

	ADungeonControllerBase* PlayersCont;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turns")
	TArray<UTurnInfo*>TurnOrder;
	TArray<UTurnInfo*>WorkingTurnOrder;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turns")
	UTurnInfo* ActiveTurn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pawns")
	TArray<ABattlePawnBase*>AllPawnsInBattle;
	TArray<ABattlePawnBase*>playerBattlePawns;
	TArray<ABattlePawnBase*>enemyBattlePawns;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Main")
	ABattleZoneBase* MyBattleZone;

	void SetUp(ABattleZoneBase* InBattleZone);
	void ConstructHUD();
	void InitializeBattle(TArray<ABattlePawnBase*>allBattlePawns, TArray<ABattlePawnBase*>playerBattlePawns, TArray<ABattlePawnBase*>enemyBattlePawns);
	void CalcInitialTurnOrder();
	UFUNCTION(BlueprintCallable)
	void ReCalcChrsTurns(ABattlePawnBase* inPawn);
	void SetActiveTurn();
	void AddNewTurn(ABattlePawnBase* MyBattlePawn,FString ChrName,int Turn,float Speed);
	bool RunActiveTurn();
	bool RunPlayersTurn();
	bool RunEnemyTurn();
	void RemovePawnsTurns(ABattlePawnBase* inPawn);

	//////////target selection///////
	UAbilityBase* activeAbility = NULL;
	bool attackMenueSpawned = false;
	bool watingForPlayersTarget = true;
	ABattlePawnBase* confirmedSingleTarget = NULL;
	///add more for difrent attack types

	////attack
	bool AttackMelee(ABattlePawnBase* attackTarget);
	bool AttackMagic(ABattlePawnBase* attackTarget);
	bool AttackRanged(ABattlePawnBase* attackTarget);
	bool atStaginPoint1 = false;
	bool atStagingPoint2 = false;
	bool atAttackPosition = false;
	bool atopotunityLocation = false;
	bool backAtSpawn = false;
	bool awatingOpotunityDecision = true;
	bool variablesReset = false;
	bool faceingTargetLocation = false;
	bool damageStepDone = false;

	void EndBattle();
	void ClearTurnOrders();



	ABattlePawnBase* attaaaaTarget;
	bool testOperationCompleted = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Turns")
	bool testOp2 = false;
};
