// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CounterAttackWidget.generated.h"



class UBattleBrainComponent;
class ADungeonControllerBase;



/**
 * 
 */
UCLASS()
class RPG_API UCounterAttackWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Brain")
		UBattleBrainComponent* Brain;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player controller")
	ADungeonControllerBase* playerController;


		UFUNCTION()
		void SetUp(UBattleBrainComponent* inBrain, ADungeonControllerBase* inPlayerController);


};
