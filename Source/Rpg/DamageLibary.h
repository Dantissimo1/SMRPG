// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamageLibary.generated.h"

/**
 * 
 */

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


UCLASS()
class RPG_API UDamageLibary : public UObject
{
	GENERATED_BODY()
	
};
