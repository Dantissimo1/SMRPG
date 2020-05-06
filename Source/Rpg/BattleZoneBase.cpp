// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleZoneBase.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "DungeonControllerBase.h"
#include "BattleSpawnPoint.h"
#include "PlayerPartyComponent.h"
#include "BattlePawnBase.h"
#include "DungeonControllerBase.h"
#include "CharacterDataSheet.h"
#include "EnemyPartyFormationCompnent.h"
#include "EnemyPartyFormationList.h"
#include "BattleBrainComponent.h"
#include "AttackPosition.h"
#include "OpotunityAttackPosition.h"



// Sets default values
ABattleZoneBase::ABattleZoneBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	RootComponent = BoxComp;
	//EnemyPartyFormation = CreateDefaultSubobject<ABattlePawnBase>(TEXT("Enemy Party Formation"));
	
	TestCam1 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1"));
	TestCam1->SetupAttachment(RootComponent);

	BattleBrain = CreateDefaultSubobject<UBattleBrainComponent>(TEXT("Battle Brain"));
	BattleBrain->SetUp(this);
	//////create Spawn points///////

	spawnPoint1 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 1"));
	spawnPoint1->SetupAttachment(RootComponent);
	PlayerBattleSpawns.Add(spawnPoint1);
	spawnPoint2 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 2"));
	spawnPoint2->SetupAttachment(RootComponent);
	PlayerBattleSpawns.Add(spawnPoint2);
	spawnPoint3 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 3"));
	spawnPoint3->SetupAttachment(RootComponent);
	PlayerBattleSpawns.Add(spawnPoint3);
	spawnPoint4 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 4"));
	spawnPoint4->SetupAttachment(RootComponent);
	PlayerBattleSpawns.Add(spawnPoint4);
	spawnPoint5 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 5"));
	spawnPoint5->SetupAttachment(RootComponent);
	PlayerBattleSpawns.Add(spawnPoint5);
	spawnPoint6 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 6"));
	spawnPoint6->SetupAttachment(RootComponent);
	PlayerBattleSpawns.Add(spawnPoint6);
	spawnPoint7 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 7"));
	spawnPoint7->SetupAttachment(RootComponent);
	PlayerBattleSpawns.Add(spawnPoint7);
	spawnPoint8 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 8"));
	spawnPoint8->SetupAttachment(RootComponent);
	PlayerBattleSpawns.Add(spawnPoint8);



	EnemySpawnPoint1 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 1"));
	EnemySpawnPoint1->SetupAttachment(RootComponent);
	EnemyBattleSpawns.Add(EnemySpawnPoint1);
	EnemySpawnPoint2 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 2"));
	EnemySpawnPoint2->SetupAttachment(RootComponent);
	EnemyBattleSpawns.Add(EnemySpawnPoint2);
	EnemySpawnPoint3 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 3"));
	EnemySpawnPoint3->SetupAttachment(RootComponent);
	EnemyBattleSpawns.Add(EnemySpawnPoint3);
	EnemySpawnPoint4 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 4"));
	EnemySpawnPoint4->SetupAttachment(RootComponent);
	EnemyBattleSpawns.Add(EnemySpawnPoint4);
	EnemySpawnPoint5 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 5"));
	EnemySpawnPoint5->SetupAttachment(RootComponent);
	EnemyBattleSpawns.Add(EnemySpawnPoint5);
	EnemySpawnPoint6 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 6"));
	EnemySpawnPoint6->SetupAttachment(RootComponent);
	EnemyBattleSpawns.Add(EnemySpawnPoint6);
	EnemySpawnPoint7 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 7"));
	EnemySpawnPoint7->SetupAttachment(RootComponent);
	EnemyBattleSpawns.Add(EnemySpawnPoint7);
	EnemySpawnPoint8 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 8"));
	EnemySpawnPoint8->SetupAttachment(RootComponent);
	EnemyBattleSpawns.Add(EnemySpawnPoint8);

	

}


// Called when the game starts or when spawned
void ABattleZoneBase::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABattleZoneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABattleZoneBase::InitializeBattle(ADungeonControllerBase* InPlayerCont)
{
	PlayerCont = InPlayerCont;
	PlayerCont->SetViewTarget(this);
	
	SpawnPlayersParty();
	SpanEnemyParty();
	BattleBrain->InitializeBattle(allBattlePawns, playerBattlePawns,enemyBattlePawns);
	
	
	
	
	
	
	GetWorldTimerManager().SetTimer(TestTimer, this, &ABattleZoneBase::EndBattle, 20.0f, false);

}

void ABattleZoneBase::SpawnPlayersParty()
{
	
	for (int i = 0; i < PlayerCont->PlayersParty->PartyFormationFrontLine.Num() ;i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn"));
		
		if (PlayerCont->PlayersParty->PartyFormationFrontLine[i] != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn  != NBULLLLL"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = PlayerCont;

			ACharacterDataSheet* ElementInDataSheet = Cast<ACharacterDataSheet>(PlayerCont->PlayersParty->PartyFormationFrontLine[i]);
			UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn,%s"), *ElementInDataSheet->GetFName().ToString());

			if (ElementInDataSheet->BattlePawnToUse)
			{
				UE_LOG(LogTemp, Warning, TEXT("BattlePawn,%s"), *ElementInDataSheet->GetFName().ToString());
			}
			ABattlePawnBase* ClassToSpawn = PlayerCont->PlayersParty->PartyFormationFrontLine[i]->CharactersBattleBlueprint;
			FVector SpawnLoc = PlayerBattleSpawns[i]->GetComponentLocation();
			SpawnLoc.Z += ElementInDataSheet->BattlePawnToUse.GetDefaultObject()->heightOffset;
			ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(ElementInDataSheet->BattlePawnToUse, SpawnLoc, FRotator(0.f, -0.0f, 0.f), SpawnParams);
			if (SpawnedPawn != NULL)
			{
				SpawnedPawn->MyBattleZone = this;
				SpawnedPawn->isOwnedByPlayer = true;
				SpawnedPawn->PawnsBaseActor = PlayerBattleSpawns[i];
				allBattlePawns.Add(SpawnedPawn);
				playerBattlePawns.Add(SpawnedPawn);
			}
		}	
	}
	
	for (int i = 0; i < PlayerCont->PlayersParty->PartyFormationBackLine.Num() ;i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn BackLine"));
		
		if (PlayerCont->PlayersParty->PartyFormationBackLine[i] != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn  BackLine != NBULLLLL"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = PlayerCont;

			ACharacterDataSheet* ElementInDataSheet = Cast<ACharacterDataSheet>(PlayerCont->PlayersParty->PartyFormationBackLine[i]);
			UE_LOG(LogTemp, Warning, TEXT("looooooop BackLine Spawnnn,%s"), *ElementInDataSheet->GetFName().ToString());

			if (ElementInDataSheet->BattlePawnToUse)
			{
				UE_LOG(LogTemp, Warning, TEXT("BattlePawn  BackLine ,%s"), *ElementInDataSheet->GetFName().ToString());
			}
			ABattlePawnBase* ClassToSpawn = PlayerCont->PlayersParty->PartyFormationBackLine[i]->CharactersBattleBlueprint;
			FVector SpawnLoc = PlayerBattleSpawns[4 + i]->GetComponentLocation();
			SpawnLoc.Z += ElementInDataSheet->BattlePawnToUse.GetDefaultObject()->heightOffset;
			ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(ElementInDataSheet->BattlePawnToUse, SpawnLoc, FRotator(0.f, -0.0f, 0.f), SpawnParams);
			if (SpawnedPawn != NULL)
			{
				UE_LOG(LogTemp, Warning, TEXT("Back Spawned"));
				SpawnedPawn->PawnsBaseActor = PlayerBattleSpawns[4 + i];
				SpawnedPawn->isOwnedByPlayer = true;
				SpawnedPawn->bIsBackLine = true;
				allBattlePawns.Add(SpawnedPawn);
				playerBattlePawns.Add(SpawnedPawn);
			}
		}	
	}
}

void ABattleZoneBase::SpanEnemyParty()
{
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	AEnemyPartyFormationList* PartyList = GetWorld()->SpawnActor<AEnemyPartyFormationList>(EnemyPartyFormationList, FVector(0.f, 0.f, 0.f), FRotator(0.f, .0f, 0.f), SpawnParams);

	int PartyListLenght = PartyList->ListOfFormations.Num();
	int RandNo = 0;
	if (PartyListLenght != 0)
	{
		RandNo = FMath::RoundToInt(FMath::FRandRange(1.f, PartyListLenght));
		UE_LOG(LogTemp, Warning, TEXT("Formation no =,%d"),rand);
		enemyPartyFormation = GetWorld()->SpawnActor<AEnemyPartyFormationCompnent>(PartyList->ListOfFormations[RandNo-1], FVector(0.f, 0.f, 0.f), FRotator(0.f, .0f, 0.f), SpawnParams);

		for (int i = 0; i < enemyPartyFormation->PartyFormationFrontLineSub.Num();i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn"));

			if (enemyPartyFormation->PartyFormationFrontLineSub[i] != NULL)
			{
				UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn  != NBULLLLL"));

				if (enemyPartyFormation->PartyFormationFrontLineSub[i])
				{
					UE_LOG(LogTemp, Warning, TEXT("BattlePawn,%s"), *enemyPartyFormation->PartyFormationFrontLineSub[i]->GetFName().ToString());
				}
				FVector SpawnLoc = EnemyBattleSpawns[i]->GetComponentLocation();
				SpawnLoc.Z += enemyPartyFormation->PartyFormationFrontLineSub[i].GetDefaultObject()->heightOffset;
				ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(enemyPartyFormation->PartyFormationFrontLineSub[i], SpawnLoc, FRotator(0.f, 180.0f, 0.f), SpawnParams);
				if (SpawnedPawn != NULL)
				{
					UE_LOG(LogTemp, Warning, TEXT("Back Spawned"));
					SpawnedPawn->PawnsBaseActor = EnemyBattleSpawns[i];
					SpawnedPawn->isOwnedByPlayer = false;
					SpawnedPawn->bIsBackLine = false;
					allBattlePawns.Add(SpawnedPawn);
					enemyBattlePawns.Add(SpawnedPawn);
				}
			}
		}
		for (int i = 0; i < enemyPartyFormation->PartyFormationBackLineSub.Num();i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn"));

			if (enemyPartyFormation->PartyFormationBackLineSub[i] != NULL)
			{
				UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn  != NBULLLLL"));

				if (enemyPartyFormation->PartyFormationBackLineSub[i])
				{
					UE_LOG(LogTemp, Warning, TEXT("BattlePawn,%s"), *enemyPartyFormation->PartyFormationBackLineSub[i]->GetFName().ToString());
				}
				FVector SpawnLoc = EnemyBattleSpawns[4 + i]->GetComponentLocation();
				SpawnLoc.Z += enemyPartyFormation->PartyFormationBackLineSub[i].GetDefaultObject()->heightOffset;
				ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(enemyPartyFormation->PartyFormationBackLineSub[i], SpawnLoc, FRotator(0.f, 180.0f, 0.f), SpawnParams);
				if (SpawnedPawn != NULL)
				{
					UE_LOG(LogTemp, Warning, TEXT("Back Spawned"));
					SpawnedPawn->PawnsBaseActor = EnemyBattleSpawns[4 + i];
					SpawnedPawn->isOwnedByPlayer = false;
					SpawnedPawn->bIsBackLine = true;
					allBattlePawns.Add(SpawnedPawn);
					enemyBattlePawns.Add(SpawnedPawn);
				}
			}
		}
	}
	
}

void ABattleZoneBase::DeleteBattlePawns()
{
	for (int i = 0; i < allBattlePawns.Num();i++)
	{
		if (allBattlePawns[i] != NULL)
		{
			if (allBattlePawns[i]->IsPendingKill() != true)////BUG CRASH
			{
				allBattlePawns[i]->Destroy();
			}
		}

	}
	allBattlePawns.Empty();
}



void ABattleZoneBase::EndBattle()
{
	////de spawn remaning pawns
	DeleteBattlePawns();
	BattleBrain->EndBattle();
	PlayerCont->EndBattle();
}