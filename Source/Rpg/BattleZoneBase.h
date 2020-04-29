// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"





#include "BattleZoneBase.generated.h"


class UBoxComponent;
class UCameraComponent;
class ADungeonControllerBase;
class UBattleSpawnPoint;


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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* PlayerSpawn1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* PlayerSpawn2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* PlayerSpawn3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* PlayerSpawn4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* PlayerSpawn5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* PlayerSpawn6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* PlayerSpawn7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* PlayerSpawn8;



	//enemyside

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* EnemySpawn1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* EnemySpawn2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* EnemySpawn3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* EnemySpawn4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* EnemySpawn5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* EnemySpawn6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* EnemySpawn7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSpawn")
		class UBattleSpawnPoint* EnemySpawn8;



	void InitializeBattle(ADungeonControllerBase* InPlayerCont);







	void EndBattle();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
