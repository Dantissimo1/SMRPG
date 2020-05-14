// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleBrainComponent.h"
#include "BattleZoneBase.h"

#include "BattleHUD.generated.h"

class UBattleBrainComponent;
class ABattleZoneBase;


/**
 * 
 */
UCLASS()
class RPG_API UBattleHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Brain")
		UBattleBrainComponent* activeBattleBrain;
		
	UFUNCTION()
	void SetUp(UBattleBrainComponent* inBrain);

	void CallCalcTurns();

	UFUNCTION(BlueprintNativeEvent, Category = "Turns")
	void CalcTurnsHUD();

};