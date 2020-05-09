// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"


#include "WeaponBase.generated.h"

USTRUCT(BluePrintType)
struct RPG_API FDamageTypesToCause
{
	GENERATED_USTRUCT_BODY()

public:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float ImpactDamage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float SlashDamage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float PunctureDamage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float FireDamage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float EarthDamage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float WaterDamage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float ColdDamage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float ElectricityDamage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float HolyDamage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float VoidDamage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float ArcaneDamage = 10;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AWeaponBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		FDamageTypesToCause myDamage;
		
};
