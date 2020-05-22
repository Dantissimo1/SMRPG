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
		float ImpactDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float SlashDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float PunctureDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float FireDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float EarthDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float WaterDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float ColdDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float ElectricityDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float HolyDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float VoidDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float ArcaneDamage = 0;

};


UCLASS()
class RPG_API UDamageLibary : public UObject
{
	GENERATED_BODY()
	
};
