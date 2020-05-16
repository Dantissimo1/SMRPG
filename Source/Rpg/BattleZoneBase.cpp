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
#include "CharacterDataSheet.h"


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
	camOriginalTrans = TestCam1->GetRelativeTransform();

	BattleBrain = CreateDefaultSubobject<UBattleBrainComponent>(TEXT("Battle Brain"));
	BattleBrain->SetUp(this);
	//////create Spawn points///////
	
	spawnPoint1 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 1"));
	spawnPoint1->SetupAttachment(RootComponent);
	spawnPoint1->placeOnGrid = 1;
	PlayerBattleSpawns.Add(spawnPoint1);
	spawnPoint2 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 2"));
	spawnPoint2->SetupAttachment(RootComponent);
	spawnPoint2->placeOnGrid = 2;
	PlayerBattleSpawns.Add(spawnPoint2);
	spawnPoint3 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 3"));
	spawnPoint3->SetupAttachment(RootComponent);
	spawnPoint3->placeOnGrid = 3;
	PlayerBattleSpawns.Add(spawnPoint3);
	spawnPoint4 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 4"));
	spawnPoint4->SetupAttachment(RootComponent);
	spawnPoint4->placeOnGrid = 4;
	PlayerBattleSpawns.Add(spawnPoint4);
	spawnPoint5 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 5"));
	spawnPoint5->SetupAttachment(RootComponent);
	spawnPoint5->placeOnGrid = 5;
	PlayerBattleSpawns.Add(spawnPoint5);
	spawnPoint6 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 6"));
	spawnPoint6->SetupAttachment(RootComponent);
	spawnPoint6->placeOnGrid = 6;
	PlayerBattleSpawns.Add(spawnPoint6);
	spawnPoint7 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 7"));
	spawnPoint7->SetupAttachment(RootComponent);
	spawnPoint7->placeOnGrid = 7;
	PlayerBattleSpawns.Add(spawnPoint7);
	spawnPoint8 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Spawn 8"));
	spawnPoint8->SetupAttachment(RootComponent);
	spawnPoint8->placeOnGrid = 8;
	PlayerBattleSpawns.Add(spawnPoint8);



	EnemySpawnPoint1 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 1"));
	EnemySpawnPoint1->SetupAttachment(RootComponent);
	EnemySpawnPoint1->placeOnGrid = 1;
	EnemyBattleSpawns.Add(EnemySpawnPoint1);
	EnemySpawnPoint2 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 2"));
	EnemySpawnPoint2->SetupAttachment(RootComponent);
	EnemySpawnPoint2->placeOnGrid = 2;
	EnemyBattleSpawns.Add(EnemySpawnPoint2);
	EnemySpawnPoint3 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 3"));
	EnemySpawnPoint3->SetupAttachment(RootComponent);
	EnemySpawnPoint3->placeOnGrid = 3;
	EnemyBattleSpawns.Add(EnemySpawnPoint3);
	EnemySpawnPoint4 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 4"));
	EnemySpawnPoint4->SetupAttachment(RootComponent);
	EnemySpawnPoint4->placeOnGrid = 4;
	EnemyBattleSpawns.Add(EnemySpawnPoint4);
	EnemySpawnPoint5 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 5"));
	EnemySpawnPoint5->SetupAttachment(RootComponent);
	EnemySpawnPoint5->placeOnGrid = 5;
	EnemyBattleSpawns.Add(EnemySpawnPoint5);
	EnemySpawnPoint6 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 6"));
	EnemySpawnPoint6->SetupAttachment(RootComponent);
	EnemySpawnPoint6->placeOnGrid = 6;
	EnemyBattleSpawns.Add(EnemySpawnPoint6);
	EnemySpawnPoint7 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 7"));
	EnemySpawnPoint7->SetupAttachment(RootComponent);
	EnemySpawnPoint7->placeOnGrid = 7;
	EnemyBattleSpawns.Add(EnemySpawnPoint7);
	EnemySpawnPoint8 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("Enemy Spawn 8"));
	EnemySpawnPoint8->SetupAttachment(RootComponent);
	EnemySpawnPoint8->placeOnGrid = 8;
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
	BattleBrain->PlayersCont = InPlayerCont;
	SpawnPlayersParty();
	SpanEnemyParty();
	BattleBrain->InitializeBattle(allBattlePawns, playerBattlePawns,enemyBattlePawns);
	
	
	
	
	
	
	//GetWorldTimerManager().SetTimer(TestTimer, this, &ABattleZoneBase::EndBattle, 120.0f, false);

}

void ABattleZoneBase::SpawnPlayersParty()
{
	
	for (int i = 0; i < PlayerCont->PlayersParty->PartyFormationFrontLine.Num() ;i++)
	{
		//////////////UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn"));
		
		if (PlayerCont->PlayersParty->PartyFormationFrontLine[i] != NULL)
		{
			//////////////UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn  != NBULLLLL"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = PlayerCont;

			ACharacterDataSheet* ElementInDataSheet = Cast<ACharacterDataSheet>(PlayerCont->PlayersParty->PartyFormationFrontLine[i]);
			//////////////UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn,%s"), *ElementInDataSheet->GetFName().ToString());

			if (ElementInDataSheet->CharacterDetails.BattlePawnToUse)
			{
				//////////////UE_LOG(LogTemp, Warning, TEXT("BattlePawn,%s"), *ElementInDataSheet->GetFName().ToString());
			}
			ABattlePawnBase* ClassToSpawn = PlayerCont->PlayersParty->PartyFormationFrontLine[i]->CharacterDetails.CharactersBattleBlueprint;
			FVector SpawnLoc = PlayerBattleSpawns[i]->GetComponentLocation();
			SpawnLoc.Z += ElementInDataSheet->CharacterDetails.BattlePawnToUse.GetDefaultObject()->heightOffset;
			ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(ElementInDataSheet->CharacterDetails.BattlePawnToUse, SpawnLoc, FRotator(0.f, -0.0f, 0.f), SpawnParams);
			if (SpawnedPawn != NULL)
			{
				PlayerBattleSpawns[i]->myPawn = SpawnedPawn;
				SpawnedPawn->SetUpPlayerPawn(ElementInDataSheet, PlayerBattleSpawns[i], this, false, true);
				allBattlePawns.Add(SpawnedPawn);
				playerBattlePawns.Add(SpawnedPawn);
				SpawnedPawn->InitializeEquipedItems();
			}
		}	
	}
	
	for (int i = 0; i < PlayerCont->PlayersParty->PartyFormationBackLine.Num() ;i++)
	{
		//////////////UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn BackLine"));
		
		if (PlayerCont->PlayersParty->PartyFormationBackLine[i] != NULL)
		{
			//////////////UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn  BackLine != NBULLLLL"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = PlayerCont;

			ACharacterDataSheet* ElementInDataSheet = Cast<ACharacterDataSheet>(PlayerCont->PlayersParty->PartyFormationBackLine[i]);
			//////////////UE_LOG(LogTemp, Warning, TEXT("looooooop BackLine Spawnnn,%s"), *ElementInDataSheet->GetFName().ToString());

			if (ElementInDataSheet->CharacterDetails.BattlePawnToUse)
			{
				//////////////UE_LOG(LogTemp, Warning, TEXT("BattlePawn  BackLine ,%s"), *ElementInDataSheet->GetFName().ToString());
			}
			ABattlePawnBase* ClassToSpawn = PlayerCont->PlayersParty->PartyFormationBackLine[i]->CharacterDetails.CharactersBattleBlueprint;
			FVector SpawnLoc = PlayerBattleSpawns[4 + i]->GetComponentLocation();
			SpawnLoc.Z += ElementInDataSheet->CharacterDetails.BattlePawnToUse.GetDefaultObject()->heightOffset;
			ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(ElementInDataSheet->CharacterDetails.BattlePawnToUse, SpawnLoc, FRotator(0.f, -0.0f, 0.f), SpawnParams);
			if (SpawnedPawn != NULL)
			{
				//////////////UE_LOG(LogTemp, Warning, TEXT("Back Spawned"));
				SpawnedPawn->SetUpPlayerPawn(ElementInDataSheet, PlayerBattleSpawns[4 +i], this, true, true);
				PlayerBattleSpawns[4 + i]->myPawn = SpawnedPawn;
				allBattlePawns.Add(SpawnedPawn);
				playerBattlePawns.Add(SpawnedPawn);
				SpawnedPawn->InitializeEquipedItems();
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
		//////////////UE_LOG(LogTemp, Warning, TEXT("Formation no =,%d"),rand);
		enemyPartyFormation = GetWorld()->SpawnActor<AEnemyPartyFormationCompnent>(PartyList->ListOfFormations[RandNo-1], FVector(0.f, 0.f, 0.f), FRotator(0.f, .0f, 0.f), SpawnParams);

		for (int i = 0; i < enemyPartyFormation->PartyFormationFrontLineSub.Num();i++)
		{
			//////////////UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn"));

			if (enemyPartyFormation->PartyFormationFrontLineSub[i] != NULL)
			{
				//////////////UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn  != NBULLLLL"));

				if (enemyPartyFormation->PartyFormationFrontLineSub[i])
				{
					//////////////UE_LOG(LogTemp, Warning, TEXT("BattlePawn,%s"), *enemyPartyFormation->PartyFormationFrontLineSub[i]->GetFName().ToString());
				}
				FVector SpawnLoc = EnemyBattleSpawns[i]->GetComponentLocation();
				SpawnLoc.Z += enemyPartyFormation->PartyFormationFrontLineSub[i].GetDefaultObject()->heightOffset;
				ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(enemyPartyFormation->PartyFormationFrontLineSub[i], SpawnLoc, FRotator(0.f, 180.0f, 0.f), SpawnParams);
				if (SpawnedPawn != NULL)
				{
					//////////////UE_LOG(LogTemp, Warning, TEXT("Back Spawned"));
					SpawnedPawn->MyBattleZone = this;
					SpawnedPawn->PawnsBaseActor = EnemyBattleSpawns[i];
					SpawnedPawn->isOwnedByPlayer = false;
					SpawnedPawn->bIsBackLine = false;
					EnemyBattleSpawns[i]->myPawn = SpawnedPawn;
					SpawnedPawn->SetUpNPCPawn();
					allBattlePawns.Add(SpawnedPawn);
					enemyBattlePawns.Add(SpawnedPawn);
					SpawnedPawn->InitializeEquipedItems();
				}
			}
		}
		for (int i = 0; i < enemyPartyFormation->PartyFormationBackLineSub.Num();i++)
		{
			//////////////UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn"));

			if (enemyPartyFormation->PartyFormationBackLineSub[i] != NULL)
			{
				//////////////UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn  != NBULLLLL"));

				if (enemyPartyFormation->PartyFormationBackLineSub[i])
				{
					//////////////UE_LOG(LogTemp, Warning, TEXT("BattlePawn,%s"), *enemyPartyFormation->PartyFormationBackLineSub[i]->GetFName().ToString());
				}
				FVector SpawnLoc = EnemyBattleSpawns[4 + i]->GetComponentLocation();
				SpawnLoc.Z += enemyPartyFormation->PartyFormationBackLineSub[i].GetDefaultObject()->heightOffset;
				ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(enemyPartyFormation->PartyFormationBackLineSub[i], SpawnLoc, FRotator(0.f, 180.0f, 0.f), SpawnParams);
				if (SpawnedPawn != NULL)
				{
					//////////////UE_LOG(LogTemp, Warning, TEXT("Back Spawned"));
					SpawnedPawn->MyBattleZone = this;
					SpawnedPawn->PawnsBaseActor = EnemyBattleSpawns[4 + i];
					SpawnedPawn->isOwnedByPlayer = false;
					SpawnedPawn->bIsBackLine = true;
					EnemyBattleSpawns[4 + i]->myPawn = SpawnedPawn;
					SpawnedPawn->SetUpNPCPawn();
					allBattlePawns.Add(SpawnedPawn);
					enemyBattlePawns.Add(SpawnedPawn);
					SpawnedPawn->InitializeEquipedItems();
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