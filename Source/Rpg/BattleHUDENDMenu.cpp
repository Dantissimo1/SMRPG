// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleHUDENDMenu.h"
#include "BattleBrainComponent.h"
#include "BattleZoneBase.h"


void UBattleHUDENDMenu::SetUp(UBattleBrainComponent* inBrain, ADungeonControllerBase* inPlayerController)
{
	if (inBrain)
	{
		//////UE_LOG(LogTemp, Warning, TEXT("UBattleBrainComponent 2"));
		activeBattleBrain = inBrain;
		playerController = inPlayerController;
		//SetUpHUD();
	}
}

void UBattleHUDENDMenu::CloseBattle()
{
	activeBattleBrain->MyBattleZone->EndBattle();
}
