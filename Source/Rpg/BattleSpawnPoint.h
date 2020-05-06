// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BattleSpawnPoint.generated.h"

class UAttackPosition;
class UOpotunityAttackPosition;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UBattleSpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBattleSpawnPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points")
		float attackPointofset = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points")
		UAttackPosition* AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points")
		float opotunityPointOfset = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points")
		UOpotunityAttackPosition* OpotunityPoint;


};
