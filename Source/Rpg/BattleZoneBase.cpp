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

	//////create Spawn points///////

	///create player ftonline spawnpoints 
	PlayersFrontLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("PlayerSpawn1")));
	PlayersFrontLineSpawnPoints[0]->SetupAttachment(RootComponent);
	PlayersFrontLineSpawnPoints[0]->SetRelativeLocation(FVector(-500, -400, 1));
	PlayersFrontLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("PlayerSpawn2")));
	PlayersFrontLineSpawnPoints[1]->SetupAttachment(RootComponent);
	PlayersFrontLineSpawnPoints[1]->SetRelativeLocation(FVector(-200, -400, 1));
	PlayersFrontLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("PlayerSpawn3")));
	PlayersFrontLineSpawnPoints[2]->SetupAttachment(RootComponent);
	PlayersFrontLineSpawnPoints[2]->SetRelativeLocation(FVector(100, -400, 1));
	PlayersFrontLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("PlayerSpawn4")));
	PlayersFrontLineSpawnPoints[3]->SetupAttachment(RootComponent);
	PlayersFrontLineSpawnPoints[3]->SetRelativeLocation(FVector(400, -400, 1));
	//create players back line spawn points
	PlayersBackLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("PlayerSpawn5")));
	PlayersBackLineSpawnPoints[0]->SetupAttachment(RootComponent);
	PlayersBackLineSpawnPoints[0]->SetRelativeLocation(FVector(-350, -659, 1));
	PlayersBackLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("PlayerSpawn6")));
	PlayersBackLineSpawnPoints[1]->SetupAttachment(RootComponent);
	PlayersBackLineSpawnPoints[1]->SetRelativeLocation(FVector(-50, -659, 1));
	PlayersBackLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("PlayerSpawn7")));
	PlayersBackLineSpawnPoints[2]->SetupAttachment(RootComponent);
	PlayersBackLineSpawnPoints[2]->SetRelativeLocation(FVector(250, -659, 1));
	PlayersBackLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("PlayerSpawn8")));
	PlayersBackLineSpawnPoints[3]->SetupAttachment(RootComponent);
	PlayersBackLineSpawnPoints[3]->SetRelativeLocation(FVector(550, -659, 1));


	//create enemy swapn comps
	///create Enemy ftonline spawnpoints 
	EnemyFrontLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn1")));
	EnemyFrontLineSpawnPoints[0]->SetupAttachment(RootComponent);
	EnemyFrontLineSpawnPoints[0]->SetRelativeLocation(FVector(-350, 400, 1));
	EnemyFrontLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn2")));
	EnemyFrontLineSpawnPoints[1]->SetupAttachment(RootComponent);
	EnemyFrontLineSpawnPoints[1]->SetRelativeLocation(FVector(-50, 400, 1));
	EnemyFrontLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn3")));
	EnemyFrontLineSpawnPoints[2]->SetupAttachment(RootComponent);
	EnemyFrontLineSpawnPoints[2]->SetRelativeLocation(FVector(250, 400, 1));
	EnemyFrontLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn4")));
	EnemyFrontLineSpawnPoints[3]->SetupAttachment(RootComponent);
	EnemyFrontLineSpawnPoints[3]->SetRelativeLocation(FVector(550, 400, 1));
	//create players back line spawn points
	EnemyBackLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn5")));
	EnemyBackLineSpawnPoints[0]->SetupAttachment(RootComponent);
	EnemyBackLineSpawnPoints[0]->SetRelativeLocation(FVector(-500, 659, 1));
	EnemyBackLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn6")));
	EnemyBackLineSpawnPoints[1]->SetupAttachment(RootComponent);
	EnemyBackLineSpawnPoints[1]->SetRelativeLocation(FVector(-200, 659, 1));
	EnemyBackLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn7")));
	EnemyBackLineSpawnPoints[2]->SetupAttachment(RootComponent);
	EnemyBackLineSpawnPoints[2]->SetRelativeLocation(FVector(100, 659, 1));
	EnemyBackLineSpawnPoints.Add(CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn8")));
	EnemyBackLineSpawnPoints[3]->SetupAttachment(RootComponent);
	EnemyBackLineSpawnPoints[3]->SetRelativeLocation(FVector(400, 659, 1));




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
	
	
	
	
	
	
	
	GetWorldTimerManager().SetTimer(TestTimer, this, &ABattleZoneBase::EndBattle, 3.0f, true);

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
			FVector SpawnLoc = PlayersFrontLineSpawnPoints[i]->GetComponentLocation();
			ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(ElementInDataSheet->BattlePawnToUse, SpawnLoc, FRotator(0.f, .0f, 0.f), SpawnParams);
			PlayerBattlePawns.Add(SpawnedPawn);
			PlayerFrontlineBattlePawns.Add(SpawnedPawn);
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
			FVector SpawnLoc = PlayersBackLineSpawnPoints[i]->GetComponentLocation();
			ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(ElementInDataSheet->BattlePawnToUse, SpawnLoc, FRotator(0.f, .0f, 0.f), SpawnParams);
			PlayerBattlePawns.Add(SpawnedPawn);
			PlayerBacklineBattlePawns.Add(SpawnedPawn);
			SpawnedPawn->bIsBackLine = true;
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
		EnemyPartyFormation = GetWorld()->SpawnActor<AEnemyPartyFormationCompnent>(PartyList->ListOfFormations[RandNo-1], FVector(0.f, 0.f, 0.f), FRotator(0.f, .0f, 0.f), SpawnParams);

		for (int i = 0; i < EnemyPartyFormation->PartyFormationFrontLineSub.Num();i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn"));

			if (EnemyPartyFormation->PartyFormationFrontLineSub[i] != NULL)
			{
				UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn  != NBULLLLL"));

				if (EnemyPartyFormation->PartyFormationFrontLineSub[i])
				{
					UE_LOG(LogTemp, Warning, TEXT("BattlePawn,%s"), *EnemyPartyFormation->PartyFormationFrontLineSub[i]->GetFName().ToString());
				}
				FVector SpawnLoc = EnemyFrontLineSpawnPoints[i]->GetComponentLocation();
				ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(EnemyPartyFormation->PartyFormationFrontLineSub[i], SpawnLoc, FRotator(0.f, 180.0f, 0.f), SpawnParams);
				EnemyBattlePawns.Add(SpawnedPawn);
				EnemyFrontlineBattlePawns.Add(SpawnedPawn);
			}
		}
		for (int i = 0; i < EnemyPartyFormation->PartyFormationBackLineSub.Num();i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn"));

			if (EnemyPartyFormation->PartyFormationBackLineSub[i] != NULL)
			{
				UE_LOG(LogTemp, Warning, TEXT("looooooop Spawnnn  != NBULLLLL"));

				if (EnemyPartyFormation->PartyFormationBackLineSub[i])
				{
					UE_LOG(LogTemp, Warning, TEXT("BattlePawn,%s"), *EnemyPartyFormation->PartyFormationBackLineSub[i]->GetFName().ToString());
				}
				FVector SpawnLoc = EnemyBackLineSpawnPoints[i]->GetComponentLocation();
				ABattlePawnBase* SpawnedPawn = GetWorld()->SpawnActor<ABattlePawnBase>(EnemyPartyFormation->PartyFormationBackLineSub[i], SpawnLoc, FRotator(0.f, 180.0f, 0.f), SpawnParams);
				EnemyBattlePawns.Add(SpawnedPawn);
				EnemyBacklineBattlePawns.Add(SpawnedPawn);
			}
		}
	}
}

void ABattleZoneBase::EndBattle()
{
	////de spawn remaning pawns
	for (int i = 0; i < PlayerBattlePawns.Num();i++)
	{
		if (PlayerBattlePawns[i]->IsPendingKill() != true && PlayerBattlePawns[i])
		{
			PlayerBattlePawns[i]->Destroy();
		}
	}
	for (int i = 0; i < EnemyBattlePawns.Num();i++)
	{
		if (EnemyBattlePawns[i] != NULL)
		{
			if (EnemyBattlePawns[i]->IsPendingKill() != true)////BUG CRASH
			{
				EnemyBattlePawns[i]->Destroy();
			}
		}
	}


	PlayerCont->EndBattle();
}