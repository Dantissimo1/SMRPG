// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePawnBase.h"
#include "DrawDebugHelpers.h"
#include "BattleZoneBase.h"
#include "GameFramework/Controller.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
ABattlePawnBase::ABattlePawnBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattlePawnBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Battle Character Exists 22"));
	Speed = BaseSpeed;
}

// Called every frame
void ABattlePawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*
// Called to bind functionality to input
void ABattlePawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

bool ABattlePawnBase::MoveToLocation(FVector inLocation,float deltaTime)
{
	

//	AddMovementInput(inLocation - GetActorLocation(),100.f,true);

	UWorld* World = GetWorld();

	FVector newLoc;
	FVector targetLoc = FVector(1.f,1.f,1.f);
	newLoc = GetActorLocation() - targetLoc;
	newLoc.Normalize();
	newLoc = GetActorLocation() - ((newLoc * 100)*deltaTime);
	newLoc.Z =MyBattleZone->GetActorLocation().Z + 87;
	SetActorLocation(newLoc);
	UE_LOG(LogTemp, Warning, TEXT("move Battle Pawn"));
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation()+( inLocation - GetActorLocation()), FColor::Red,false, 0.1f);

	
	return false;
}

