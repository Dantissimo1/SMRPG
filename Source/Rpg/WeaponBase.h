// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageLibary.h"

#include "WeaponBase.generated.h"


class AProjectileBase;

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
		FString name = "Poop Stick";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		bool isRanged = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		FDamageTypesToCause myDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		TSubclassOf<AProjectileBase> ProjectileToUse;

		
};
