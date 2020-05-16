// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleHUD.h"
#include "BattleBrainComponent.h"
#include "DungeonControllerBase.h"
#include "AbilityBase.h"



void UBattleHUD::SetUp(UBattleBrainComponent* inBrain, ADungeonControllerBase* inPlayerController)
{
	////UE_LOG(LogTemp, Warning, TEXT("UBattleBrainComponent 1"));
	if (inBrain)
	{
		////UE_LOG(LogTemp, Warning, TEXT("UBattleBrainComponent 2"));
		activeBattleBrain = inBrain;
		playerController = inPlayerController;
	}

}

void UBattleHUD::CallCalcTurns()
{
	////UE_LOG(LogTemp, Warning, TEXT("CalcTurnsHUD 1"));
	CalcTurnsHUD();
	////UE_LOG(LogTemp, Warning, TEXT("CalcTurnsHUD 2"));
}


void UBattleHUD::SelectSingleTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("Select Single Target 1"));
	playerController->isWaitingForSingleTargetSelection = true;
	playerController->lookingForHostile = true;
	selectingTargets = true;
	
}



void UBattleHUD::CalcTurnsHUD_Implementation()
{
}


