// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDataSheet.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API ACharacterDataSheet : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ACharacterDataSheet();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		


	////////////character detials / stats///.//////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		TSubclassOf<class ABattlePawnBase>BattlePawnToUse;
		ABattlePawnBase* CharactersBattleBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		FString CharacterName = "Gav111";
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
















};
