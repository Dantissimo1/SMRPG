// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleZoneBase.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "DungeonControllerBase.h"
#include "BattleSpawnPoint.h"



// Sets default values
ABattleZoneBase::ABattleZoneBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	RootComponent = BoxComp;


	TestCam1 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1"));
	TestCam1->SetupAttachment(RootComponent);

	//create player spwan comps
	PlayerSpawn1 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("SpawnPint1"));
	PlayerSpawn1->SetupAttachment(RootComponent);
	PlayerSpawn1->SetRelativeLocation(FVector(-500,-400,1));
	PlayerSpawn2 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("SpawnPint2"));
	PlayerSpawn2->SetupAttachment(RootComponent);
	PlayerSpawn2->SetRelativeLocation(FVector(-200, -400, 1));
	PlayerSpawn3 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("SpawnPint3"));
	PlayerSpawn3->SetupAttachment(RootComponent);
	PlayerSpawn3->SetRelativeLocation(FVector(100, -400, 1));
	PlayerSpawn4 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("SpawnPint4"));
	PlayerSpawn4->SetupAttachment(RootComponent);
	PlayerSpawn4->SetRelativeLocation(FVector(400, -400, 1));
	PlayerSpawn5 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("SpawnPint5"));
	PlayerSpawn5->SetupAttachment(RootComponent);
	PlayerSpawn5->SetRelativeLocation(FVector(-350, -659, 1));
	PlayerSpawn6 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("SpawnPint6"));
	PlayerSpawn6->SetupAttachment(RootComponent);
	PlayerSpawn6->SetRelativeLocation(FVector(-50, -659, 1));
	PlayerSpawn7 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("SpawnPint7"));
	PlayerSpawn7->SetupAttachment(RootComponent);
	PlayerSpawn7->SetRelativeLocation(FVector(250, -659, 1));
	PlayerSpawn8 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("SpawnPint8"));
	PlayerSpawn8->SetupAttachment(RootComponent);
	PlayerSpawn8->SetRelativeLocation(FVector(550, -659, 1));

	//create enemy swapn comps
	EnemySpawn1 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn1"));
	EnemySpawn1->SetupAttachment(RootComponent);
	EnemySpawn1->SetRelativeLocation(FVector(-350, 400, 1));
	EnemySpawn2 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn2"));
	EnemySpawn2->SetupAttachment(RootComponent);
	EnemySpawn2->SetRelativeLocation(FVector(-50, 400, 1));
	EnemySpawn3 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn3"));
	EnemySpawn3->SetupAttachment(RootComponent);
	EnemySpawn3->SetRelativeLocation(FVector(250, 400, 1));
	EnemySpawn4 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn4"));
	EnemySpawn4->SetupAttachment(RootComponent);
	EnemySpawn4->SetRelativeLocation(FVector(550, 400, 1));
	EnemySpawn5 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn5"));
	EnemySpawn5->SetupAttachment(RootComponent);
	EnemySpawn5->SetRelativeLocation(FVector(-500, 659, 1));
	EnemySpawn6 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn6"));
	EnemySpawn6->SetupAttachment(RootComponent);
	EnemySpawn6->SetRelativeLocation(FVector(-200, 659, 1));
	EnemySpawn7 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn7"));
	EnemySpawn7->SetupAttachment(RootComponent);
	EnemySpawn7->SetRelativeLocation(FVector(100, 659, 1));
	EnemySpawn8 = CreateDefaultSubobject<UBattleSpawnPoint>(TEXT("EnemySpawn8"));
	EnemySpawn8->SetupAttachment(RootComponent);
	EnemySpawn8->SetRelativeLocation(FVector(400, 659, 1));





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
	GetWorldTimerManager().SetTimer(TestTimer, this, &ABattleZoneBase::EndBattle, 10.0f, true);

}

void ABattleZoneBase::EndBattle()
{



	PlayerCont->EndBattle();
}