// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DungeonControllerBase.h"




// Sets default values
ADungeonCharacterBase::ADungeonCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);


}

// Called when the game starts or when spawned
void ADungeonCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	World = GetWorld();


}

// Called every frame
void ADungeonCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	ClampCameraPitch();
}

void ADungeonCharacterBase::ForwardsInput(float Value)
{



}

void ADungeonCharacterBase::HorizontalInput(float Value)
{



}

void ADungeonCharacterBase::CameraYawInput(float Value)
{
	AddControllerYawInput(Value);
}

void ADungeonCharacterBase::CameraPitchInput(float Value)
{
	AddControllerPitchInput(Value);
}



void ADungeonCharacterBase::ClampCameraPitch()
{
	float NewPitch = GetControlRotation().Pitch;
	FRotator NewRot = GetControlRotation();
	if (NewPitch < 270 && NewPitch > 20)
	{
		NewPitch = 20;
		NewRot.Pitch = NewPitch;
		GetController()->SetControlRotation(NewRot);
		return;
	}
}

void ADungeonCharacterBase::ScrollCamera(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("M 1,%f"), Value);
	float NewBoomLength = CameraBoom->TargetArmLength -( Value * World->GetDeltaSeconds() * CamScrollSpeed);
	UE_LOG(LogTemp, Warning, TEXT("M 2,%f"), NewBoomLength);
	if (NewBoomLength > MaxCamDistance) { NewBoomLength = MaxCamDistance; }
	else if (NewBoomLength < MinCamDistance) { NewBoomLength = MinCamDistance; }
	CameraBoom->TargetArmLength = NewBoomLength;
	

}

