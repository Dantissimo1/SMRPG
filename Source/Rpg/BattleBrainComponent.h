// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine.h"

#include "BattleBrainComponent.generated.h"


class ABattleZoneBase;
class ABattlePawnBase;



USTRUCT(BluePrintType)
struct RPG_API FBattlePawnTurnInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABattlePawnBase* MyBattlePawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChrName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Turn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;




};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UBattleBrainComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBattleBrainComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	TArray<FBattlePawnTurnInfo>TurnOrder;
	TArray<FBattlePawnTurnInfo>WorkingTurnOrder;
	FBattlePawnTurnInfo* ActiveTurn;
	TArray<ABattlePawnBase*>AllPawnsInBattle;
	
	ABattleZoneBase* MyBattleZone;

	void SetUp(ABattleZoneBase* InBattleZone);

	void InitializeBattle();
	void CalcInitialTurnOrder();
	void ReCalcChrsTurns(ABattlePawnBase* inPawn);
	void SetActiveTurn();
	void AddNewTurn(ABattlePawnBase* MyBattlePawn,FString ChrName,int Turn,float Speed);


	void EndBattle();
	void ClearTurnOrders();


};
