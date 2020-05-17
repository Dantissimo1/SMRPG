// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "CharacterDataSheet.h"
#include "DamageLibary.h"
#include "Test2.h"

#include "BattlePawnBase.generated.h"

class USkeletalMeshComponent;
class ABattleZoneBase;
class AIController;
class UAttackPosition;
class UOpotunityAttackPosition;
class UBattleSpawnPoint;
class UEffectSource;
class UEffect;
class UCameraComponent;



UENUM()
enum class ECharacterType : uint8
{
	Melee,
	Ranged,
	Magic,
	Support,
	Healing,

};



UCLASS()
class RPG_API ABattlePawnBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABattlePawnBase();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Properties")
		float heightOffset = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cammera")
		UCameraComponent* Camera;

	void SetUpPlayerPawn(ACharacterDataSheet* inDataSheet, UBattleSpawnPoint* inPawnsBaseActor, ABattleZoneBase* inBattleZone,bool inbackline,bool inOwnedByPlayer);
	void SetUpNPCPawn();

	ABattleZoneBase* MyBattleZone;

	ACharacterDataSheet* myDataSheet;

	UBattleSpawnPoint* PawnsBaseActor;
	bool bIsBackLine = false;
	bool bHasReaction = true;
	bool isOwnedByPlayer = false;
	int positionOnGrid;



	///states
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="States")
		bool isAttackingMelee = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
		bool isAttackingMagic = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
		bool isAttackingRanged = false;
	bool projectileHit = false;
	bool attackActionCompleeted = false;

	UFUNCTION(BlueprintCallable)
		void EndAttack();


	//////////////////////stats/////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
	FCharacterDetails mainCharInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		FOfensiveStats OfensiveStats;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		FDDefensiveStats DefensiveStats;


	//////////////////portraight///////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portrait")
	UTexture* PortraitImage;
	


	/////////abilitys
	void InitializePlayersAbilitys();

	UAbilityBase* activeAbility = NULL;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCAbilitys")
		TArray<TSubclassOf<UAbilityBase>> abilityClasses;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilitys")
	TArray<UAbilityBase*> abilitys;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCAbilitys")
		TArray<TSubclassOf<UAbilityBase>> magicAbilityClasses;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilitys")
	TArray<UAbilityBase*> magicAbilitys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCAbilitys")
		TSubclassOf<UTest2> TestClass;
	
	


	//////// Epquiptment

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equiped Items")
	FEquipedItems MyEquipedItems;
	
	void InitializeEquipedItems();

	///movement
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		bool isMoving;

	bool MoveToLocation(FVector inLocation);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float movementSpeed = 600;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float rotationSpeed = 650;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float zHeightOffset = 90;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float moveDistanceTolerance = 30;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float rotationTolerance =.1;

	void MoveForwards(FVector inLocation);
	bool RotateToTarget(FVector inLocation);


	////Freindly targeting
	ABattlePawnBase* lastFreindlyTarget = NULL;


	/////atacking

	UAttackPosition* attackPosition;
	UOpotunityAttackPosition* opotunityLocation;
	bool AttackTargetMelee(ABattlePawnBase* inTarget);
	bool AttackTargetMagic(ABattlePawnBase* inTarget);
	ABattlePawnBase* lastAttackTarget = NULL;

	///////   damage


	bool isDown = false;
	void CauseDamageToBattlePawn(ABattlePawnBase* inPawn,bool isMagic);
	//void CauseRangedDamageToBattlePawn(ABattlePawnBase* inPawn);
	//void CauseMagicDamageToBattlePawn(ABattlePawnBase* inPawn);
	//void TakeDamage(FBattlePawnTurnInfo* inDamage);

	void TakeBattleDamage(FDamageTypesToCause* inDamage);

	TArray<UEffectSource*>activeEffectSources;
	TArray<UEffect*>activeEffects;
	
};




