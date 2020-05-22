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
#include "BattleZoneBase.h"
#include "BattleBrainComponent.h"
#include "ParticleHolder.h"
#include "ProjectileBase.h"


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
	OfensiveStatsBase = myDataSheet->OfensiveStats;
	DefensiveStatsBase = myDataSheet->DefensiveStats;

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
	animFinished = true;
	//////////////UE_LOG(LogTemp, Warning, TEXT("AtackActioncokpleeted"));
}
void ABattlePawnBase::EndOpotunityAttack()
{
	opotunityActionCompleeted = true;
}
void ABattlePawnBase::EndCounterAttack()
{
	CounterActionCompleeted = true;
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
		if (myDataSheet->abilityClasses[i] != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("InitializePlayersAbilitys 1"));
			abilitys.Add(NewObject<UAbilityBase>(this, myDataSheet->abilityClasses[i]));
		}
	}

	for (int i = 0; i < myDataSheet->magicAbilityClasses.Num();i++)
	{
		if (myDataSheet->magicAbilityClasses[i] != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("InitializePlayersAbilitysMagic 1"));
			magicAbilitys.Add(NewObject<UAbilityBase>(this, myDataSheet->magicAbilityClasses[i]));
		}
	}
	
}

void ABattlePawnBase::InitializeEquipedItems()
{
	FActorSpawnParameters Spawnparams;
	Spawnparams.Owner = this;
	FVector locationToSpawn = FVector(0, 0, 0);

	if (isOwnedByPlayer != true)
	{
		MyEquipedItems.myWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponToSpawn, locationToSpawn, FRotator(0, 0, 0), Spawnparams);
	}
	if (isOwnedByPlayer == true)
	{
		MyEquipedItems.myWeapon = GetWorld()->SpawnActor<AWeaponBase>(myDataSheet->itemsEquiped.myWeapon, locationToSpawn, FRotator(0, 0, 0), Spawnparams);
	}


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
		return true;
	}
	return false;
}

bool ABattlePawnBase::RunAttackTargetMelee(ABattlePawnBase* inTarget, UAbilityBase* inAbility)
{
	if (attackCompleeted == false)
	{
		attackTarget = inTarget;
		activeAbility = inAbility;
		if (animFinished != true)
		{
			isAttackingMelee = true;
		}else
		{
			isAttackingMelee = false;
		}
		if (doingDamage)
		{
			RunDamageStepMelee(inTarget);
		}
		if (animFinished && damageDone)
		{
			attackCompleeted = true;
		}
	}
	else
	{
		attackTarget = NULL;
		activeAbility = NULL;
		attackCompleeted = false;
		animFinished = false;
		damageDone = false;
		doingDamage = false;
		return true;
	}
	return false;
}


void ABattlePawnBase::RunDamageStepMelee(ABattlePawnBase* inTarget)
{
	FDamageTypesToCause DamageToDeal;
	float statsModifierTouse = 0;
	statsModifierTouse = OfensiveStats.Strength;
	statsModifierTouse /= 100;

	/// spawn mele damage particle here from weapon
	UE_LOG(LogTemp, Warning, TEXT("waepon naem  = %s"), *MyEquipedItems.myWeapon->name);
	DamageToDeal.ImpactDamage = (MyEquipedItems.myWeapon->myDamage.ImpactDamage * (statsModifierTouse));
	DamageToDeal.SlashDamage = (MyEquipedItems.myWeapon->myDamage.SlashDamage * (statsModifierTouse));
	DamageToDeal.PunctureDamage = (MyEquipedItems.myWeapon->myDamage.PunctureDamage * (statsModifierTouse));
	DamageToDeal.FireDamage = (MyEquipedItems.myWeapon->myDamage.FireDamage * (statsModifierTouse));
	DamageToDeal.EarthDamage = (MyEquipedItems.myWeapon->myDamage.EarthDamage * (statsModifierTouse));
	DamageToDeal.WaterDamage = (MyEquipedItems.myWeapon->myDamage.WaterDamage * (statsModifierTouse));
	DamageToDeal.ColdDamage = (MyEquipedItems.myWeapon->myDamage.ColdDamage * (statsModifierTouse));
	DamageToDeal.ElectricityDamage = (MyEquipedItems.myWeapon->myDamage.ElectricityDamage * (statsModifierTouse));
	DamageToDeal.HolyDamage = (MyEquipedItems.myWeapon->myDamage.HolyDamage * (statsModifierTouse));
	DamageToDeal.VoidDamage = (MyEquipedItems.myWeapon->myDamage.VoidDamage * (statsModifierTouse));
	DamageToDeal.ArcaneDamage = (MyEquipedItems.myWeapon->myDamage.ArcaneDamage * (statsModifierTouse));

	if (activeAbility != NULL)
	{
		activeAbility->AbilitysInstructions(this, inTarget, statsModifierTouse, DamageToDeal);
	}
	else
	{
		inTarget->TakeBattleDamage(DamageToDeal);
	}
	doingDamage = false;
	damageDone = true;
}

bool ABattlePawnBase::RunAttackTargetMagic(ABattlePawnBase* inTarget, UAbilityBase* inAbility)
{
	if (attackCompleeted == false)
	{
		attackTarget = inTarget;
		activeAbility = inAbility;
		if (animFinished != true)
		{
			isAttackingMagic = true;
		}
		else
		{
			isAttackingMagic = false;
		}
		if (doingDamage)
		{
			UE_LOG(LogTemp, Warning, TEXT("RunDamageStepMagic "))
			doingDamage = RunDamageStepMagic(inTarget);
		}
		if (animFinished && damageDone)
		{
			attackCompleeted = true;
		}
	}
	else
	{
		attackTarget = NULL;
		activeAbility = NULL;
		attackCompleeted = false;
		animFinished = false;
		damageDone = false;
		doingDamage = false;
		return true;
	}
	return false;
}

bool ABattlePawnBase::RunDamageStepMagic(ABattlePawnBase* inTarget)
{
	// here i need to spawn a particle whith ref to this and triggger a bool in this once damage is done
	FDamageTypesToCause DamageToDeal;
	float statsModifierTouse = 0;
	statsModifierTouse = OfensiveStats.ArcaneAptitude;
	statsModifierTouse /= 100;
	if (activeAbility != NULL)
	{
		if (particleSpawned != true)
		{
			if (activeAbility->dammgeEffect != NULL)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				spawnedParticle = GetWorld()->SpawnActor<AParticleHolder>(activeAbility->dammgeEffect, inTarget->GetActorLocation(),FRotator(0,0,0),SpawnParams);
				spawnedParticle->SetUp(this);
				particleSpawned = true;
				//spawn particle
			}
			else
			{
				doAbilityDamage = true;
			}
		}
		if (doAbilityDamage)
		{
			activeAbility->AbilitysInstructions(this, inTarget, statsModifierTouse, DamageToDeal);
			particleSpawned = false;
			doAbilityDamage = false;
		}
		else if (abilityAnimDone)
		{
			damageDone = true;
			doingDamage = false;
			return false;
		}
	}
	else
	{
		//inTarget->TakeBattleDamage(DamageToDeal);
		damageDone = true;
		doingDamage = false;
		return false;
	}

	return true;
}


bool ABattlePawnBase::RunAttackTargetRanged(ABattlePawnBase* inTarget, UAbilityBase* inAbility)
{
	if (attackCompleeted == false)
	{
		UE_LOG(LogTemp, Warning, TEXT(" RunAttackTargetRanged 1"));
		attackTarget = inTarget;
		activeAbility = inAbility;
		if (animFinished != true)
		{
			UE_LOG(LogTemp, Warning, TEXT(" RunAttackTargetRanged 2"));
			isAttackingRanged = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT(" RunAttackTargetRanged 3"));
			isAttackingRanged = false;
		}
		if (doingDamage)
		{
			UE_LOG(LogTemp, Warning, TEXT(" RunAttackTargetRanged 4"));
			doingDamage = RunDamageStepRanged(inTarget);
		}
		if (animFinished && damageDone)
		{
			UE_LOG(LogTemp, Warning, TEXT(" RunAttackTargetRanged 5"));
			attackCompleeted = true;
		}
	}
	else
	{
		attackTarget = NULL;
		activeAbility = NULL;
		attackCompleeted = false;
		animFinished = false;
		damageDone = false;
		doingDamage = false;
		return true;
	}
	return false;
}

bool ABattlePawnBase::RunDamageStepRanged(ABattlePawnBase* inTarget)
{
	UE_LOG(LogTemp, Warning, TEXT(" RunDamageStepRanged 0"));
	if (hasShot != true)
	{
		UE_LOG(LogTemp, Warning, TEXT(" RunDamageStepRanged 1"));
		AProjectileBase* spawnedProjectile;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		spawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(MyEquipedItems.myWeapon->ProjectileToUse, GetActorLocation(), GetActorRotation(), SpawnParams);
		spawnedProjectile->SetUp(this,inTarget);
		hasShot = true;
		//hasHit = true;
	}

	if (hasHit)
	{
		FDamageTypesToCause DamageToDeal;
		float statsModifierTouse = 0;
		statsModifierTouse = OfensiveStats.RangeFinesse;
		statsModifierTouse /= 100;

		UE_LOG(LogTemp, Warning, TEXT("waepon naem  = %s"), *MyEquipedItems.myWeapon->name);
		DamageToDeal.ImpactDamage = (MyEquipedItems.myWeapon->myDamage.ImpactDamage * (statsModifierTouse));
		DamageToDeal.SlashDamage = (MyEquipedItems.myWeapon->myDamage.SlashDamage * (statsModifierTouse));
		DamageToDeal.PunctureDamage = (MyEquipedItems.myWeapon->myDamage.PunctureDamage * (statsModifierTouse));
		DamageToDeal.FireDamage = (MyEquipedItems.myWeapon->myDamage.FireDamage * (statsModifierTouse));
		DamageToDeal.EarthDamage = (MyEquipedItems.myWeapon->myDamage.EarthDamage * (statsModifierTouse));
		DamageToDeal.WaterDamage = (MyEquipedItems.myWeapon->myDamage.WaterDamage * (statsModifierTouse));
		DamageToDeal.ColdDamage = (MyEquipedItems.myWeapon->myDamage.ColdDamage * (statsModifierTouse));
		DamageToDeal.ElectricityDamage = (MyEquipedItems.myWeapon->myDamage.ElectricityDamage * (statsModifierTouse));
		DamageToDeal.HolyDamage = (MyEquipedItems.myWeapon->myDamage.HolyDamage * (statsModifierTouse));
		DamageToDeal.VoidDamage = (MyEquipedItems.myWeapon->myDamage.VoidDamage * (statsModifierTouse));
		DamageToDeal.ArcaneDamage = (MyEquipedItems.myWeapon->myDamage.ArcaneDamage * (statsModifierTouse));

		if (activeAbility != NULL)
		{
			activeAbility->AbilitysInstructions(this, inTarget, statsModifierTouse, DamageToDeal);
			hasShot = false;
			hasHit = false;
			damageDone = true;
			return false;
		}
		else
		{
			inTarget->TakeBattleDamage(DamageToDeal);
			hasShot = false;
			hasHit = false;
			damageDone = true;
			return false;
		}
		doingDamage = false;
		damageDone = true;
	}


	return true;
}

bool ABattlePawnBase::RunAttackTargetCounter(ABattlePawnBase* inTarget)
{
	if (attackCompleeted == false)
	{
		attackTarget = inTarget;
		if (animFinished != true)
		{
			isAttackingStanding = true;
		}
		else
		{
			isAttackingStanding = false;
		}
		if (doingDamage)
		{
			if (MyEquipedItems.myWeapon->isRanged)
			{
				RunDamageStepRanged(inTarget);
			}
			else
			{
				RunDamageStepMelee(inTarget);
			}
		}
		if (animFinished && damageDone)
		{
			attackCompleeted = true;
		}
	}
	else
	{
		bHasReaction = false;
		attackTarget = NULL;
		activeAbility = NULL;
		attackCompleeted = false;
		animFinished = false;
		damageDone = false;
		doingDamage = false;
		return true;
	}
	return false;
	return false;
}




void ABattlePawnBase::TriggerDamageStep()
{
	doingDamage = true;
}

void ABattlePawnBase::CauseDamageToBattlePawn(ABattlePawnBase* inPawn)
{

	FDamageTypesToCause DamageToDeal;
	float statsModifierTouse = 0;

	if (isAttackingMelee)
	{
		statsModifierTouse = OfensiveStats.Strength;
	}
	if (isAttackingRanged)
	{
		statsModifierTouse = OfensiveStats.RangeFinesse;
	}
	if (isAttackingMagic)
	{
		statsModifierTouse = OfensiveStats.ArcaneAptitude;
	}

	if (activeAbility == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("waepon naem  = %s"), *MyEquipedItems.myWeapon->name);
		DamageToDeal.ImpactDamage = (MyEquipedItems.myWeapon->myDamage.ImpactDamage * (statsModifierTouse / 100));
		DamageToDeal.SlashDamage = (MyEquipedItems.myWeapon->myDamage.SlashDamage * (statsModifierTouse / 100));
		DamageToDeal.PunctureDamage = (MyEquipedItems.myWeapon->myDamage.PunctureDamage * (statsModifierTouse / 100));
		DamageToDeal.FireDamage = (MyEquipedItems.myWeapon->myDamage.FireDamage * (statsModifierTouse / 100));
		DamageToDeal.EarthDamage = (MyEquipedItems.myWeapon->myDamage.EarthDamage * (statsModifierTouse / 100));
		DamageToDeal.WaterDamage = (MyEquipedItems.myWeapon->myDamage.WaterDamage * (statsModifierTouse / 100));
		DamageToDeal.ColdDamage = (MyEquipedItems.myWeapon->myDamage.ColdDamage * (statsModifierTouse / 100));
		DamageToDeal.ElectricityDamage = (MyEquipedItems.myWeapon->myDamage.ElectricityDamage * (statsModifierTouse / 100));
		DamageToDeal.HolyDamage = (MyEquipedItems.myWeapon->myDamage.HolyDamage * (statsModifierTouse / 100));
		DamageToDeal.VoidDamage = (MyEquipedItems.myWeapon->myDamage.VoidDamage * (statsModifierTouse / 100));
		DamageToDeal.ArcaneDamage = (MyEquipedItems.myWeapon->myDamage.ArcaneDamage * (statsModifierTouse / 100));
	}else
	{
		if (isAttackingMagic )
		{
			DamageToDeal.ImpactDamage = activeAbility->DamageTypes.ImpactDamage * (statsModifierTouse / 100);
			DamageToDeal.SlashDamage = activeAbility->DamageTypes.SlashDamage * (statsModifierTouse / 100);
			DamageToDeal.PunctureDamage = activeAbility->DamageTypes.PunctureDamage * (statsModifierTouse / 100);
			DamageToDeal.FireDamage = activeAbility->DamageTypes.FireDamage * (statsModifierTouse / 100);
			DamageToDeal.EarthDamage = activeAbility->DamageTypes.EarthDamage * (statsModifierTouse / 100);
			DamageToDeal.WaterDamage = activeAbility->DamageTypes.WaterDamage * (statsModifierTouse / 100);
			DamageToDeal.ColdDamage = activeAbility->DamageTypes.ColdDamage * (statsModifierTouse / 100);
			DamageToDeal.ElectricityDamage = activeAbility->DamageTypes.ElectricityDamage * (statsModifierTouse / 100);
			DamageToDeal.HolyDamage = activeAbility->DamageTypes.HolyDamage * (statsModifierTouse / 100);
			DamageToDeal.VoidDamage = activeAbility->DamageTypes.VoidDamage * (statsModifierTouse / 100);
			DamageToDeal.ArcaneDamage = activeAbility->DamageTypes.ArcaneDamage * (statsModifierTouse / 100);
		}
		else
		{
			DamageToDeal.ImpactDamage = (activeAbility->DamageTypes.ImpactDamage + MyEquipedItems.myWeapon->myDamage.ImpactDamage) * (statsModifierTouse / 100);
			DamageToDeal.SlashDamage = (activeAbility->DamageTypes.SlashDamage + MyEquipedItems.myWeapon->myDamage.SlashDamage) * (statsModifierTouse / 100);
			DamageToDeal.PunctureDamage = (activeAbility->DamageTypes.PunctureDamage + MyEquipedItems.myWeapon->myDamage.PunctureDamage) * (statsModifierTouse / 100);
			DamageToDeal.FireDamage = (activeAbility->DamageTypes.FireDamage + MyEquipedItems.myWeapon->myDamage.FireDamage) * (statsModifierTouse / 100);
			DamageToDeal.EarthDamage = (activeAbility->DamageTypes.EarthDamage + MyEquipedItems.myWeapon->myDamage.EarthDamage) * (statsModifierTouse / 100);
			DamageToDeal.WaterDamage = (activeAbility->DamageTypes.WaterDamage + MyEquipedItems.myWeapon->myDamage.WaterDamage) * (statsModifierTouse / 100);
			DamageToDeal.ColdDamage = (activeAbility->DamageTypes.ColdDamage + MyEquipedItems.myWeapon->myDamage.ColdDamage) * (statsModifierTouse / 100);
			DamageToDeal.ElectricityDamage = (activeAbility->DamageTypes.ElectricityDamage + MyEquipedItems.myWeapon->myDamage.ElectricityDamage) * (statsModifierTouse / 100);
			DamageToDeal.HolyDamage = (activeAbility->DamageTypes.HolyDamage + MyEquipedItems.myWeapon->myDamage.HolyDamage) * (statsModifierTouse / 100);
			DamageToDeal.VoidDamage = (activeAbility->DamageTypes.VoidDamage + MyEquipedItems.myWeapon->myDamage.VoidDamage) * (statsModifierTouse / 100);
			DamageToDeal.ArcaneDamage = (activeAbility->DamageTypes.ArcaneDamage + MyEquipedItems.myWeapon->myDamage.ArcaneDamage) * (statsModifierTouse / 100);
		}
	}

	inPawn->TakeBattleDamage(DamageToDeal);
	damageDone = true;

}

void ABattlePawnBase::TakeBattleDamage(FDamageTypesToCause inDamage)
{
	FDamageTypesToCause finalDamage;

	finalDamage.ImpactDamage = inDamage.ImpactDamage -((inDamage.ImpactDamage / 100) *DefensiveStats.ImpactResistance);
	finalDamage.SlashDamage = inDamage.SlashDamage - ((inDamage.SlashDamage / 100) * DefensiveStats.SlashResistance);
	finalDamage.PunctureDamage = inDamage.PunctureDamage - ((inDamage.PunctureDamage / 100) * DefensiveStats.PunctureResistance);
	finalDamage.FireDamage = inDamage.FireDamage - ((inDamage.FireDamage / 100) * DefensiveStats.FireResistance);
	finalDamage.EarthDamage = inDamage.EarthDamage - ((inDamage.EarthDamage / 100) * DefensiveStats.EarthResistance);
	finalDamage.WaterDamage = inDamage.WaterDamage - ((inDamage.WaterDamage / 100) * DefensiveStats.WaterResistance);
	finalDamage.ColdDamage = inDamage.ColdDamage - ((inDamage.ColdDamage / 100) * DefensiveStats.ColdResistance);
	finalDamage.ElectricityDamage = inDamage.ElectricityDamage - ((inDamage.ElectricityDamage / 100) * DefensiveStats.ElectricityResistance);
	finalDamage.HolyDamage = inDamage.HolyDamage - ((inDamage.HolyDamage / 100) * DefensiveStats.HolyResistance);
	finalDamage.VoidDamage = inDamage.VoidDamage -((inDamage.VoidDamage / 100) * DefensiveStats.VoidResistance);
	finalDamage.ArcaneDamage = inDamage.ArcaneDamage - ((inDamage.ArcaneDamage / 100) * DefensiveStats.ArcaneResistance);

	float finalDamageTaken = finalDamage.ImpactDamage + finalDamage.SlashDamage + finalDamage.PunctureDamage + finalDamage.FireDamage
		+ finalDamage.EarthDamage + finalDamage.WaterDamage + finalDamage.ColdDamage + finalDamage.ElectricityDamage
		+ finalDamage.HolyDamage + finalDamage.VoidDamage + finalDamage.ArcaneDamage;

	mainCharInfo.Health -= finalDamageTaken;
	if (mainCharInfo.Health < 1)
	{
		GoDown();
	}
	UE_LOG(LogTemp, Warning, TEXT("finalDamageTaken %f"), finalDamageTaken);
	UE_LOG(LogTemp, Warning, TEXT("mainCharInfo.Health %f"), mainCharInfo.Health);

}

void ABattlePawnBase::HealTarget(ABattlePawnBase* inPawn)
{
	if (activeAbility != NULL)
	{
		float healAmount = ((inPawn->mainCharInfo.MaxHealth / 100) * activeAbility->healPercent)* (OfensiveStats.ArcaneAptitude / 100);

		inPawn->mainCharInfo.Health += healAmount;
		if (mainCharInfo.Health > mainCharInfo.MaxHealth)
		{
			mainCharInfo.Health = mainCharInfo.MaxHealth;
		}
	}

}

void ABattlePawnBase::GoDown()
{
	isDown = true;

	MyBattleZone->BattleBrain->RemovePawnsTurns(this);

}



