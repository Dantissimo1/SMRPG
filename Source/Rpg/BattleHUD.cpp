// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleHUD.h"
#include "BattleBrainComponent.h"

void UBattleHUD::SetUp(UBattleBrainComponent* inBrain)
{
	UE_LOG(LogTemp, Warning, TEXT("UBattleBrainComponent 1"));
	if (inBrain)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBattleBrainComponent 2"));
		activeBattleBrain = inBrain;
	}

}

void UBattleHUD::CallCalcTurns()
{
	CalcTurnsHUD();
}


void UBattleHUD::CalcTurnsHUD_Implementation()
{
}


