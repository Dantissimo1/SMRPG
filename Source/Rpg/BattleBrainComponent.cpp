// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBrainComponent.h"
#include "BattleZoneBase.h"
#include "BattlePawnBase.h"


// Sets default values for this component's properties
UBattleBrainComponent::UBattleBrainComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBattleBrainComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBattleBrainComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBattleBrainComponent::SetUp(ABattleZoneBase* InBattleZone)
{
	MyBattleZone = InBattleZone;
}

void UBattleBrainComponent::InitializeBattle()
{
	for (int i = 0; i < MyBattleZone->PlayerBattlePawns.Num();i++)
	{
		AllPawnsInBattle.Add(MyBattleZone->PlayerBattlePawns[i]);
	}
	for (int i = 0; i < MyBattleZone->EnemyBattlePawns.Num();i++)
	{
		AllPawnsInBattle.Add(MyBattleZone->EnemyBattlePawns[i]);
	}

	///set initial turn order
	CalcInitialTurnOrder();
	SetActiveTurn();
}

void UBattleBrainComponent::CalcInitialTurnOrder()
{
	//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 1 %d"), AllPawnsInBattle.Num());
	for (int t = 1; t < 6;t++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 2"));
		for (int i = 0; i < AllPawnsInBattle.Num();i++)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 3"));
			FBattlePawnTurnInfo PawnTurnInfo;
			PawnTurnInfo.MyBattlePawn = AllPawnsInBattle[i];
			PawnTurnInfo.Speed = AllPawnsInBattle[i]->Speed * t;
			PawnTurnInfo.Turn = t;
			TurnOrder.Add(PawnTurnInfo);
		}
	}
	for (int i = 0; i < TurnOrder.Num();i++)
	{
		bool bElementAdded = 0;
		UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 4"));
		if (i == 0)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 5"));
			//UE_LOG(LogTemp, Warning, TEXT("Character name,%s"), *TurnOrder[0].MyBattlePawn->CharacterName);
			WorkingTurnOrder.Add(TurnOrder[0]);
			//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 6"));
		}
		else
		{
			int iNewPosition;
			
			//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 7"));
			if (WorkingTurnOrder.Num() == 1)
			{

			}

			for (int p = WorkingTurnOrder.Num()-1;p >= 0;p--)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 8"));
				if (TurnOrder[i].Speed < WorkingTurnOrder[p].Speed)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 9"));
					iNewPosition = p;
					WorkingTurnOrder.Insert(TurnOrder[i],p);
					//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 10"));
				}
				else if(bElementAdded == 0)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 11"));
					WorkingTurnOrder.Add(TurnOrder[i]);
					bElementAdded = 1;
					//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 12"));
				}
			}
		}
	}

	for (int h = 0; h < WorkingTurnOrder.Num();h++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character name,%s"), *WorkingTurnOrder[h].MyBattlePawn->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Working turn order pawn speed = %f"),WorkingTurnOrder[h].Speed);

	}
	TurnOrder = WorkingTurnOrder;
	ReCalcChrsTurns(TurnOrder[2].MyBattlePawn);

}

void UBattleBrainComponent::ReCalcChrsTurns(ABattlePawnBase* inPawn)
{
	TArray< FBattlePawnTurnInfo*> CurrentTurns;
	TArray<int>TurnNos;
	UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 1"));
	for (int i = 0; i < TurnOrder.Num();i++)
	{	
		UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 2"))
		if(TurnOrder[i].MyBattlePawn ==inPawn)
		{
			UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 3"))
			CurrentTurns.Add(&TurnOrder[i]);
		}
	}
	for(int j = 0; j < CurrentTurns.Num();j++)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 4"))
		//only update speed if it not the active turn
		if (CurrentTurns[j] != ActiveTurn) 
		{
			UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 5"))
			TurnNos.Add(CurrentTurns[j]->Turn);
			UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 6"))
			CurrentTurns[j]->Speed = CurrentTurns[j]->MyBattlePawn->Speed * CurrentTurns[j]->Turn;	
		}
	}
	if (CurrentTurns.Num() < 5)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 7"))
		int HighestTurnNo = 0;
		for (int u = 0; u < TurnNos.Num();u++)
		{
			UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 8"))
			if (TurnNos[u] > HighestTurnNo)
			{
				UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 9"))
				HighestTurnNo = TurnNos[u];
			}
		}
		FBattlePawnTurnInfo NewTurn;
		UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 10"))
		AddNewTurn(CurrentTurns[0]->MyBattlePawn, CurrentTurns[0]->ChrName, HighestTurnNo+1, CurrentTurns[0]->MyBattlePawn->Speed);
	}
}



void UBattleBrainComponent::SetActiveTurn()
{
	if (TurnOrder.Num() > 0)
	{
		ActiveTurn = &TurnOrder[0];
	}
}

void UBattleBrainComponent::AddNewTurn(ABattlePawnBase* MyBattlePawn, FString ChrName, int Turn, float Speed)
{
	FBattlePawnTurnInfo TurnToAdd;
	TurnToAdd.MyBattlePawn = MyBattlePawn;
	TurnToAdd.ChrName = ChrName;
	TurnToAdd.Turn = Turn;
	TurnToAdd.Speed = Speed * Turn;

	for (int i = 0; i <TurnOrder.Num();i++)	
	{ 
		UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 11"))
		if (TurnToAdd.Speed < TurnOrder[i].Speed)
		{
			UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 12"))
			TurnOrder.Insert(TurnToAdd, i);
		}
	}
}

void UBattleBrainComponent::EndBattle()
{
	ClearTurnOrders();
}

void UBattleBrainComponent::ClearTurnOrders()
{
	TurnOrder.Empty();
	TurnOrder.SetNum(0);
	WorkingTurnOrder.Empty();
	WorkingTurnOrder.SetNum(0);
	AllPawnsInBattle.Empty();
	UE_LOG(LogTemp, Warning, TEXT("Turns left,%d"), AllPawnsInBattle.Num());
	
	ActiveTurn = NULL;
}

