// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleBrainComponent.h"
#include "BattleZoneBase.h"

#include "BattleHUD.generated.h"

class UBattleBrainComponent;
class ABattleZoneBase;
class ABattlePawn;
class ADungeonControllerBase;
class UAbilityBase;


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
	void SetUp(UBattleBrainComponent* inBrain, ADungeonControllerBase* playerController);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player controller")
	ADungeonControllerBase* playerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "activeAbility")
		UAbilityBase* activeAbility;

	void CallCalcTurns();

	UFUNCTION(BlueprintNativeEvent, Category = "Turns")
	void CalcTurnsHUD();

	UFUNCTION(BlueprintNativeEvent, Category = "Turns")
		void EndBattleWin();

	UFUNCTION(BlueprintNativeEvent, Category = "SetUpHUD")
		void SetUpHUD();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowAttackMenue();
	UFUNCTION(BlueprintImplementableEvent)
		void HideAttackMenue();


	bool hasCreatedOpotunityMenu = false;
	UFUNCTION(BlueprintNativeEvent, Category = "SetUpHUD")
		void CreateOpotunityMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "SetUpHUD")
		void RemoveOpotunityMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "SetUpHUD")
		void CreateCounterMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "SetUpHUD")
		void RemoveCounterMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "SetUpHUD")
		void CreateChargingMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "SetUpHUD")
		void RemoveChargingMenu();


	UFUNCTION(BlueprintImplementableEvent)
		void BackToAttackSelection();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
		bool selectingTargets;

	UFUNCTION(BlueprintCallable)
		void SelectTarget();



};
