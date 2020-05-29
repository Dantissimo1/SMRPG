// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSpawnPoint.h"
#include "DrawDebugHelpers.h"
#include "AttackPosition.h"
#include "OpotunityAttackPosition.h"



// Sets default values for this component's properties
UBattleSpawnPoint::UBattleSpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	
	FVector newPos = GetComponentLocation();
	newPos.X = attackPointofset;
	AttackPoint = CreateDefaultSubobject<UAttackPosition>(TEXT("Attack Point"));
	AttackPoint->SetupAttachment(this);
	AttackPoint->SetWorldLocation(newPos);
	newPos.X = opotunityPointOfset;
	OpotunityPoint = CreateDefaultSubobject<UOpotunityAttackPosition>(TEXT("Opotunity Point"));
	OpotunityPoint->SetupAttachment(this);
	OpotunityPoint->SetWorldLocation(newPos);

	//DrawDebugPoint(GetWorld(), AttackPoint->GetComponentLocation(), 10.f, FColor::Red, true);

	//DrawDebugPoint(GetWorld(), OpotunityPoint->GetComponentLocation(), 10.f, FColor::Yellow, true);

	// ...
}


// Called when the game starts
void UBattleSpawnPoint::BeginPlay()
{
	Super::BeginPlay();



	//DrawDebugPoint(GetWorld(), AttackPoint->GetComponentLocation(), 10.f, FColor::Red, true);
	//DrawDebugPoint(GetWorld(), OpotunityPoint->GetComponentLocation(), 10.f, FColor::Yellow, true);

	// ...
	
}


// Called every frame
void UBattleSpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//DrawDebugPoint(GetWorld(), GetComponentLocation(), 10.0f, FColor::Green, false, 0.1f);
}

