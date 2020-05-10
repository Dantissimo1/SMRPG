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
	////////UE_LOG(LogTemp, Warning, TEXT("Battle Character Exists 22"));
	mainCharInfo.Speed = mainCharInfo.BaseSpeed;
}

// Called every frame
void ABattlePawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattlePawnBase::SetUpPlayerPawn(ACharacterDataSheet* inDataSheet, UBattleSpawnPoint* inPawnsBaseActor, ABattleZoneBase* inBattleZone, bool inbackline, bool inOwnedByPlayer)
{
	MyBattleZone = inBattleZone;
	myDataSheet = inDataSheet;
	PawnsBaseActor = inPawnsBaseActor;
	bIsBackLine = inbackline;
	isOwnedByPlayer = inOwnedByPlayer;

	//set stats
	mainCharInfo = myDataSheet->CharacterDetails;
	OfensiveStats = myDataSheet->OfensiveStats;
	DefensiveStats = myDataSheet->DefensiveStats;

	MyEquipedItems = myDataSheet->itemsEquiped;

}

void ABattlePawnBase::EndAttack()
{
	attackActionCompleeted = true;
	////////UE_LOG(LogTemp, Warning, TEXT("AtackActioncokpleeted"));
}
/*
// Called to bind functionality to input
void ABattlePawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

void ABattlePawnBase::InitializeEquipedItems()
{
	FActorSpawnParameters Spawnparams;
	Spawnparams.Owner = this;
	MyEquipedItems.myWeapon = GetWorld()->SpawnActor<AWeaponBase>(Spawnparams);



}

bool ABattlePawnBase::MoveToLocation(FVector inLocation)
{
	////////UE_LOG(LogTemp, Warning, TEXT("move to location"));
	bool moveCompleeted = false;
	bool rotationCompleted = false;
	FVector actorLocOnBattleFloor = GetActorLocation();
	////////UE_LOG(LogTemp, Warning, TEXT("move to location 1"));
	actorLocOnBattleFloor.Z = MyBattleZone->GetActorLocation().Z;
	////////UE_LOG(LogTemp, Warning, TEXT("move to location 2"));
	FVector inLocOnBattleFloor = inLocation;
	inLocOnBattleFloor.Z = MyBattleZone->GetActorLocation().Z;
	////////UE_LOG(LogTemp, Warning, TEXT("move to location 3"));
	if (FVector::Dist(actorLocOnBattleFloor, inLocOnBattleFloor) < moveDistanceTolerance)
	{
		////////UE_LOG(LogTemp, Warning, TEXT("move within Tolerance"));
		moveCompleeted = true;
	}else
	{
		////////UE_LOG(LogTemp, Warning, TEXT("move forwards"));
		MoveForwards(inLocation);
	}
	RotateToTarget(inLocation);
	if (FVector::DotProduct(GetActorRightVector(), GetActorLocation() - inLocOnBattleFloor) < rotationTolerance)
	{
		rotationCompleted = true;

	}
	
	if (moveCompleeted == true)
	{
		isMoving = false;
		return true;
	}

	////////UE_LOG(LogTemp, Warning, TEXT("move Battle Pawn"));
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation()+((GetActorForwardVector()*800)), FColor::Red,false, 0.1f);
	
	////////UE_LOG(LogTemp, Warning, TEXT("Keep moving"));
	return false;
}

void ABattlePawnBase::MoveForwards(FVector inLocation)
{
	////////UE_LOG(LogTemp, Warning, TEXT("move forawards 111"));
	isMoving = true;
	FVector newLoc;
	newLoc = GetActorLocation() - inLocation;
	newLoc.Normalize();
	newLoc = GetActorLocation() - ((newLoc * movementSpeed) * GetWorld()->DeltaTimeSeconds);
	newLoc.Z = MyBattleZone->GetActorLocation().Z + zHeightOffset;
	SetActorLocation(newLoc);
}

bool ABattlePawnBase::RotateToTarget(FVector inLocation)
{
	FVector targetLoc = inLocation;
	FRotator myRot = GetActorRotation();

	FVector t1 = -GetActorRightVector();
	t1.Z = 0;
	t1.Normalize();
	FVector t2 = GetActorLocation();
	t2.Z = 0;
	inLocation.Z = 0;
	FVector t3 = t2 - inLocation;
	t3.Normalize();

	float angleBetween = FVector::DotProduct(t1, t3 );
	float rotToAdd = 0;

	FRotator rotRemaning = GetActorRotation() - (inLocation - GetActorLocation()).Rotation();

	if (abs(angleBetween) < rotationTolerance)
	{
		if ((inLocation - GetActorLocation()).Rotation().Yaw == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("rot return true  ===   00000"));
		}

		UE_LOG(LogTemp, Warning, TEXT("rot return true "));
		return true;
	}

	if (rotRemaning.Yaw < -179)
	{
		rotRemaning.Yaw += 360;
	}
	if (rotRemaning.Yaw > 179)
	{
		rotRemaning.Yaw -= 360;
	}

	DrawDebugPoint(GetWorld(), inLocation, 50.f, FColor::White, false, 0.1f);
	UE_LOG(LogTemp, Warning, TEXT("angle between %f"), rotRemaning.Yaw);
	if (rotRemaning.Yaw <= 0)
	{
		rotToAdd = rotationSpeed * GetWorld()->DeltaTimeSeconds;
		UE_LOG(LogTemp, Warning, TEXT("rledft  %f"), rotToAdd);
	}
	else if (rotRemaning.Yaw > 0)
	{
		rotToAdd -= rotationSpeed * GetWorld()->DeltaTimeSeconds;
		UE_LOG(LogTemp, Warning, TEXT("right =  %f"), rotToAdd);
	}

	UE_LOG(LogTemp, Warning, TEXT("rot to add 2 =  %f"), rotToAdd);
	if (abs(rotToAdd) > abs(rotRemaning.Yaw))
	{

		rotToAdd = rotRemaning.Yaw;
		UE_LOG(LogTemp, Warning, TEXT("rot corection    =  %f"), rotToAdd);
	}

	FRotator rotation(0.f, rotToAdd, 0.f);
	FRotator FinalRot = myRot + rotation;
	//UE_LOG(LogTemp, Warning, TEXT("rot to add 3 =  %s"), *FinalRot.ToString());
	if (FinalRot.Yaw < -180)
	{
		FinalRot.Yaw += 360;
	}
	if (FinalRot.Yaw>180)
	{
		FinalRot.Yaw -= 360;
	}

	SetActorRotation(FinalRot);
	//AddActorWorldRotation(rotation);
	if (abs(angleBetween) < rotationTolerance)
	{


		UE_LOG(LogTemp, Warning, TEXT("rot return true "));
		return true;
	}
	return false;
}

bool ABattlePawnBase::AttackTargetMelee(ABattlePawnBase* inTarget)
{




	return false;
}

bool ABattlePawnBase::AttackTargetMagic(ABattlePawnBase* inTarget)
{



	return false;
}

void ABattlePawnBase::CauseDamageToBattlePawn(ABattlePawnBase* inPawn)
{
	FDamageTypesToCause DamageToDeal;

	float damagemodifierToUse = 1;




	DamageToDeal.ImpactDamage = (MyEquipedItems.myWeapon->myDamage.ImpactDamage* damagemodifierToUse);
	DamageToDeal.SlashDamage = (MyEquipedItems.myWeapon->myDamage.SlashDamage * damagemodifierToUse);
	DamageToDeal.PunctureDamage = (MyEquipedItems.myWeapon->myDamage.PunctureDamage * damagemodifierToUse);
	DamageToDeal.FireDamage = (MyEquipedItems.myWeapon->myDamage.FireDamage * damagemodifierToUse);
	DamageToDeal.EarthDamage = (MyEquipedItems.myWeapon->myDamage.EarthDamage * damagemodifierToUse);
	DamageToDeal.WaterDamage = (MyEquipedItems.myWeapon->myDamage.WaterDamage * damagemodifierToUse);
	DamageToDeal.ColdDamage = (MyEquipedItems.myWeapon->myDamage.ColdDamage * damagemodifierToUse);
	DamageToDeal.ElectricityDamage = (MyEquipedItems.myWeapon->myDamage.ElectricityDamage * damagemodifierToUse);
	DamageToDeal.HolyDamage = (MyEquipedItems.myWeapon->myDamage.HolyDamage * damagemodifierToUse);
	DamageToDeal.VoidDamage = (MyEquipedItems.myWeapon->myDamage.VoidDamage * damagemodifierToUse);
	DamageToDeal.ArcaneDamage = (MyEquipedItems.myWeapon->myDamage.ArcaneDamage * damagemodifierToUse);






}


