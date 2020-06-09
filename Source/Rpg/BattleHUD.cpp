// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleHUD.h"
#include "BattleBrainComponent.h"
#include "DungeonControllerBase.h"
#include "AbilityBase.h"



void UBattleHUD::SetUp(UBattleBrainComponent* inBrain, ADungeonControllerBase* inPlayerController)
{
	//////UE_LOG(LogTemp, Warning, TEXT("UBattleBrainComponent 1"));
	if (inBrain)
	{
		//////UE_LOG(LogTemp, Warning, TEXT("UBattleBrainComponent 2"));
		activeBattleBrain = inBrain;
		playerController = inPlayerController;
		SetUpHUD();
	}

}

void UBattleHUD::CallCalcTurns()
{
	//////UE_LOG(LogTemp, Warning, TEXT("CalcTurnsHUD 1"));
	CalcTurnsHUD();
	//////UE_LOG(LogTemp, Warning, TEXT("CalcTurnsHUD 2"));
}

void UBattleHUD::EndBattleWin_Implementation()
{
}

void UBattleHUD::SetUpHUD_Implementation()
{
}




void UBattleHUD::SelectTarget()
{
	//UE_LOG(LogTemp, Warning, TEXT("Select Target 1"));
	playerController->skillSelected = true;
	playerController->activeAbility = activeAbility;
	activeAbility = NULL;
	selectingTargets = true;
}




void UBattleHUD::CalcTurnsHUD_Implementation()
{
}

void UBattleHUD::CreateOpotunityMenu_Implementation()
{
}

void UBattleHUD::RemoveOpotunityMenu_Implementation()
{
}

void UBattleHUD::CreateCounterMenu_Implementation()
{
}

void UBattleHUD::RemoveCounterMenu_Implementation()
{
}

void UBattleHUD::CreateChargingMenu_Implementation()
{
}

void UBattleHUD::RemoveChargingMenu_Implementation()
{
}
