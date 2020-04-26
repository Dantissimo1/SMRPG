// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonControllerBase.h"
#include "DungeonCharacterBase.h"


// Sets default values
ADungeonControllerBase::ADungeonControllerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ADungeonControllerBase::BeginPlay()
{
	Super::BeginPlay();

	MyChar = Cast<ADungeonCharacterBase>(GetCharacter());
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
	
	MyChar->ForwardsInput(Value);

}

void ADungeonControllerBase::HorizontalInput(float Value)
{
	MyChar->HorizontalInput(Value);
}

void ADungeonControllerBase::JumpInput()
{
	GetCharacter()->Jump();
}

void ADungeonControllerBase::CameraYawInput(float Value)
{
	MyChar->CameraYawInput(Value);
}

void ADungeonControllerBase::CameraPitchInput(float Value)
{
	
	MyChar->CameraPitchInput(Value);
}

void ADungeonControllerBase::ScrollInput(float Value)
{
	MyChar->ScrollCamera(Value);


}
