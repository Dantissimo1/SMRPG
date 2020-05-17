// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePawnBase.h"
#include "DrawDebugHelpers.h"
#include "BattleZoneBase.h"
#include "GameFramework/Controller.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilityBase.h"
#include "DamageLibary.h"
#include "EffectSource.h"
#include "Effect.h"
#include "Camera/CameraComponent.h"



// Sets default values
ABattlePawnBase::ABattlePawnBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABattlePawnBase::BeginPlay()
{
	Super::BeginPlay();
	//////////////UE_LOG(LogTemp, Warning, TEXT("Battle Character Exists 22"));
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

	InitializePlayersAbilitys();



}

void ABattlePawnBase::SetUpNPCPawn()
{
	
	for (int i = 0; i < abilityClasses.Num();i++)
	{	
		abilitys.Add(NewObject<UAbilityBase>(this, abilityClasses[i]));

		//NewObject<UMyObject>(this, TMyObj->GetFName(), RF_NoFlags, TMyObj.GetDefaultObject());
		
		
	}

	for (int i = 0; i < magicAbilityClasses.Num();i++)
	{
		magicAbilitys.Add(NewObject<UAbilityBase>(this ,magicAbilityClasses[i]));
	}
	
}

void ABattlePawnBase::EndAttack()
{
	attackActionCompleeted = true;
	//////////////UE_LOG(LogTemp, Warning, TEXT("AtackActioncokpleeted"));
}
/*
// Called to bind functionality to input
void ABattlePawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

void ABattlePawnBase::InitializePlayersAbilitys()
{
	UE_LOG(LogTemp, Warning, TEXT("InitializePlayersAbilitys"));
	for (int i = 0; i < myDataSheet->abilityClasses.Num();i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializePlayersAbilitys 1"));
		FActorSpawnParameters Spawnparams;
		Spawnparams.Owner = this;

		abilitys.Add(NewObject<UAbilityBase>(this ,myDataSheet->abilityClasses[i]));
	}

	for (int i = 0; i < myDataSheet->magicAbilityClasses.Num();i++)
	{

		magicAbilitys.Add(NewObject<UAbilityBase>(this ,myDataSheet->magicAbilityClasses[i]));

	}
	
}

void ABattlePawnBase::InitializeEquipedItems()
{
	FActorSpawnParameters Spawnparams;
	Spawnparams.Owner = this;
	MyEquipedItems.myWeapon = GetWorld()->SpawnActor<AWeaponBase>(Spawnparams);



}

bool ABattlePawnBase::MoveToLocation(FVector inLocation)
{
	//////////////UE_LOG(LogTemp, Warning, TEXT("move to location"));
	bool moveCompleeted = false;
	bool rotationCompleted = false;
	FVector actorLocOnBattleFloor = GetActorLocation();
	//////////////UE_LOG(LogTemp, Warning, TEXT("move to location 1"));
	actorLocOnBattleFloor.Z = MyBattleZone->GetActorLocation().Z;
	//////////////UE_LOG(LogTemp, Warning, TEXT("move to location 2"));
	FVector inLocOnBattleFloor = inLocation;
	inLocOnBattleFloor.Z = MyBattleZone->GetActorLocation().Z;
	//////////////UE_LOG(LogTemp, Warning, TEXT("move to location 3"));
	if (FVector::Dist(actorLocOnBattleFloor, inLocOnBattleFloor) < moveDistanceTolerance)
	{
		//////////////UE_LOG(LogTemp, Warning, TEXT("move within Tolerance"));
		moveCompleeted = true;
	}else
	{
		//////////////UE_LOG(LogTemp, Warning, TEXT("move forwards"));
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

	//////////////UE_LOG(LogTemp, Warning, TEXT("move Battle Pawn"));
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation()+((GetActorForwardVector()*800)), FColor::Red,false, 0.1f);
	
	//////////////UE_LOG(LogTemp, Warning, TEXT("Keep moving"));
	return false;
}

void ABattlePawnBase::MoveForwards(FVector inLocation)
{
	//////////////UE_LOG(LogTemp, Warning, TEXT("move forawards 111"));
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
	//////UE_LOG(LogTemp, Warning, TEXT("angle between %f"), angleBetween);
	FRotator rotRemaning = GetActorRotation() - (inLocation - t2).Rotation();

	if (angleBetween < rotationTolerance && angleBetween > - rotationTolerance)
	{
		FVector t4 = GetActorForwardVector();
		t4.Z = 0;
		float sideAngle = FVector::DotProduct(t4, t3);
		//////UE_LOG(LogTemp, Warning, TEXT("sideAngle =  %f"),sideAngle);
		if (sideAngle < rotationTolerance)
		{

			//////UE_LOG(LogTemp, Warning, TEXT("rot return true "));
			return true;
		}
		else
		{
			rotToAdd = rotationSpeed * GetWorld()->DeltaTimeSeconds;
			FRotator rot = GetActorRotation();
			rot.Yaw += rotToAdd;
			SetActorRotation(rot);

			return false;
		}



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
	
	if (rotRemaning.Yaw <= 0)
	{
		rotToAdd = rotationSpeed * GetWorld()->DeltaTimeSeconds;
		//////UE_LOG(LogTemp, Warning, TEXT("rledft  %f"), rotToAdd);
	}
	else if (rotRemaning.Yaw > 0)
	{
		rotToAdd -= rotationSpeed * GetWorld()->DeltaTimeSeconds;
		//////UE_LOG(LogTemp, Warning, TEXT("right =  %f"), rotToAdd);
	}

	//////UE_LOG(LogTemp, Warning, TEXT("rot to add 2 =  %f"), rotToAdd);
	if (abs(rotToAdd) > abs(rotRemaning.Yaw))
	{

		rotToAdd = rotRemaning.Yaw;
		//////UE_LOG(LogTemp, Warning, TEXT("rot corection    =  %f"), rotToAdd);
	}

	FRotator rotation(0.f, rotToAdd, 0.f);
	FRotator FinalRot = myRot + rotation;
	////////UE_LOG(LogTemp, Warning, TEXT("rot to add 3 =  %s"), *FinalRot.ToString());
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


		//////UE_LOG(LogTemp, Warning, TEXT("rot return true 2"));
		//return true;
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

void ABattlePawnBase::CauseDamageToBattlePawn(ABattlePawnBase* inPawn,bool isMagic)
{
	FDamageTypesToCause DamageToDeal;

	if (isMagic != true)
	{
		DamageToDeal.ImpactDamage = (MyEquipedItems.myWeapon->myDamage.ImpactDamage * OfensiveStats.Strength);
		DamageToDeal.SlashDamage = (MyEquipedItems.myWeapon->myDamage.SlashDamage * OfensiveStats.Strength);
		DamageToDeal.PunctureDamage = (MyEquipedItems.myWeapon->myDamage.PunctureDamage * OfensiveStats.Strength);
		DamageToDeal.FireDamage = (MyEquipedItems.myWeapon->myDamage.FireDamage * OfensiveStats.Strength);
		DamageToDeal.EarthDamage = (MyEquipedItems.myWeapon->myDamage.EarthDamage * OfensiveStats.Strength);
		DamageToDeal.WaterDamage = (MyEquipedItems.myWeapon->myDamage.WaterDamage * OfensiveStats.Strength);
		DamageToDeal.ColdDamage = (MyEquipedItems.myWeapon->myDamage.ColdDamage * OfensiveStats.Strength);
		DamageToDeal.ElectricityDamage = (MyEquipedItems.myWeapon->myDamage.ElectricityDamage * OfensiveStats.Strength);
		DamageToDeal.HolyDamage = (MyEquipedItems.myWeapon->myDamage.HolyDamage * OfensiveStats.Strength);
		DamageToDeal.VoidDamage = (MyEquipedItems.myWeapon->myDamage.VoidDamage * OfensiveStats.Strength);
		DamageToDeal.ArcaneDamage = (MyEquipedItems.myWeapon->myDamage.ArcaneDamage * OfensiveStats.Strength);
	}

	if (activeAbility != NULL)
	{
		DamageToDeal.ImpactDamage = activeAbility->DamageTypes.ImpactDamage;
		DamageToDeal.SlashDamage = activeAbility->DamageTypes.SlashDamage;
		DamageToDeal.PunctureDamage = activeAbility->DamageTypes.PunctureDamage;
		DamageToDeal.FireDamage = activeAbility->DamageTypes.FireDamage;
		DamageToDeal.EarthDamage = activeAbility->DamageTypes.EarthDamage;
		DamageToDeal.WaterDamage = activeAbility->DamageTypes.WaterDamage;
		DamageToDeal.ColdDamage = activeAbility->DamageTypes.ColdDamage;
		DamageToDeal.ElectricityDamage = activeAbility->DamageTypes.ElectricityDamage;
		DamageToDeal.HolyDamage = activeAbility->DamageTypes.HolyDamage;
		DamageToDeal.VoidDamage = activeAbility->DamageTypes.VoidDamage;
		DamageToDeal.ArcaneDamage = activeAbility->DamageTypes.ArcaneDamage;

		inPawn->TakeBattleDamage(&DamageToDeal);


	}




}

void ABattlePawnBase::TakeBattleDamage(FDamageTypesToCause* inDamage)
{





}



