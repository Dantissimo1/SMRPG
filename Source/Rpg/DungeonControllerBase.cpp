// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonControllerBase.h"
#include "DungeonCharacterBase.h"
#include "EncounterVolumeBase.h"
#include "BattleZoneBase.h"
#include "PlayerPartyComponent.h"
#include "BattleHUD.h"
#include "DungeonHUD.h"
#include "TurnInfo.h"
#include "BattlePawnBase.h"
#include "BattleSpawnPoint.h"
#include "DrawDebugHelpers.h"
#include "AbilityBase.h"
#include "BattleSpawnPoint.h"
#include "BattleHUDENDMenu.h"




// Sets default values
ADungeonControllerBase::ADungeonControllerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayersParty = CreateDefaultSubobject<UPlayerPartyComponent>(TEXT("Players Party"));
	PlayersParty->MyController = this;
	
}

// Called when the game starts or when spawned
void ADungeonControllerBase::BeginPlay()
{
	Super::BeginPlay();

	MyChar = Cast<ADungeonCharacterBase>(GetCharacter());

	//// load the players party here??

	SpawnDungeonHUD();
	
}

// Called every frame
void ADungeonControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (skillSelected == true)
	{
		UE_LOG(LogTemp, Warning, TEXT(" skillSelected 1"));
		if (activeAbility == NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT(" activeAbility == NULL 1"));
			isWaitingForSingleTargetSelection = true;
			lookingForHostile = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT(" activeAbility exists 1"));
			lookingForHostile = activeAbility->targetsHostile;
			UE_LOG(LogTemp, Warning, TEXT(" activeAbility exists 2"));
			
			
			if (activeAbility->attackType == EAttackType::singleTarget)
			{
				isWaitingForSingleTargetSelection = true;
			}
			if (activeAbility->attackType == EAttackType::aoeMed)
			{
				isWaitingForSingleTargetSelection = true;
				isWaitingForMedAoeSelection = true;
			}
			if (activeAbility->attackType == EAttackType::aoePartywide)
			{
				isWaitingForPartyAOESelection = true;
			}
		}
	}
	if (isWaitingForSingleTargetSelection)
	{
		if (lookingForHostile)
		{
			if (hasSetLastTarget == false && CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget && CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget->isDown != true)
			{
				UE_LOG(LogTemp, Warning, TEXT("wating set singel to last 0"));
				singleTarget = CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget;
				UE_LOG(LogTemp, Warning, TEXT(" Loooking for hostile 1"));
				SetViewTargetWithBlend(singleTarget, 0.3f);
				UE_LOG(LogTemp, Warning, TEXT(" Looking for hostile 2"));
				hasSetLastTarget = true;
			}
			if (singleTarget == NULL)
			{
				UE_LOG(LogTemp, Warning, TEXT("single targe t null"));
				singleTarget = SelectFirstHostileTarget();
				SetViewTargetWithBlend(singleTarget, 1.0f);
			}
			else
			{
				SetViewTargetWithBlend(singleTarget, 0.3f);
			}			
		}
		else
		{
			if (hasSetLastTarget == false && CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastFreindlyTarget && CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastFreindlyTarget->isDown != true)
			{
				UE_LOG(LogTemp, Warning, TEXT("wating set singel to ally last 0"));
				singleTarget = CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastFreindlyTarget;
				UE_LOG(LogTemp, Warning, TEXT(" Loooking for ally 1"));
				SetViewTargetWithBlend(singleTarget, 0.3f);
				UE_LOG(LogTemp, Warning, TEXT(" Looking for ally 2"));
				hasSetLastTarget = true;
			}
			if (singleTarget == NULL)
			{
				UE_LOG(LogTemp, Warning, TEXT("single targe ally null"));
				singleTarget = SelectFirstHostileTarget();
				SetViewTargetWithBlend(singleTarget, 1.0f);
			}
			else
			{
				SetViewTargetWithBlend(singleTarget, 0.3f);
			}
		}
		DrawDebugPoint(GetWorld(), singleTarget->GetActorLocation(), 100.f, FColor::Red, false, 0.1f);
	}
	
}


// Called to bind functionality to input
void ADungeonControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &ADungeonControllerBase::JumpInput);
	InputComponent->BindAxis("MoveForward", this, &ADungeonControllerBase::ForwardsInput);
	InputComponent->BindAxis("MoveRight", this, &ADungeonControllerBase::HorizontalInput);
	InputComponent->BindAxis("Turn", this, &ADungeonControllerBase::CameraYawInput);
	InputComponent->BindAxis("LookUp", this, &ADungeonControllerBase::CameraPitchInput);
	InputComponent->BindAxis("Scroll", this, &ADungeonControllerBase::ScrollInput);
	InputComponent->BindAction("Back", IE_Pressed,this, &ADungeonControllerBase::Back);
}

void ADungeonControllerBase::ForwardsInput(float Value)
{
	if (bIsInBattleMode != true)
	{
		MyChar->ForwardsInput(Value);
	}
	else if (isWaitingForSingleTargetSelection)
	{
		if (Value > 0 || Value < 0)
		{
			SelectSingleVertical(Value);
		}
	}




}

void ADungeonControllerBase::HorizontalInput(float Value)
{
	if (bIsInBattleMode != true)
	{
		MyChar->HorizontalInput(Value);
	}
	else if (isWaitingForSingleTargetSelection)
	{
		if (Value > 0 || Value < 0)
		{
			SelectSingleHorizontal(Value);
		}
	}
}

void ADungeonControllerBase::JumpInput()
{
	if (bIsInBattleMode != true)
	{
		GetCharacter()->Jump();
	}
	else if (isWaitingForSingleTargetSelection)
	{
		ConfirmSingleTarget();
	}
}

void ADungeonControllerBase::Back()
{
	UE_LOG(LogTemp, Warning, TEXT("Back"));

	if (BattleHUD != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Back  2"));
		if (BattleHUD->selectingTargets == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Back   3")); 
			BattleHUD->selectingTargets = false;
			BattleHUD->BackToAttackSelection();
			isWaitingForSingleTargetSelection = false;
			isWatingForSmallAOESelection = false;
			isWaitingForMedAoeSelection = false;
			isWaitingForPartyAOESelection = false;
			skillSelected = false;
			activeAbility = NULL;
			singleTarget = NULL;
			//BattleHUD->selectingTargets = false;
			SetViewTargetWithBlend(CurrentBattleArea, 0.3f);
		}



	}


}

void ADungeonControllerBase::CameraYawInput(float Value)
{
	if (bIsInBattleMode != true)
	{
		MyChar->CameraYawInput(Value);
	}
}

void ADungeonControllerBase::CameraPitchInput(float Value)
{
	if (bIsInBattleMode != true)
	{
		MyChar->CameraPitchInput(Value);
	}
}

void ADungeonControllerBase::ScrollInput(float Value)
{
	if (bIsInBattleMode != true)
	{
		MyChar->ScrollCamera(Value);
	}


}

void ADungeonControllerBase::SpawnDungeonHUD()
{
	if (DungeonHUDClass)
	{
		DungeonHUD = CreateWidget<UDungeonHUD>(this, DungeonHUDClass);
		DungeonHUD->AddToViewport();
		DungeonHUD->SetVisibility(ESlateVisibility::Visible);
	}else
	{
	
	}
}

void ADungeonControllerBase::ToggleDungeonHUD(bool hudOn)
{
	if (hudOn)
	{
		DungeonHUD->SetVisibility(ESlateVisibility::Visible);
	}
	else if (hudOn != true)
	{
		DungeonHUD->SetVisibility(ESlateVisibility::Hidden);
	}


}

void ADungeonControllerBase::SetBattleCamlocation(FVector* newLoc, FRotator* newRot)
{


}

void ADungeonControllerBase::BattleHUDSpawn()
{
	if (BattleHUDClass)
	{
		BattleHUD = CreateWidget<UBattleHUD>(this, BattleHUDClass);
		BattleHUD->AddToViewport();
		BattleHUD->SetVisibility(ESlateVisibility::Visible);
		////UE_LOG(LogTemp, Warning, TEXT("UBattleBrainComponent 0"));
		BattleHUD->SetUp(CurrentBattleArea->BattleBrain, this);

	}
	else
	{

	}
}


void ADungeonControllerBase::BattleHUDDespawn()
{
	if (BattleHUD)
	{
		BattleHUD->RemoveFromParent();
	}
}

void ADungeonControllerBase::BattleHUDENDSpawn()
{
	UE_LOG(LogTemp, Warning, TEXT("BattleHUDENDSpawn 0"));
	if (BattleHUDENDClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("BattleHUDENDSpawn 0"));
		BattleEndMenue = CreateWidget<UBattleHUDENDMenu>(this, BattleHUDENDClass);
		BattleEndMenue->AddToViewport();
		BattleEndMenue->SetVisibility(ESlateVisibility::Visible);
		
		BattleEndMenue->SetUp(CurrentBattleArea->BattleBrain, this);

	}
}

void ADungeonControllerBase::BattleHUDENDDeSpawn()
{
	if (BattleEndMenue)
	{
		BattleEndMenue->RemoveFromParent();
	}
}

void ADungeonControllerBase::SelectSingleHorizontal(float value)
{
	
	if (switchTimerReady == true)
	{
		GetWorldTimerManager().SetTimer(tSwitchTimerHandle, this, &ADungeonControllerBase::ToggleSwitchTimer, 0.5f, false);
		switchTimerReady = false;

		TArray<UBattleSpawnPoint*>spawnPointsToUse;
		if (lookingForHostile == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal  lookingForHostile 1"));
			spawnPointsToUse = CurrentBattleArea->EnemyBattleSpawns;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal  lookingForHostile 1"));
			spawnPointsToUse = CurrentBattleArea->PlayerBattleSpawns;
		}

		UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 1"));

			int rowMin = 1;
			int rowMax = 4;
			if (singleTarget->bIsBackLine == true)
			{
				rowMin = 5;
				rowMax = 8;
			}

			UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 4"));
			int newPlaceOnGrid = 0;
			if (value > 0)
			{
				newPlaceOnGrid = singleTarget->PawnsBaseActor->placeOnGrid;
				UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 5 %d"), newPlaceOnGrid);

				bool HasBeenPlacedOnRow = false;
				for (int y = 1;y < 5;y++)
				{
					UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 6.01 %d"), y);
					if (singleTarget->bIsBackLine == true)
					{
						rowMin = 5;
						rowMax = 8;
					}
					newPlaceOnGrid += 1;
					if (newPlaceOnGrid > rowMax)
					{
						UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 6.1 %d"), newPlaceOnGrid);
						newPlaceOnGrid = rowMin;
						UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 6.2 "));
						y = 1;
					}
					if (spawnPointsToUse[newPlaceOnGrid - 1]->myPawn != NULL && spawnPointsToUse[newPlaceOnGrid - 1]->myPawn->isDown != true)//&& spawnPointsToUse[newPlaceOnGrid - 1]->myPawn != singleTarget
					{
						UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 7 %d"), newPlaceOnGrid);
						singleTarget = spawnPointsToUse[newPlaceOnGrid - 1]->myPawn;
						SetViewTargetWithBlend(singleTarget, .3f);
						HasBeenPlacedOnRow = true;
						return;
					}
				}
			}
			if (value < 0)
			{
				newPlaceOnGrid = singleTarget->PawnsBaseActor->placeOnGrid;
				UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 5 %d"), newPlaceOnGrid);

				bool HasBeenPlacedOnRow = false;
				for (int y = 1;y < 5;y++)
				{
					if (singleTarget->bIsBackLine == true)
					{
						UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 5.8 %d"), newPlaceOnGrid);
						rowMin = 5;
						rowMax = 8;
					}
					newPlaceOnGrid -= 1;
					if (newPlaceOnGrid < rowMin)
					{
						UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 6 %d"), newPlaceOnGrid);
						newPlaceOnGrid = rowMax;
						y = 1;
					}
					UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 6.7 %d"), newPlaceOnGrid);
					if (spawnPointsToUse[newPlaceOnGrid - 1]->myPawn != NULL && spawnPointsToUse[newPlaceOnGrid - 1]->myPawn->isDown != true)//&& spawnPointsToUse[newPlaceOnGrid - 1]->myPawn != singleTarget
					{
						UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 7 %d"), newPlaceOnGrid);
						singleTarget = spawnPointsToUse[newPlaceOnGrid - 1]->myPawn;
						SetViewTargetWithBlend(singleTarget, .3f);
						HasBeenPlacedOnRow = true;
						return;
					}
				}
			}	
	}
}

void ADungeonControllerBase::SelectSingleVertical(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("SelectSingleVertical 1"));

	TArray<UBattleSpawnPoint*>spawnPointsToUse;
	if (lookingForHostile == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal  lookingForHostile 1"));
		spawnPointsToUse = CurrentBattleArea->EnemyBattleSpawns;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal  lookingForHostile 1"));
		spawnPointsToUse = CurrentBattleArea->PlayerBattleSpawns;
	}

		if (switchTimerReady == true)
		{
			int newPlaceOnGrid;
			GetWorldTimerManager().SetTimer(tSwitchTimerHandle, this, &ADungeonControllerBase::ToggleSwitchTimer, 0.5f, false);
			switchTimerReady = false;
			if (singleTarget->bIsBackLine != true)
			{
				if (SearchValidBackline(spawnPointsToUse)!=NULL)
				{
					if (SearchValidBackline(spawnPointsToUse)->PawnsBaseActor->placeOnGrid != NULL)
					{
						newPlaceOnGrid = SearchValidBackline(spawnPointsToUse)->PawnsBaseActor->placeOnGrid;
					}
				}
				else
				{
					newPlaceOnGrid = SearchValidFrontline(spawnPointsToUse)->PawnsBaseActor->placeOnGrid;
				}
			}
			else
			{
				if (SearchValidFrontline(spawnPointsToUse) != NULL)
				{
					if (SearchValidFrontline(spawnPointsToUse)->PawnsBaseActor->placeOnGrid != NULL)
					{
						newPlaceOnGrid = SearchValidFrontline(spawnPointsToUse)->PawnsBaseActor->placeOnGrid;
					}
				}
				else 
				{
					newPlaceOnGrid = SearchValidBackline(spawnPointsToUse)->PawnsBaseActor->placeOnGrid;
				}
			}
			
			singleTarget = spawnPointsToUse[newPlaceOnGrid - 1]->myPawn;
			SetViewTargetWithBlend(singleTarget, .3f);
		}
}

ABattlePawnBase* ADungeonControllerBase::SelectFirstHostileTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 1"));

	if (lookingForHostile)
	{
		if (CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget != NULL)
		{
			//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 6"));
			if (CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget->isDown != true)
			{
				return CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget;
			}
			UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 2"));
		}
		
		
			//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 6"));
			ABattlePawnBase* target = NULL;
			for (int i = 0; i < CurrentBattleArea->enemyBattlePawns.Num();i++)
			{

				//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 4"));
				if (CurrentBattleArea->enemyBattlePawns[i]->isDown != true)
				{
					return target = CurrentBattleArea->enemyBattlePawns[i];
				}

			}if (target == NULL)
			{
				//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 5"));
				return target = CurrentBattleArea->enemyBattlePawns[0];
			}
		
	}
	else
	{
		if (CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastFreindlyTarget == NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("selcet ally 1"));
			ABattlePawnBase* target = NULL;
			for (int i = 0; i < CurrentBattleArea->playerBattlePawns.Num();i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("selcet ally 2"));
				float higestHealth = 1000000000000;
				if (activeAbility->isHealing == true)
				{
					if (CurrentBattleArea->playerBattlePawns[i]->mainCharInfo.Health < higestHealth)
					{
						higestHealth = CurrentBattleArea->playerBattlePawns[i]->mainCharInfo.Health;
						target = CurrentBattleArea->playerBattlePawns[i];
					}

				}else if (CurrentBattleArea->playerBattlePawns[i]->bIsBackLine != true)
				{
					//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 4"));
					return target = CurrentBattleArea->playerBattlePawns[i];
				}

			}if (target == NULL)
			{
				//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 5"));
				target = CurrentBattleArea->playerBattlePawns[0];
			}
			return target;
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 6"));
			return CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastFreindlyTarget;
		}

	}





	return NULL;
}

ABattlePawnBase* ADungeonControllerBase::SearchValidBackline(TArray<UBattleSpawnPoint*>inSpawnPointsToUse)
{
	int q = 0;
	int newPlaceOnGrid = 0;
	UE_LOG(LogTemp, Warning, TEXT("SearchValidBackline 1"));
	for (int u = 4; u < inSpawnPointsToUse.Num();u++)
	{
		q++;
		UE_LOG(LogTemp, Warning, TEXT("SearchValidBackline 2"));
		newPlaceOnGrid = singleTarget->PawnsBaseActor->placeOnGrid + u;
		if (newPlaceOnGrid > 8)
		{
			UE_LOG(LogTemp, Warning, TEXT("SearchValidBackline 3"));
			newPlaceOnGrid = 4;
			u = 1;
		}
		if (inSpawnPointsToUse[newPlaceOnGrid - 1]->myPawn != NULL && inSpawnPointsToUse[newPlaceOnGrid - 1]->myPawn->isDown != true)
		{
			UE_LOG(LogTemp, Warning, TEXT("SearchValidBackline 4"));
			return inSpawnPointsToUse[newPlaceOnGrid - 1]->myPawn;
			
		}
		if (q > 8)
		{
			return NULL;
		}
	}
	return singleTarget;
}

ABattlePawnBase* ADungeonControllerBase::SearchValidFrontline(TArray<UBattleSpawnPoint*>inSpawnPointsToUse)
{
	int q = 0;
	int newPlaceOnGrid = 0;
	UE_LOG(LogTemp, Warning, TEXT("SearchValidFrontline  1"));

	if (singleTarget->bIsBackLine)
	{
		newPlaceOnGrid = singleTarget->PawnsBaseActor->placeOnGrid - 4;
	}
	else
	{
		newPlaceOnGrid = singleTarget->PawnsBaseActor->placeOnGrid;
	}


	for (int u = 0; u < 4;u++)
	{
		q++;
		UE_LOG(LogTemp, Warning, TEXT("SearchValidFrontline  2"));
		newPlaceOnGrid ++;
		if (newPlaceOnGrid > 4)
		{
			UE_LOG(LogTemp, Warning, TEXT("SearchValidFrontline  3"));
			newPlaceOnGrid = 1;
			u = 0;
		}
		if (newPlaceOnGrid < 1)
		{
			newPlaceOnGrid = 1;
		}
		if (inSpawnPointsToUse[newPlaceOnGrid - 1]->myPawn != NULL && inSpawnPointsToUse[newPlaceOnGrid - 1]->myPawn->isDown != true)
		{
			UE_LOG(LogTemp, Warning, TEXT("SearchValidFrontline  4"));
			return inSpawnPointsToUse[newPlaceOnGrid - 1]->myPawn;
		
		}
		if (q > 8)
		{
			return NULL;
		}
	}

	return singleTarget;
}

void ADungeonControllerBase::ToggleSwitchTimer()
{
	switchTimerReady = true;
}

void ADungeonControllerBase::ConfirmSingleTarget()
{
	//UE_LOG(LogTemp, Warning, TEXT("ConfirmSingleTarget 1"));
	if (singleTarget != NULL)
	{
		CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget = singleTarget;
		UE_LOG(LogTemp, Warning, TEXT("ConfirmSingleTarget 2"));
		CurrentBattleArea->BattleBrain->confirmedSingleTarget = singleTarget;
		CurrentBattleArea->BattleBrain->watingForPlayersTarget = false;
		isWaitingForSingleTargetSelection = false;
		isWatingForSmallAOESelection = false;
		isWaitingForMedAoeSelection = false;
		isWaitingForPartyAOESelection = false;
		skillSelected = false;
		BattleHUD->selectingTargets = false;
		lookingForHostile = false;
		hasSetLastTarget = false;
		CurrentBattleArea->BattleBrain->activeAbility = activeAbility;
		activeAbility = NULL;
		BattleHUD->BackToAttackSelection();
		SetViewTarget(CurrentBattleArea);
		
	}
}


/////////battle mode //////////
void ADungeonControllerBase::BeginBattle(ABattleZoneBase* InBattleZone)
{
	bIsInBattleMode = true;
	CurrentBattleArea = InBattleZone;
	InBattleZone->InitializeBattle(this);

	ToggleDungeonHUD(false);
	BattleHUDSpawn();
	BattleHUD->CalcTurnsHUD();
	InBattleZone->BattleBrain->isLoaded = true;

}

void ADungeonControllerBase::EndBattle()
{
	SetViewTarget(MyChar);
	bIsInBattleMode = false;
	MyChar->CurrentEncountreVolume->BattleEndTimerReset();
	//BattleHUDDespawn();
	BattleHUDENDDeSpawn();
	ToggleDungeonHUD(true);

}
