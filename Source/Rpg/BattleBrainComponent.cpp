// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBrainComponent.h"
#include "BattleZoneBase.h"
#include "BattlePawnBase.h"
#include "BattleSpawnPoint.h"
#include "AttackPosition.h"
#include "OpotunityAttackPosition.h"
#include "BattleHUD.h"
#include "BattleZoneBase.h"
#include "DungeonControllerBase.h"
#include "TurnInfo.h"
#include "AbilityBase.h"



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

	if (isLoaded == true)
	{
		if (RunActiveTurn())
		{ 
			if (MyBattleZone-> PlayerCont)
			{
				//UE_LOG(LogTemp, Warning, TEXT("inplayer cont"));
			}
			//UE_LOG(LogTemp, Warning, TEXT("crash check 1 %d"),);
			//start next turn
			ReCalcChrsTurns(ActiveTurn->MyBattlePawn);
			//UE_LOG(LogTemp, Warning, TEXT("crash check 2 %d"), );
	


			if (ActiveTurn->MyBattlePawn->isOwnedByPlayer == true)
			{
				confirmedSingleTarget = NULL;
				PlayersCont->lookingForHostile = false;
				PlayersCont->singleTarget = NULL;
				PlayersCont->lookingForHostile = false;
				PlayersCont->isWaitingForSingleTargetSelection = false;
				watingForPlayersTarget = true;
			}


			ActiveTurn = TurnOrder[0];
			TurnOrder.RemoveAt(0);
			PlayersCont->BattleHUD->CallCalcTurns();
		}
	}

	// ...
}

void UBattleBrainComponent::SetUp(ABattleZoneBase* InBattleZone)
{
	MyBattleZone = InBattleZone;
}

void UBattleBrainComponent::ConstructHUD()
{
	//GetWorld()->GetFirstPlayerController()->BattleHUD->CalcTurnsHUD();
	MyBattleZone->PlayerCont->BattleHUD->CalcTurnsHUD();
}



void UBattleBrainComponent::InitializeBattle(TArray<ABattlePawnBase*>inPawns, TArray<ABattlePawnBase*>inPlayerBattlePawns, TArray<ABattlePawnBase*>inEnemyBattlePawns)
{
	if (inPawns.Num() > 0)
	{
		AllPawnsInBattle = inPawns;
	}
	if (inPlayerBattlePawns.Num() > 0)
	{
		playerBattlePawns = inPlayerBattlePawns;
	}
	if (inEnemyBattlePawns.Num() > 0)
	{
		enemyBattlePawns = inEnemyBattlePawns;
	}
	///set initial turn order
	CalcInitialTurnOrder();
	SetActiveTurn();
	

}

void UBattleBrainComponent::CalcInitialTurnOrder()
{

	WorkingTurnOrder.Empty();
	//////////////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 1 %d"), AllPawnsInBattle.Num());
	for (int t = 1; t < 6;t++)
	{
		//////////////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 2"));
		for (int i = 0; i < AllPawnsInBattle.Num();i++)
		{
			//////////////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 3"));
			UTurnInfo* PawnTurnInfo = NewObject<UTurnInfo>(UTurnInfo::StaticClass());
			PawnTurnInfo->MyBattlePawn = AllPawnsInBattle[i];
			PawnTurnInfo->Speed = AllPawnsInBattle[i]->mainCharInfo.BaseSpeed * t;
			PawnTurnInfo->Turn = t;
			PawnTurnInfo->ChrName = AllPawnsInBattle[i]->mainCharInfo.CharacterName;
			TurnOrder.Add(PawnTurnInfo);
		}
	}
	for (int i = 0; i < TurnOrder.Num();i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("chr 111 %s"),*TurnOrder[i]->ChrName);
		//UE_LOG(LogTemp, Warning, TEXT("chr111 %f"), TurnOrder[i]->Speed);
		//UE_LOG(LogTemp, Warning, TEXT("chr 111111 %d"), TurnOrder[i]->Turn);
		bool hasBeenPlaced = false;
		int place = 0;
		if (WorkingTurnOrder.Num() > 0)
		{
			for (int q = 0; q < WorkingTurnOrder.Num();q++)
			{
				//UE_LOG(LogTemp, Warning, TEXT("chr wwwww %s"), *WorkingTurnOrder[q]->ChrName);
				//UE_LOG(LogTemp, Warning, TEXT("chr wwwwww %f"), WorkingTurnOrder[q]->Speed);
				//UE_LOG(LogTemp, Warning, TEXT("chr wwwwwwww %d"), WorkingTurnOrder[q]->Turn);
				if (TurnOrder[i] != WorkingTurnOrder[q])
				{
					if (TurnOrder[i]->Speed < WorkingTurnOrder[q]->Speed)
					{

						place = q;
						hasBeenPlaced = true;
						break;
					}
					if (TurnOrder[i]->Speed == WorkingTurnOrder[q]->Speed)
					{
						place = q + 1;
						hasBeenPlaced = true;
					}
				}
			}
			if (hasBeenPlaced == false)
			{
				WorkingTurnOrder.Add(TurnOrder[i]);
			}else
			{
				//UE_LOG(LogTemp, Warning, TEXT("place place 1111 %d"), place);
				WorkingTurnOrder.Insert(TurnOrder[i], place);
			}
		}
		else
		{
			WorkingTurnOrder.Add(TurnOrder[i]);
		}
	}

	TurnOrder.Empty();
	for (int y = 0; y < WorkingTurnOrder.Num();y++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("chr fff %s"), *WorkingTurnOrder[y]->ChrName);
		//UE_LOG(LogTemp, Warning, TEXT("chrffff %f"), WorkingTurnOrder[y]->Speed);
		//UE_LOG(LogTemp, Warning, TEXT("chrffffff %d"), WorkingTurnOrder[y]->Turn);
		TurnOrder.Insert(WorkingTurnOrder[y],y);
	}
}

void UBattleBrainComponent::ReCalcChrsTurns(ABattlePawnBase* inPawn)
{
	TArray< UTurnInfo*> CurrentTurns;
	TArray<int>TurnNos;
	//UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 1"));
	for (int i = 0; i < TurnOrder.Num();i++)
	{	
		//UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 2"))
		if(TurnOrder[i]->MyBattlePawn ==inPawn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 3"))
			CurrentTurns.Add(TurnOrder[i]);
		}
	}
	for(int j = 0; j < CurrentTurns.Num();j++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 4"))
		//only update speed if it not the active turn
		if (CurrentTurns[j] != ActiveTurn) 
		{
			//UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 5"))
			TurnNos.Add(CurrentTurns[j]->Turn);
			//UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 6"))
			CurrentTurns[j]->Speed = CurrentTurns[j]->MyBattlePawn->mainCharInfo.Speed * CurrentTurns[j]->Turn;


			int iNewPosition;
			bool bElementAdded = 0;
			//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 7"));
			for (int p = 0;p < TurnOrder.Num();p++)
			{
				if (CurrentTurns[j] != TurnOrder[p])
				{
					//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 8"));
					if (CurrentTurns[j]->Speed < TurnOrder[p]->Speed)
					{
						//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 9"));
						iNewPosition = p;
						break;
						//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 10"));
					}
				}
				else if (CurrentTurns[j]->Speed == TurnOrder[p]->Speed)
				{
					iNewPosition = p;
					break;
				}



			}
			//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 13"));
			UTurnInfo* turnToinsert = CurrentTurns[j];
			TurnOrder.RemoveSingle(CurrentTurns[j]);
			//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 14"));
			TurnOrder.Insert(turnToinsert, iNewPosition);
			//UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 15"));
		}
	}
	while (TurnNos.Num() < 4)
	{
		//////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 7 %d"), CurrentTurns.Num())
		int HighestTurnNo = 0;
		for (int u = 0; u < TurnNos.Num();u++)
		{
			//////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 8"))
			if (TurnNos[u] > HighestTurnNo)
			{
				//////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 9 %d"), HighestTurnNo)
				HighestTurnNo = TurnNos[u];
			}
		}
		//////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 10"))
		AddNewTurn(CurrentTurns[0]->MyBattlePawn, CurrentTurns[0]->ChrName, HighestTurnNo+1, inPawn->mainCharInfo.Speed);
		TurnNos.Add(HighestTurnNo +1 );

	}
}



void UBattleBrainComponent::SetActiveTurn()
{
	if (TurnOrder.Num() > 0)
	{

		ActiveTurn = TurnOrder[0];
		TurnOrder.RemoveAt(0);
	}
}

void UBattleBrainComponent::AddNewTurn(ABattlePawnBase* MyBattlePawn, FString ChrName, int Turn, float Speed)
{
	UTurnInfo* TurnToAdd = NewObject<UTurnInfo>(UTurnInfo::StaticClass());
	TurnToAdd->MyBattlePawn = MyBattlePawn;
	TurnToAdd->ChrName = ChrName;
	TurnToAdd->Turn = Turn;
	TurnToAdd->Speed = Speed * Turn;

	int a = 0;
	for (int i = 0; i <TurnOrder.Num();i++)	
	{ 
		//////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 11"))
		if (TurnToAdd->Speed < TurnOrder[i]->Speed)
		{
			//////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 12"))
				a = i;
		}
		else
		{
			a = TurnOrder.Num();
		}
	}

	TurnOrder.Insert(TurnToAdd, a);

}

bool UBattleBrainComponent::RunActiveTurn()
{
	if (ActiveTurn != NULL)
	{
		bool turnCompleted;
		DrawDebugPoint(GetWorld(), ActiveTurn->MyBattlePawn->GetActorLocation(), 50.f, FColor::Black, false, 0.1f);
		if (ActiveTurn->MyBattlePawn->isOwnedByPlayer)
		{
			//////UE_LOG(LogTemp, Warning, TEXT("Players Turn"));
			return turnCompleted = RunPlayersTurn();		
		}
		else
		{
			//////UE_LOG(LogTemp, Warning, TEXT("enemy Turn"));
			return turnCompleted = RunEnemyTurn();
		}
	}


	return false;
}

bool UBattleBrainComponent::RunPlayersTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("players turn 0"));
	if (watingForPlayersTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("watingForPlayersTarget 0"));
		PlayersCont->BattleHUD->ShowAttackMenue();

		return false;

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" No longer watingForPlayersTarget 0"));
		if (confirmedSingleTarget != NULL)
		{
			PlayersCont->BattleHUD->HideAttackMenue();
			UE_LOG(LogTemp, Warning, TEXT("confirmedSingleTarget 0"));
			
			return testOp2 = AttackMelee(confirmedSingleTarget);
		}

	}

	attaaaaTarget = enemyBattlePawns[1];
	testOperationCompleted = true;



		return testOp2 = AttackMelee(attaaaaTarget);

}

bool UBattleBrainComponent::RunEnemyTurn()
{


	attaaaaTarget = playerBattlePawns[1];
	testOperationCompleted = true;
	

	
	return testOp2 = AttackMelee(attaaaaTarget);
	
}

bool UBattleBrainComponent::AttackMelee(ABattlePawnBase* attackTarget)
{

	//rte do all
	////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee "));
	if (ActiveTurn->MyBattlePawn->attackActionCompleeted != true)
	{

		if (ActiveTurn->MyBattlePawn->bIsBackLine)
		{
			////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee im at back"));
			if (atStaginPoint1 != true)
			{
				////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee move to staging"));
				atStaginPoint1 = ActiveTurn->MyBattlePawn->MoveToLocation(ActiveTurn->MyBattlePawn->PawnsBaseActor->OpotunityPoint->GetComponentLocation());
				return false;
			}
		}
		//if (attackTarget->bIsBackLine)
		{
			////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee  target is back"));
			if (atopotunityLocation != true)
			{
				////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee move to opotunity"));
				atopotunityLocation = ActiveTurn->MyBattlePawn->MoveToLocation(attackTarget->PawnsBaseActor->OpotunityPoint->GetComponentLocation());
				return false;
			}
			if (awatingOpotunityDecision)
			{
				////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee  awating opotunity decision"));
				////put in functions for player and enemy opotunity decisions
				//return false;
			}
		}

		if (atAttackPosition != true)
		{
			ActiveTurn->MyBattlePawn->isAttackingMelee = true;
			atAttackPosition = ActiveTurn->MyBattlePawn->MoveToLocation(attackTarget->PawnsBaseActor->AttackPoint->GetComponentLocation());
			return false;
		}
		return false;

	}
	else
	{
		////////////UE_LOG(LogTemp, Warning, TEXT(" attack done goingg home "));
		if (variablesReset == false)
		{
			////////////UE_LOG(LogTemp, Warning, TEXT(" attack done goingg home variable reset one time "));
			ActiveTurn->MyBattlePawn->isAttackingMelee = false;
			atAttackPosition = false;
			awatingOpotunityDecision = true;
			atopotunityLocation = false;
			atStaginPoint1 = false;
			variablesReset = true;			
		}
		if (attackTarget->bIsBackLine)
		{
			////////////UE_LOG(LogTemp, Warning, TEXT(" attack done goingg home target is back line"));
			if (atopotunityLocation != true)
			{
				atopotunityLocation = ActiveTurn->MyBattlePawn->MoveToLocation(attackTarget->PawnsBaseActor->OpotunityPoint->GetComponentLocation());
				return false;
			}
		}
		if (ActiveTurn->MyBattlePawn->bIsBackLine)
		{
			if (atStaginPoint1 != true)
			{
				atStaginPoint1 = ActiveTurn->MyBattlePawn->MoveToLocation(ActiveTurn->MyBattlePawn->PawnsBaseActor->OpotunityPoint->GetComponentLocation());
				return false;
			}
		}
		if (atStagingPoint2 != true)
		{
			atStagingPoint2 = ActiveTurn->MyBattlePawn->MoveToLocation(ActiveTurn->MyBattlePawn->PawnsBaseActor->GetComponentLocation());
			return false;
		}
		if (faceingTargetLocation == false)
		{
			faceingTargetLocation = ActiveTurn->MyBattlePawn->RotateToTarget(ActiveTurn->MyBattlePawn->PawnsBaseActor->AttackPoint->GetComponentLocation());
			return false;
		}else
		{		
			//reset all used variables
			atStaginPoint1 = false;
			atStagingPoint2 = false;
			atAttackPosition = false;
			atopotunityLocation = false;
			backAtSpawn = false;
			awatingOpotunityDecision = true;
			variablesReset = false;
			faceingTargetLocation = false;
			ActiveTurn->MyBattlePawn->attackActionCompleeted = false;
			////////////UE_LOG(LogTemp, Warning, TEXT(" Attack rune Melee done"))
			return true;		
		}
		////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee atack completed move home "))
	}
	///return to ready position
	return false;
}

bool UBattleBrainComponent::AttackMagic(ABattlePawnBase* attackTarget)
{
	////UE_LOG(LogTemp, Warning, TEXT(" Attack magic"));
	//ActiveTurn->MyBattlePawn->isAttackingMagic = true;
	if (atStaginPoint1 != true)
	{
		atStaginPoint1 = ActiveTurn->MyBattlePawn->RotateToTarget(attackTarget->PawnsBaseActor->GetComponentLocation());
		ActiveTurn->MyBattlePawn->isAttackingMagic = true;
		////UE_LOG(LogTemp, Warning, TEXT(" Attack Magic Atttaaaaaa "));
	}
	if (ActiveTurn->MyBattlePawn->attackActionCompleeted == true)
	{
		////UE_LOG(LogTemp, Warning, TEXT(" Attack magic 2"));
		if (ActiveTurn->MyBattlePawn->RotateToTarget(ActiveTurn->MyBattlePawn->PawnsBaseActor->OpotunityPoint->GetComponentLocation()))
		{
			ActiveTurn->MyBattlePawn->isAttackingMagic = false;
			////UE_LOG(LogTemp, Warning, TEXT(" Attack magic 3"));
			ActiveTurn->MyBattlePawn->attackActionCompleeted = false;	
			atStaginPoint1 = false;
			return true;
		}
	}

	return false;
}

bool UBattleBrainComponent::AttackRanged(ABattlePawnBase* attackTarget)
{
	////UE_LOG(LogTemp, Warning, TEXT(" Attack range"));
	
	if (atStaginPoint1 != true)
	{
		atStaginPoint1 = ActiveTurn->MyBattlePawn->RotateToTarget(attackTarget->PawnsBaseActor->GetComponentLocation());
		ActiveTurn->MyBattlePawn->isAttackingRanged = true;
		////UE_LOG(LogTemp, Warning, TEXT(" Attack reange Atttaaaaaa "));
	}

	/// adjustt to get if projectile has hit when you make them
	if (ActiveTurn->MyBattlePawn->attackActionCompleeted == true)
	{
		////UE_LOG(LogTemp, Warning, TEXT(" Attack reange 2"));
		if (ActiveTurn->MyBattlePawn->RotateToTarget(ActiveTurn->MyBattlePawn->PawnsBaseActor->OpotunityPoint->GetComponentLocation()))
		{
			ActiveTurn->MyBattlePawn->isAttackingRanged = false;
			////UE_LOG(LogTemp, Warning, TEXT(" Attack range 3"));
			ActiveTurn->MyBattlePawn->attackActionCompleeted = false;
			atStaginPoint1 = false;
			return true;
		}
	}

	return false;
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
	////////////UE_LOG(LogTemp, Warning, TEXT("Turns left,%d"), AllPawnsInBattle.Num());
	
	ActiveTurn = NULL;
}

