// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonControllerBase.h"
#include "DungeonCharacterBase.h"
#include "EncounterVolumeBase.h"
#include "BattleZoneBase.h"
#include "PlayerPartyComponent.h"





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


}

// Called every frame
void ADungeonControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

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

}

void ADungeonControllerBase::ForwardsInput(float Value)
{
	if (bIsInBattleMode != true)
	{
		MyChar->ForwardsInput(Value);
	}
}

void ADungeonControllerBase::HorizontalInput(float Value)
{
	if (bIsInBattleMode != true)
	{
		MyChar->HorizontalInput(Value);
	}
}

void ADungeonControllerBase::JumpInput()
{
	if (bIsInBattleMode != true)
	{
		GetCharacter()->Jump();
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

/////////battle mode //////////
void ADungeonControllerBase::BeginBattle(ABattleZoneBase* InBattleZone)
{
	bIsInBattleMode = true;
	CurrentBattleArea = InBattleZone;
	InBattleZone->InitializeBattle(this);


}

void ADungeonControllerBase::EndBattle()
{
	SetViewTarget(MyChar);
	bIsInBattleMode = false;
	MyChar->CurrentEncountreVolume->BattleEndTimerReset();


}
