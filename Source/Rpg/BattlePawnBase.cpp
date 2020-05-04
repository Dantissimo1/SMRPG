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
	bool moveCompleeted = false;
	bool rotationCompleted = false;
	FVector actorLocOnBattleFloor = GetActorLocation();
	actorLocOnBattleFloor.Z = MyBattleZone->GetActorLocation().Z;
	FVector inLocOnBattleFloor = inLocation;
	inLocOnBattleFloor.Z = MyBattleZone->GetActorLocation().Z;
	if (FVector::Dist(actorLocOnBattleFloor, inLocOnBattleFloor) < moveDistanceTolerance)
	{
		UE_LOG(LogTemp, Warning, TEXT("move within Tolerance"));
		moveCompleeted = true;
	}else
	{
		MoveForwards();
	}
	RotateToTarget(inLocation);
	if (FVector::DotProduct(GetActorRightVector(), GetActorLocation() - inLocation) < rotationTolerance)
	{
		rotationCompleted = true;

	}
	
	if (rotationCompleted && moveCompleeted == true)
	{
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("move Battle Pawn"));
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation()+((GetActorForwardVector()*800)), FColor::Red,false, 0.1f);


	UE_LOG(LogTemp, Warning, TEXT("Keep moving"));
	return false;
}

void ABattlePawnBase::MoveForwards()
{
	FVector newLoc;
	newLoc = GetActorForwardVector();
	newLoc.Normalize();
	newLoc = GetActorLocation() + ((newLoc * movementSpeed) * GetWorld()->DeltaTimeSeconds);
	newLoc.Z = MyBattleZone->GetActorLocation().Z + zHeightOffset;
	SetActorLocation(newLoc);
}

void ABattlePawnBase::RotateToTarget(FVector inLocation)
{
	FVector targetLoc = inLocation;
	float rotToAdd = 0;
	float angleBetween = FVector::DotProduct(-GetActorRightVector(), GetActorLocation() - targetLoc);
	DrawDebugPoint(GetWorld(), inLocation, 50.f, FColor::Cyan, false, 0.1f);
	UE_LOG(LogTemp, Warning, TEXT("angle between %f"), angleBetween);
	if (angleBetween > 0)
	{
		rotToAdd = rotationSpeed * GetWorld()->DeltaTimeSeconds;
	}
	else if (angleBetween < 0)
	{
		rotToAdd = -rotationSpeed * GetWorld()->DeltaTimeSeconds;
	}
	FRotator rotation(0.f, rotToAdd, 0.f);
	AddActorWorldRotation(rotation);
}

