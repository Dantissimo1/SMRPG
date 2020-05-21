// Fill out your copyright notice in the Description page of Project Settings.


#include "CounterAttackWidget.h"
#include "BattleBrainComponent.h"
#include "DungeonControllerBase.h"




void UCounterAttackWidget::SetUp(UBattleBrainComponent* inBrain, ADungeonControllerBase* inPlayerController)
{
	Brain = inBrain;
	playerController = inPlayerController;

}
