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
			if (MyBattleZone)
			{
				UE_LOG(LogTemp, Warning, TEXT("inplayer cont"));
			}
			////UE_LOG(LogTemp, Warning, TEXT("crash check 1 %d"),);
			//start next turn
			ReCalcChrsTurns(ActiveTurn->MyBattlePawn);
			////UE_LOG(LogTemp, Warning, TEXT("crash check 2 %d"), );
	


			if (ActiveTurn->MyBattlePawn->isOwnedByPlayer == true)
			{
				attackMenueSpawned = false;
				confirmedSingleTarget = NULL;
				PlayersCont->lookingForHostile = false;
				PlayersCont->singleTarget = NULL;
				PlayersCont->lookingForHostile = false;
				PlayersCont->isWaitingForSingleTargetSelection = false;
				watingForPlayersTarget = true;
			}
			activeAbility = NULL;
			damageStepDone = false;
			ActiveTurn->MyBattlePawn->activeAbility = NULL;
			ActiveTurn = TurnOrder[0];
			TurnOrder.RemoveAt(0);
			PlayersCont->BattleHUD->CallCalcTurns();

			bool winCondition = true;
			bool failCondition = true;
			for (int y = 0; y < enemyBattlePawns.Num();y++)
			{

				if (enemyBattlePawns[y]->isDown != true)
				{
					winCondition = false;
				}
			}
			for (int y = 0; y < playerBattlePawns.Num();y++)
			{
				if (playerBattlePawns[y]->isDown != true)
				{
					failCondition = false;
				}
			}
			if (winCondition == true)
			{
				UE_LOG(LogTemp, Warning, TEXT("EndBattle "));
				EndBattle();
				
			}

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
	////////////////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 1 %d"), AllPawnsInBattle.Num());
	for (int t = 1; t < 6;t++)
	{
		////////////////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 2"));
		for (int i = 0; i < AllPawnsInBattle.Num();i++)
		{
			////////////////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 3"));
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
		////UE_LOG(LogTemp, Warning, TEXT("chr 111 %s"),*TurnOrder[i]->ChrName);
		////UE_LOG(LogTemp, Warning, TEXT("chr111 %f"), TurnOrder[i]->Speed);
		////UE_LOG(LogTemp, Warning, TEXT("chr 111111 %d"), TurnOrder[i]->Turn);
		bool hasBeenPlaced = false;
		int place = 0;
		if (WorkingTurnOrder.Num() > 0)
		{
			for (int q = 0; q < WorkingTurnOrder.Num();q++)
			{
				////UE_LOG(LogTemp, Warning, TEXT("chr wwwww %s"), *WorkingTurnOrder[q]->ChrName);
				////UE_LOG(LogTemp, Warning, TEXT("chr wwwwww %f"), WorkingTurnOrder[q]->Speed);
				////UE_LOG(LogTemp, Warning, TEXT("chr wwwwwwww %d"), WorkingTurnOrder[q]->Turn);
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
				////UE_LOG(LogTemp, Warning, TEXT("place place 1111 %d"), place);
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
		////UE_LOG(LogTemp, Warning, TEXT("chr fff %s"), *WorkingTurnOrder[y]->ChrName);
		////UE_LOG(LogTemp, Warning, TEXT("chrffff %f"), WorkingTurnOrder[y]->Speed);
		////UE_LOG(LogTemp, Warning, TEXT("chrffffff %d"), WorkingTurnOrder[y]->Turn);
		TurnOrder.Insert(WorkingTurnOrder[y],y);
	}
}

void UBattleBrainComponent::ReCalcChrsTurns(ABattlePawnBase* inPawn)
{
	TArray< UTurnInfo*> CurrentTurns;
	TArray<int>TurnNos;
	////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 1"));
	for (int i = 0; i < TurnOrder.Num();i++)
	{	
		////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 2"))
		if(TurnOrder[i]->MyBattlePawn ==inPawn)
		{
			////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 3"))
			CurrentTurns.Add(TurnOrder[i]);
		}
	}
	for(int j = 0; j < CurrentTurns.Num();j++)
	{
		////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 4"))
		//only update speed if it not the active turn
		if (CurrentTurns[j] != ActiveTurn) 
		{
			////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 5"))
			TurnNos.Add(CurrentTurns[j]->Turn);
			////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 6"))
			CurrentTurns[j]->Speed = CurrentTurns[j]->MyBattlePawn->mainCharInfo.Speed * CurrentTurns[j]->Turn;


			int iNewPosition;
			bool bElementAdded = 0;
			////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 7"));
			for (int p = 0;p < TurnOrder.Num();p++)
			{
				if (CurrentTurns[j] != TurnOrder[p])
				{
					////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 8"));
					if (CurrentTurns[j]->Speed < TurnOrder[p]->Speed)
					{
						////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 9"));
						iNewPosition = p;
						break;
						////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 10"));
					}
				}
				else if (CurrentTurns[j]->Speed == TurnOrder[p]->Speed)
				{
					iNewPosition = p;
					break;
				}



			}
			////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 13"));
			UTurnInfo* turnToinsert = CurrentTurns[j];
			TurnOrder.RemoveSingle(CurrentTurns[j]);
			////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 14"));
			TurnOrder.Insert(turnToinsert, iNewPosition);
			////UE_LOG(LogTemp, Warning, TEXT("Calc Turn order 15"));
		}
	}
	while (TurnNos.Num() < 4)
	{
		////////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 7 %d"), CurrentTurns.Num())
		int HighestTurnNo = 0;
		for (int u = 0; u < TurnNos.Num();u++)
		{
			////////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 8"))
			if (TurnNos[u] > HighestTurnNo)
			{
				////////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 9 %d"), HighestTurnNo)
				HighestTurnNo = TurnNos[u];
			}
		}
		////////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 10"))
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
		////////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 11"))
		if (TurnToAdd->Speed < TurnOrder[i]->Speed)
		{
			////////////UE_LOG(LogTemp, Warning, TEXT("ReCalcChrsTurns 12"))
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

		RunPawnBeginTrun(ActiveTurn->MyBattlePawn);

		if (ActiveTurn->MyBattlePawn->isOwnedByPlayer)
		{
			////////UE_LOG(LogTemp, Warning, TEXT("Players Turn"));
			return turnCompleted = RunPlayersTurn();		
		}
		else
		{
			////////UE_LOG(LogTemp, Warning, TEXT("enemy Turn"));
			return turnCompleted = RunEnemyTurn();
		}
	}


	return false;
}

bool UBattleBrainComponent::RunPlayersTurn()
{
	////UE_LOG(LogTemp, Warning, TEXT("players turn 0"));
	if (watingForPlayersTarget)
	{
		////UE_LOG(LogTemp, Warning, TEXT("watingForPlayersTarget 0"));
		if (attackMenueSpawned != true)
		{
			attackMenueSpawned = true;
			PlayersCont->BattleHUD->ShowAttackMenue();
		}


		return false;

	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT(" No longer watingForPlayersTarget 0"));
		if (confirmedSingleTarget != NULL)
		{
			PlayersCont->BattleHUD->HideAttackMenue();
			//UE_LOG(LogTemp, Warning, TEXT("confirmedSingleTarget 0"));
			
			if (activeAbility)
			{
				if (activeAbility->AttackStyle == EAttackStyle::Melee)
				{
					return testOp2 = AttackMelee(confirmedSingleTarget);
				}
				if (activeAbility->AttackStyle == EAttackStyle::Magic)
				{
					return testOp2 = AttackMagic(confirmedSingleTarget);
				}
				if (activeAbility->AttackStyle == EAttackStyle::Rganged)
				{
					return testOp2 = AttackRanged(confirmedSingleTarget);
				}
			}
			else
			{
				return testOp2 = AttackMelee(confirmedSingleTarget);
			}




			//return testOp2 = AttackMelee(confirmedSingleTarget);
		}
		/// more for difrent attack types




	}

	attaaaaTarget = enemyBattlePawns[1];
	testOperationCompleted = true;



		return testOp2 = AttackMelee(attaaaaTarget);

}

bool UBattleBrainComponent::RunEnemyTurn()
{


	for (int i = 0; i < playerBattlePawns.Num();i++)
	{
		if (playerBattlePawns[i]->bIsBackLine)
		{

			attaaaaTarget = playerBattlePawns[i];
		}
	}

	
	return testOp2 = AttackMelee(attaaaaTarget);
	
}

void UBattleBrainComponent::RemovePawnsTurns(ABattlePawnBase* inPawn)
{
	for (int j = 0; j < TurnOrder.Num();j++)
	{
		if (TurnOrder[j]->MyBattlePawn == inPawn)
		{
			TurnOrder.RemoveAt(j);
			j -= 1;
		}	
	}
	PlayersCont->BattleHUD->CalcTurnsHUD();
}

void UBattleBrainComponent::RunPawnBeginTrun(ABattlePawnBase* inPawn)
{
	ResetPawnsReaction(inPawn);

}

void UBattleBrainComponent::ResetPawnsReaction(ABattlePawnBase* inPawn)
{
	inPawn->bHasReaction = true;
}

void UBattleBrainComponent::RunPawnEndTurn(ABattlePawnBase* inPawn)
{
}

TArray<ABattlePawnBase*> UBattleBrainComponent::FindAvalibleForOpotunity(ABattlePawnBase* inTarget)
{
	TArray<ABattlePawnBase*> pawnsToReturn;
	if (inTarget->bIsBackLine != true)
	{	
		return pawnsToReturn;
	}

	TArray<ABattlePawnBase*> pawnSetToCheck;
	if (ActiveTurn->MyBattlePawn->isOwnedByPlayer)
	{
		pawnSetToCheck = enemyBattlePawns ;
	}
	else
	{
		pawnSetToCheck = playerBattlePawns;
	}

	int placeToCheck1 = 0;
	int placeToCheck2 = 0;

	if (inTarget->PawnsBaseActor->placeOnGrid == 5)
	{
		placeToCheck1 = 1;
		placeToCheck2 = 2;
	}
	if (inTarget->PawnsBaseActor->placeOnGrid == 6)
	{
		placeToCheck1 = 2;
		placeToCheck2 = 3;
	}
	if (inTarget->PawnsBaseActor->placeOnGrid == 7)
	{
		placeToCheck1 = 3;
		placeToCheck2 = 4;
	}
	if (inTarget->PawnsBaseActor->placeOnGrid == 8)
	{
		placeToCheck1 = 4;
		placeToCheck2 = 0;
	}

	for (int i = 0; i < pawnSetToCheck.Num();i++)
	{
		if (pawnSetToCheck[i]->PawnsBaseActor->placeOnGrid == placeToCheck1)
		{
			DrawDebugPoint(GetWorld(), pawnSetToCheck[i]->GetActorLocation(), 60.f, FColor::Emerald, false, 2.f);
			if (pawnSetToCheck[i]->bHasReaction)
			{
				pawnsToReturn.Add(pawnSetToCheck[i]);
			}
		}
		if (pawnSetToCheck[i]->PawnsBaseActor->placeOnGrid == placeToCheck2)
		{
			DrawDebugPoint(GetWorld(), pawnSetToCheck[i]->GetActorLocation(), 60.f, FColor::Emerald, false, 2.f);
			if (pawnSetToCheck[i]->bHasReaction)
			{
				pawnsToReturn.Add(pawnSetToCheck[i]);
			}
		}
	}

	return pawnsToReturn;;
}

bool UBattleBrainComponent::SpawnOpotunityMenue(TArray<ABattlePawnBase*> inPawn)
{
	return true;
}

bool UBattleBrainComponent::RunOpotunityAttack()
{
	if (opotunityAttackPreformed != true)
	{
		if (atOpotunityPoint1 != true)
		{
			pawnToOpotunity->bHasReaction = false;
			UE_LOG(LogTemp, Warning, TEXT(" RunOpotunityAttack1 "));
			atOpotunityPoint1 = pawnToOpotunity->RotateToTarget(ActiveTurn->MyBattlePawn->GetActorLocation());
			return false;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT(" RunOpotunityAttack2 "));
			pawnToOpotunity->isAtackingOpotunity = true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT(" RunOpotunityAttack3 "));
	if (pawnToOpotunity->opotunityActionCompleeted == true)
	{
		UE_LOG(LogTemp, Warning, TEXT(" RunOpotunityAttack4 "));
		pawnToOpotunity->opotunityActionCompleeted = false;
		opotunityAttackPreformed = true;
	}

	if (atOpotunityPoint2 != true)
	{
		UE_LOG(LogTemp, Warning, TEXT(" RunOpotunityAttack5 "));
		atOpotunityPoint2 = pawnToOpotunity->RotateToTarget(pawnToOpotunity->PawnsBaseActor->OpotunityPoint->GetComponentLocation());
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT(" RunOpotunityAttack6 "));
	atOpotunityPoint1 = false;
	atOpotunityPoint2 = false;
	opotunityAttackPreformed = false;
	awatingOpotunityDecision = false;
	pawnToOpotunity->opotunityActionCompleeted = false;
	pawnToOpotunity->isAtackingOpotunity = false;
	return true;
}

bool UBattleBrainComponent::CanCounter(ABattlePawnBase* inPawn)
{
	if (inPawn->bHasReaction != true)
	{
		return false;
	}

	int randNo = FMath::RandRange(0.f, 100.f);
	randNo = FMath::RoundToInt(randNo);
	if (randNo < inPawn->mainCharInfo.counterChance)
	{
		return true;
	}

	return false;
}

bool UBattleBrainComponent::RunCounter(ABattlePawnBase* inPawn)
{	
	if (inPawn->bHasReaction)
	{
		UE_LOG(LogTemp, Warning, TEXT(" bHasReaction "));
		if (counterBool1 == false)
		{
			UE_LOG(LogTemp, Warning, TEXT(" counterBool1 "));
			if (inPawn->RotateToTarget(ActiveTurn->MyBattlePawn->GetActorLocation()))
			{
				UE_LOG(LogTemp, Warning, TEXT(" RotateToTarget "));
				counterBool1 = true;
			}
			return false;
		}
		if (inPawn->CounterActionCompleeted != true)
		{
			UE_LOG(LogTemp, Warning, TEXT(" CounterActionCompleeted "));
			inPawn->isAtackingCounter = true;
			return false;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT(" CounterActionCompleeted2 "));
			inPawn->isAtackingCounter = false;
		}
		if (inPawn->RotateToTarget(inPawn->PawnsBaseActor->OpotunityPoint->GetComponentLocation()))
		{
			UE_LOG(LogTemp, Warning, TEXT(" RotateToTarget 2 "));
			inPawn->CounterActionCompleeted = false;
			counterBool1 = false;
			counterBool2 = false;
			inPawn->bHasReaction = false;
			return true;
		}
	}
	return false;
}

bool UBattleBrainComponent::RunStandingAttack(ABattlePawnBase* inTarget, ABattlePawnBase* inOwner)
{
	return false;
}

bool UBattleBrainComponent::AttackMelee(ABattlePawnBase* attackTarget)
{ 
	//rte do all
	//////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee "));
	if (ActiveTurn->MyBattlePawn->attackActionCompleeted != true)
	{
		if (ActiveTurn->MyBattlePawn->bIsBackLine)
		{
			//////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee im at back"));
			if (atStaginPoint1 != true)
			{
				//////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee move to staging"));
				atStaginPoint1 = ActiveTurn->MyBattlePawn->MoveToLocation(ActiveTurn->MyBattlePawn->PawnsBaseActor->OpotunityPoint->GetComponentLocation());
				return false;
			}
		}
		//if (attackTarget->bIsBackLine)
		{
			//////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee  target is back"));
			if (atopotunityLocation != true)
			{
				//////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee move to opotunity"));
				atopotunityLocation = ActiveTurn->MyBattlePawn->MoveToLocation(attackTarget->PawnsBaseActor->OpotunityPoint->GetComponentLocation());
				return false;
			}
			if (awatingOpotunityDecision)
			{
				UE_LOG(LogTemp, Warning, TEXT(" Attack Melee  awating opotunity decision"));
				
				if (ActiveTurn->MyBattlePawn->isOwnedByPlayer != true)
				{
					if (pawnToOpotunity == NULL)
					{
						UE_LOG(LogTemp, Warning, TEXT(" pawnToOpotunity 1"));
						if (serchedForOpotunityPawns != true)
						{
							UE_LOG(LogTemp, Warning, TEXT(" pawnToOpotunity 2"));
							pawnsForOpotunityDecision = FindAvalibleForOpotunity(attackTarget);
							serchedForOpotunityPawns = true;
						}
						if (pawnsForOpotunityDecision.Num() > 0)
						{
							UE_LOG(LogTemp, Warning, TEXT(" pawnToOpotunity 3"));
							if (pawnToOpotunity == NULL)
							{
								UE_LOG(LogTemp, Warning, TEXT(" pawnToOpotunity 4"));
								if (PlayersCont->BattleHUD->hasCreatedOpotunityMenu != true)
								{
									UE_LOG(LogTemp, Warning, TEXT(" pawnToOpotunity 5"));
									PlayersCont->BattleHUD->CreateOpotunityMenu();
									PlayersCont->BattleHUD->hasCreatedOpotunityMenu = true;
									return false;
								}
								UE_LOG(LogTemp, Warning, TEXT(" pawnToOpotunity 6"));
								return false;
							}
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT(" pawnToOpotunity 7"));
							awatingOpotunityDecision = false;
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT(" pawnToOpotunity do attack"));
						if (RunOpotunityAttack()!=true)
						{
							PlayersCont->BattleHUD->RemoveOpotunityMenu();
							PlayersCont->BattleHUD->hasCreatedOpotunityMenu = false;
							return false;
						}
					}
				}
				else
				{
					//NPCOpotunityDecision();
				}
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
		if (variablesReset == false)
		{
			//////////////UE_LOG(LogTemp, Warning, TEXT(" attack done goingg home variable reset one time "));
			ActiveTurn->MyBattlePawn->isAttackingMelee = false;
			atAttackPosition = false;
			atopotunityLocation = false;
			atStaginPoint1 = false;
			variablesReset = true;
			serchedForOpotunityPawns = false;
			pawnToOpotunity = NULL;
		}

		///Damage Step REWORK this do damage from abilitys if we have one so i can do more interesting things from them
		if (damageStepDone == false)
		{
			if (activeAbility != NULL)
			{
				TArray<ABattlePawnBase*> targets;
				targets = activeAbility->AbilitysInstructions(ActiveTurn->MyBattlePawn, attackTarget);
				ActiveTurn->MyBattlePawn->activeAbility = activeAbility;
				if (activeAbility->isHealing != true)
				{
					UE_LOG(LogTemp, Warning, TEXT(" Attack Magic Atttaaaaaa 2"));
					for (int d = 0; d < targets.Num();d++)
					{
						UE_LOG(LogTemp, Warning, TEXT(" Attack Magic Atttaaaaaa 3"));
						ActiveTurn->MyBattlePawn->CauseDamageToBattlePawn(targets[d]);
					}
				}
				else
				{
					for (int d = 0; d < targets.Num();d++)
					{
						ActiveTurn->MyBattlePawn->HealTarget(targets[d]);
					}
				}

			}
			else
			{
				ActiveTurn->MyBattlePawn->CauseDamageToBattlePawn(attackTarget);
			}
			damageStepDone = true;

		}



			////countre Attack
			if (CountreAtempted != true)
			{
				UE_LOG(LogTemp, Warning, TEXT(" CountreAtempted "));
				CountreAtempted = true;
				canCounter = CanCounter(attackTarget);
			}
			if (canCounter)
			{
				UE_LOG(LogTemp, Warning, TEXT(" canCounter "));
				if (awatingCounterDecision)
				{
					UE_LOG(LogTemp, Warning, TEXT(" awatingCounterDecision "));
					if (attackTarget->isOwnedByPlayer)
					{
						UE_LOG(LogTemp, Warning, TEXT(" CountreAtempted 2"));
						PlayersCont->BattleHUD->CreateCounterMenu();
						return false;
					}
					else
					{

					}

				}
				else if (counterAproved)
				{
					
					UE_LOG(LogTemp, Warning, TEXT(" counterAproved "));
					PlayersCont->BattleHUD->RemoveCounterMenu();

					

					if (RunCounter(attackTarget) == false)
					{
						counterBool3 = true;
						UE_LOG(LogTemp, Warning, TEXT(" RunCounter return "));
						return false;
					}
					else
					{
						canCounter = false;
					}
				}
			}
		
	


		//////////////UE_LOG(LogTemp, Warning, TEXT(" attack done goingg home "));

		if (attackTarget->bIsBackLine)
		{
			//////////////UE_LOG(LogTemp, Warning, TEXT(" attack done goingg home target is back line"));
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
			UE_LOG(LogTemp, Warning, TEXT(" reset all used variables "));
			//reset all used variables
			counterBool3 = false;
			awatingCounterDecision = true;
			counterAproved = false;
			atStaginPoint1 = false;
			atStagingPoint2 = false;
			atAttackPosition = false;
			atopotunityLocation = false;
			backAtSpawn = false;
			canCounter = false;
			awatingCounterDecision = true;
			awatingOpotunityDecision = true;
			variablesReset = false;
			faceingTargetLocation = false;
			ActiveTurn->MyBattlePawn->attackActionCompleeted = false;
			CountreAtempted = false;
			//////////////UE_LOG(LogTemp, Warning, TEXT(" Attack rune Melee done"))
			return true;		
		}
		//////////////UE_LOG(LogTemp, Warning, TEXT(" Attack Melee atack completed move home "))
	}
	///return to ready position
	return false;
}

bool UBattleBrainComponent::AttackMagic(ABattlePawnBase* attackTarget)
{
	//////UE_LOG(LogTemp, Warning, TEXT(" Attack magic"));
	//ActiveTurn->MyBattlePawn->isAttackingMagic = true;
	if (atStaginPoint1 != true)
	{
		atStaginPoint1 = ActiveTurn->MyBattlePawn->RotateToTarget(attackTarget->PawnsBaseActor->GetComponentLocation());
		ActiveTurn->MyBattlePawn->isAttackingMagic = true;
		//////UE_LOG(LogTemp, Warning, TEXT(" Attack Magic Atttaaaaaa "));
	}
	if (ActiveTurn->MyBattlePawn->attackActionCompleeted == true)
	{
		if (damageStepDone == false)
		{
			if (activeAbility != NULL)
			{
				TArray<ABattlePawnBase*> targets;
				ActiveTurn->MyBattlePawn->activeAbility = activeAbility;
				targets = activeAbility->AbilitysInstructions(ActiveTurn->MyBattlePawn, attackTarget);
				if (activeAbility->isHealing != true)
				{	
					UE_LOG(LogTemp, Warning, TEXT(" Attack Magic Atttaaaaaa 2"));
					for (int d = 0; d < targets.Num();d++)
					{
						UE_LOG(LogTemp, Warning, TEXT(" Attack Magic Atttaaaaaa 3"));
						ActiveTurn->MyBattlePawn->CauseDamageToBattlePawn(targets[d]);
					}
				}
				else
				{
					for (int d = 0; d < targets.Num();d++)
					{
						ActiveTurn->MyBattlePawn->HealTarget(targets[d]);
					}
				}

			}
			else
			{
				ActiveTurn->MyBattlePawn->CauseDamageToBattlePawn(attackTarget);
			}
			damageStepDone = true;
		}
		//////UE_LOG(LogTemp, Warning, TEXT(" Attack magic 2"));
		if (ActiveTurn->MyBattlePawn->RotateToTarget(ActiveTurn->MyBattlePawn->PawnsBaseActor->OpotunityPoint->GetComponentLocation()))
		{
			ActiveTurn->MyBattlePawn->isAttackingMagic = false;
			//////UE_LOG(LogTemp, Warning, TEXT(" Attack magic 3"));
			ActiveTurn->MyBattlePawn->attackActionCompleeted = false;	
			atStaginPoint1 = false;
			return true;
		}
	}

	return false;
}

bool UBattleBrainComponent::AttackRanged(ABattlePawnBase* attackTarget)
{
	//////UE_LOG(LogTemp, Warning, TEXT(" Attack range"));
	
	if (atStaginPoint1 != true)
	{
		atStaginPoint1 = ActiveTurn->MyBattlePawn->RotateToTarget(attackTarget->PawnsBaseActor->GetComponentLocation());
		ActiveTurn->MyBattlePawn->isAttackingRanged = true;
		//////UE_LOG(LogTemp, Warning, TEXT(" Attack reange Atttaaaaaa "));
	}

	/// adjustt to get if projectile has hit when you make them
	if (ActiveTurn->MyBattlePawn->attackActionCompleeted == true)
	{
		if (damageStepDone == false)
		{
			if (activeAbility != NULL)
			{
				TArray<ABattlePawnBase*> targets;
				ActiveTurn->MyBattlePawn->activeAbility = activeAbility;
				targets = activeAbility->AbilitysInstructions(ActiveTurn->MyBattlePawn, attackTarget);
				if (activeAbility->isHealing != true)
				{
					UE_LOG(LogTemp, Warning, TEXT(" Attack AttackRanged Atttaaaaaa 2"));
					for (int d = 0; d < targets.Num();d++)
					{
						UE_LOG(LogTemp, Warning, TEXT(" Attack AttackRanged Atttaaaaaa 3"));
						ActiveTurn->MyBattlePawn->CauseDamageToBattlePawn(targets[d]);
					}
				}
				else
				{
					for (int d = 0; d < targets.Num();d++)
					{
						ActiveTurn->MyBattlePawn->HealTarget(targets[d]);
					}
				}

			}
			else
			{
				ActiveTurn->MyBattlePawn->CauseDamageToBattlePawn(attackTarget);
			}
			damageStepDone = true;
		}
		//////UE_LOG(LogTemp, Warning, TEXT(" Attack reange 2"));
		if (ActiveTurn->MyBattlePawn->RotateToTarget(ActiveTurn->MyBattlePawn->PawnsBaseActor->OpotunityPoint->GetComponentLocation()))
		{
			ActiveTurn->MyBattlePawn->isAttackingRanged = false;
			//////UE_LOG(LogTemp, Warning, TEXT(" Attack range 3"));
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

	PlayersCont->BattleHUDDespawn();
	PlayersCont->BattleHUDENDSpawn();

}

void UBattleBrainComponent::ClearTurnOrders()
{
	TurnOrder.Empty();
	TurnOrder.SetNum(0);
	WorkingTurnOrder.Empty();
	WorkingTurnOrder.SetNum(0);
	AllPawnsInBattle.Empty();
	//////////////UE_LOG(LogTemp, Warning, TEXT("Turns left,%d"), AllPawnsInBattle.Num());
	
	ActiveTurn = NULL;
}

