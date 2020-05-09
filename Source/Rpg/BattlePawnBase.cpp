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
	UE_LOG(LogTemp, Warning, TEXT("AtackActioncokpleeted"));
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
	UE_LOG(LogTemp, Warning, TEXT("move to location"));
	bool moveCompleeted = false;
	bool rotationCompleted = false;
	FVector actorLocOnBattleFloor = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("move to location 1"));
	actorLocOnBattleFloor.Z = MyBattleZone->GetActorLocation().Z;
	UE_LOG(LogTemp, Warning, TEXT("move to location 2"));
	FVector inLocOnBattleFloor = inLocation;
	inLocOnBattleFloor.Z = MyBattleZone->GetActorLocation().Z;
	UE_LOG(LogTemp, Warning, TEXT("move to location 3"));
	if (FVector::Dist(actorLocOnBattleFloor, inLocOnBattleFloor) < moveDistanceTolerance)
	{
		UE_LOG(LogTemp, Warning, TEXT("move within Tolerance"));
		moveCompleeted = true;
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("move forwards"));
		MoveForwards(inLocation);
	}
	RotateToTarget(inLocation);
	if (FVector::DotProduct(GetActorRightVector(), GetActorLocation() - inLocation) < rotationTolerance)
	{
		rotationCompleted = true;

	}
	
	if (moveCompleeted == true)
	{
		isMoving = false;
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("move Battle Pawn"));
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation()+((GetActorForwardVector()*800)), FColor::Red,false, 0.1f);
	
	UE_LOG(LogTemp, Warning, TEXT("Keep moving"));
	return false;
}

void ABattlePawnBase::MoveForwards(FVector inLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("move forawards 111"));
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
	float rotToAdd = 0;
	float angleBetween = FVector::DotProduct(-GetActorRightVector(), GetActorLocation() - targetLoc);
	float crossAngle = FVector::DotProduct(-GetActorForwardVector(), GetActorLocation() - targetLoc);

	DrawDebugPoint(GetWorld(), inLocation, 50.f, FColor::White, false, 0.1f);
	UE_LOG(LogTemp, Warning, TEXT("angle between %f"), angleBetween);
	if (angleBetween > 0)
	{
		rotToAdd = rotationSpeed * GetWorld()->DeltaTimeSeconds;
		if (rotToAdd > angleBetween)
		{
			//rotToAdd = angleBetween;
		}
	}
	else if (angleBetween < 0)
	{
		rotToAdd = -rotationSpeed * GetWorld()->DeltaTimeSeconds;
		if (rotToAdd > angleBetween)
		{
			//rotToAdd = angleBetween;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("rotToAdd ,%f"), rotToAdd);
	if (abs(angleBetween) < rotationTolerance)
	{
		if (crossAngle < 130 && crossAngle > 40)
		{

			return true;
		}
		//else
		{
			//rotToAdd = rotationSpeed * GetWorld()->DeltaTimeSeconds;
		}
	}


	FRotator rotation(0.f, rotToAdd, 0.f);
	AddActorWorldRotation(rotation);

	return false;
}

bool ABattlePawnBase::AttackTargetMelee(ABattlePawnBase* inTarget)
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


