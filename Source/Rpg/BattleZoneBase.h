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

	/////////////Cameras
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* TestCam1;


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




	void InitializeBattle(ADungeonControllerBase* InPlayerCont);

	void SpawnPlayersParty();





	void EndBattle();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
