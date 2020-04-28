// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleZoneBase.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "DungeonControllerBase.h"



// Sets default values
ABattleZoneBase::ABattleZoneBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	RootComponent = BoxComp;


	TestCam1 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1"));
	TestCam1->SetupAttachment(RootComponent);
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