// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"





#include "BattleZoneBase.generated.h"


class UBoxComponent;
class UCameraComponent;
class ADungeonControllerBase;
class UBattleSpawnPoint;
class ABattlePawnBase;
class AEnemyPartyformationComponent;
class AEnemyPartyFormationList;
class UBattleBrainComponent;


UCLASS()
class RPG_API ABattleZoneBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleZoneBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoxComp")
	class UBoxComponent* BoxComp ;

	ADungeonControllerBase* PlayerCont;


	/////////////Battle Brain
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		UBattleBrainComponent* BattleBrain;


	/////////////Cameras
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* TestCam1;


	//////enemy party
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyParty")
		TSubclassOf<class AEnemyPartyFormationList>EnemyPartyFormationList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyParty")
	class AEnemyPartyFormationCompnent* EnemyPartyFormation;

	FTimerHandle TestTimer;

	//////////spawn points////////////
	//playerside
	TArray<UBattleSpawnPoint*> PlayersFrontLineSpawnPoints;
	TArray<UBattleSpawnPoint*> PlayersBackLineSpawnPoints;


	TArray<ABattlePawnBase*> PlayerFrontlineBattlePawns;
	TArray<ABattlePawnBase*> PlayerBacklineBattlePawns;
	TArray<ABattlePawnBase*> PlayerBattlePawns;


	//enemyside
	TArray<UBattleSpawnPoint*> EnemyFrontLineSpawnPoints;
	TArray<UBattleSpawnPoint*> EnemyBackLineSpawnPoints;


	TArray<ABattlePawnBase*> EnemyFrontlineBattlePawns;
	TArray<ABattlePawnBase*> EnemyBacklineBattlePawns;
	TArray<ABattlePawnBase*> EnemyBattlePawns;



	void InitializeBattle(ADungeonControllerBase* InPlayerCont);

	void SpawnPlayersParty();
	void SpanEnemyParty();




	void EndBattle();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
