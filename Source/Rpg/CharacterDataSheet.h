// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDataSheet.generated.h"


class AWeaponBase;
class UAbilityBase;

USTRUCT(BluePrintType)
struct RPG_API FCharacterDetails
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		TSubclassOf<class ABattlePawnBase>BattlePawnToUse;
	ABattlePawnBase* CharactersBattleBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		FString CharacterName = "Gav";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		int Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		int Experiance = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float Health = MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float HealthRegenRate = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float ManaMax = 12;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float Mana = ManaMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float ManaRegenRate = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float BaseSpeed = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
	float Speed = BaseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		float counterChance = 5;

};

USTRUCT(BluePrintType)
struct RPG_API FOfensiveStats
{
	GENERATED_USTRUCT_BODY()

public:

	//ofensive stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ofensive stats")
		float Strength = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ofensive stats")
		float RangeFinesse = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ofensive stats")
		float Acuracy = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ofensive stats")
		float ArcaneAptitude = 100;

};

USTRUCT(BluePrintType)
struct RPG_API FDDefensiveStats
{
	GENERATED_USTRUCT_BODY()

public:

	////defensive stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ofensive stats")
		float Evasion = 1;

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




USTRUCT(BluePrintType)
struct RPG_API FSavedEquipedItems
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		TSubclassOf<AWeaponBase> myWeapon;





};

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
		FCharacterDetails CharacterDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		FOfensiveStats OfensiveStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		FDDefensiveStats DefensiveStats;

	//////Equiptment

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		TSubclassOf<class AWeaponBase>WeaponToUse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Chr Info")
		FSavedEquipedItems itemsEquiped;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilitys")
		TArray<TSubclassOf<UAbilityBase>> abilityClasses;
	TArray<UAbilityBase*> abilities;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilitys")
		TArray<TSubclassOf<UAbilityBase>> magicAbilityClasses;
	TArray<UAbilityBase*> magicAbilities;




};
