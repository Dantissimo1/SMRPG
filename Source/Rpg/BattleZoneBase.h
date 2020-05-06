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
class UOpotunityAttackPosition;
class UAttackPosition;


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


	class AEnemyPartyFormationCompnent* enemyPartyFormation;

	FTimerHandle TestTimer;

	//////////spawn points////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoints")
		UBattleSpawnPoint* spawnPoint1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoints")
		UBattleSpawnPoint* spawnPoint2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoints")
		UBattleSpawnPoint* spawnPoint3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoints")
		UBattleSpawnPoint* spawnPoint4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoints")
		UBattleSpawnPoint* spawnPoint5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoints")
		UBattleSpawnPoint* spawnPoint6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoints")
		UBattleSpawnPoint* spawnPoint7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoints")
		UBattleSpawnPoint* spawnPoint8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPointsOposite")
		UBattleSpawnPoint* EnemySpawnPoint1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPointsOposite")
		UBattleSpawnPoint* EnemySpawnPoint2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPointsOposite")
		UBattleSpawnPoint* EnemySpawnPoint3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPointsOposite")
		UBattleSpawnPoint* EnemySpawnPoint4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPointsOposite")
		UBattleSpawnPoint* EnemySpawnPoint5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPointsOposite")
		UBattleSpawnPoint* EnemySpawnPoint6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPointsOposite")
		UBattleSpawnPoint* EnemySpawnPoint7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPointsOposite")
		UBattleSpawnPoint* EnemySpawnPoint8;


	//playerside
	TArray<UBattleSpawnPoint*> PlayerBattleSpawns;

	//enemyside
	TArray<UBattleSpawnPoint*> EnemyBattleSpawns;

	TArray<ABattlePawnBase*> allBattlePawns;
	TArray<ABattlePawnBase*> enemyBattlePawns;
	TArray<ABattlePawnBase*> playerBattlePawns;


	/////opotunity points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Locations")
	TArray<UOpotunityAttackPosition*> OpotunityPoints;


	///////Attack points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Locations")
	TArray<UAttackPosition*> AttackPoints;





	void InitializeBattle(ADungeonControllerBase* InPlayerCont);

	void SpawnPlayersParty();
	void SpanEnemyParty();
	void DeleteBattlePawns();


	void EndBattle();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
