// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TurnInfo.generated.h"


class ABattlePawnBase;

/**
 * 
 */
UCLASS()
class RPG_API UTurnInfo : public UObject
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABattlePawnBase* MyBattlePawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChrName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Turn = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed =0;

};
