// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BattlePawnBase.generated.h"

class USkeletalMeshComponent;
class ABattleZoneBase;
class AIController;



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




	ABattleZoneBase* MyBattleZone;


	bool bIsBackLine = false;
	bool bHasReaction = true;



	//////////////////////stats/////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		FString CharacterName = "Gav";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		int Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		int Experiance = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float Health = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float ManaMax = 12;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float ManaRegenRate = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float HealthRegenRate = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float BaseSpeed = 1;
		float Speed = 1;
	

	/////ofensive stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float Strength = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float Evasion = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float ArcaneAptitude = 10;

	////defensive stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float ImpactResistance = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float SlashResistance = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float PunctureResistance = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float FireResistance = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float EarthResistance = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float WaterResistance = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float ColdResistance = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float ElectricityResistance = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float HolyResistance = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float VoidResistance = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float ArcaneResistance = 10;




	///movement

	bool MoveToLocation(FVector inLocation,float deltaTime);


};
