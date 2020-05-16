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

	if (isWaitingForSingleTargetSelection)
	{
		if (lookingForHostile)
		{
			if (hasSetLastTarget == false && CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget && CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget->isDown != true)
			{
				//UE_LOG(LogTemp, Warning, TEXT("wating set singel to last 0"));
				singleTarget = CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget;
				SetViewTargetWithBlend(singleTarget, 0.3f);
				hasSetLastTarget = true;
			}
			if (singleTarget == NULL)
			{
				//UE_LOG(LogTemp, Warning, TEXT("single targe t null"));
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
			BattleHUD->BackToAttackSelection();
			isWaitingForSingleTargetSelection = false;
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

void ADungeonControllerBase::SelectSingleHorizontal(float value)
{
	
	if (switchTimerReady == true)
	{
		GetWorldTimerManager().SetTimer(tSwitchTimerHandle, this, &ADungeonControllerBase::ToggleSwitchTimer, 0.5f, false);
		switchTimerReady = false;
		//UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 1"));
		if (lookingForHostile)
		{
			int rowMin = 1;
			int rowMax = 4;
			if (singleTarget->bIsBackLine == true)
			{
				rowMin = 5;
				rowMax = 8;
			}

			//UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 4"));
			int newPlaceOnGrid = 0;
			if (value > 0)
			{
				newPlaceOnGrid = singleTarget->PawnsBaseActor->placeOnGrid;
				//UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 5 %d"), newPlaceOnGrid);

				bool HasBeenPlacedOnRow = false;
				for (int y = 1;y < 5;y++)
				{
					if (singleTarget->bIsBackLine == true)
					{
						rowMin = 5;
						rowMax = 8;
					}
					newPlaceOnGrid += y;
					if (newPlaceOnGrid > rowMax)
					{
						//UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 6.1 %d"), newPlaceOnGrid);
						newPlaceOnGrid = rowMin;
						//UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 6.2 "));
						y = 1;
					}
					if (CurrentBattleArea->EnemyBattleSpawns[newPlaceOnGrid - 1]->myPawn != NULL && CurrentBattleArea->EnemyBattleSpawns[newPlaceOnGrid - 1]->myPawn != singleTarget)
					{
						//UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 7 %d"), newPlaceOnGrid);
						singleTarget = CurrentBattleArea->EnemyBattleSpawns[newPlaceOnGrid - 1]->myPawn;
						SetViewTargetWithBlend(singleTarget, .3f);
						HasBeenPlacedOnRow = true;
						return;
					}
				}
			}
			if (value < 0)
			{
				newPlaceOnGrid = singleTarget->PawnsBaseActor->placeOnGrid;
				//UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 5 %d"), newPlaceOnGrid);

				bool HasBeenPlacedOnRow = false;
				for (int y = 1;y < 5;y++)
				{
					if (singleTarget->bIsBackLine == true)
					{
						rowMin = 5;
						rowMax = 8;
					}
					newPlaceOnGrid -= y;
					if (newPlaceOnGrid < rowMin)
					{
						//UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 6 %d"), newPlaceOnGrid);
						newPlaceOnGrid = rowMax;
						y = 1;
					}

					if (CurrentBattleArea->EnemyBattleSpawns[newPlaceOnGrid - 1]->myPawn != NULL && CurrentBattleArea->EnemyBattleSpawns[newPlaceOnGrid - 1]->myPawn != singleTarget)
					{
						//UE_LOG(LogTemp, Warning, TEXT("SelectSingleHorizontal 7 %d"), newPlaceOnGrid);
						singleTarget = CurrentBattleArea->EnemyBattleSpawns[newPlaceOnGrid - 1]->myPawn;
						SetViewTargetWithBlend(singleTarget, .3f);
						HasBeenPlacedOnRow = true;
						return;
					}
				}
			}
		}
	}
}

void ADungeonControllerBase::SelectSingleVertical(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("SelectSingleVertical 1"));
	if (lookingForHostile)
	{
		if (switchTimerReady == true)
		{
			GetWorldTimerManager().SetTimer(tSwitchTimerHandle, this, &ADungeonControllerBase::ToggleSwitchTimer, 0.5f, false);
			switchTimerReady = false;
			int newPlaceOnGrid = 0;
			if (singleTarget->bIsBackLine != true)
			{
				for (int u = 4; u < CurrentBattleArea->EnemyBattleSpawns.Num();u++)
				{
					newPlaceOnGrid = singleTarget->PawnsBaseActor->placeOnGrid + u;

					if (CurrentBattleArea->EnemyBattleSpawns[newPlaceOnGrid - 1]->myPawn != NULL)
					{
						break;
					}
				}
			}
			else
			{
				for (int u = 4; u < 8;u++)
				{
					newPlaceOnGrid = singleTarget->PawnsBaseActor->placeOnGrid - u;

					if (CurrentBattleArea->EnemyBattleSpawns[newPlaceOnGrid - 1]->myPawn != NULL)
					{
						break;
					}
				}
			}




			singleTarget = CurrentBattleArea->EnemyBattleSpawns[newPlaceOnGrid - 1]->myPawn;
			SetViewTargetWithBlend(singleTarget, .3f);
		}

	}


}

ABattlePawnBase* ADungeonControllerBase::SelectFirstHostileTarget()
{
	//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 1"));
	if (CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget == NULL)
	{
		//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 2"));
		ABattlePawnBase* target = NULL;
		for (int i = 0; i < CurrentBattleArea->enemyBattlePawns.Num();i++)
		{
			//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 3"));
			if (CurrentBattleArea->enemyBattlePawns[i]->bIsBackLine != true)
			{
				//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 4"));
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
		//UE_LOG(LogTemp, Warning, TEXT("SelectFirstHostileTarget 6"));
		return CurrentBattleArea->BattleBrain->ActiveTurn->MyBattlePawn->lastAttackTarget;
	}
	return NULL;
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
		//UE_LOG(LogTemp, Warning, TEXT("ConfirmSingleTarget 2"));
		CurrentBattleArea->BattleBrain->confirmedSingleTarget = singleTarget;
		CurrentBattleArea->BattleBrain->watingForPlayersTarget = false;
		isWaitingForSingleTargetSelection = false;
		SetViewTarget(CurrentBattleArea);
		hasSetLastTarget = false;
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
	BattleHUDDespawn();
	ToggleDungeonHUD(true);

}
