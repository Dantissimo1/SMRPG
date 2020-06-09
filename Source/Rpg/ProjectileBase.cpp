// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "DrawDebugHelpers.h"
#include "BattlePawnBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));

	
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DrawDebugPoint(GetWorld(), GetActorLocation(),10.f, FColor::Red, false, 0.1f);
	//UE_LOG(LogTemp, Warning, TEXT(" Prjectile esxiststskljhsd;fgklhja;dlgkh ") );
	if (LobbedProjectile == false)
	{
		MoveToTargetDirect();
	}
}

void AProjectileBase::SetUp(ABattlePawnBase* inOwner, ABattlePawnBase* inTarget)
{
	myOwner = inOwner;
	target = inTarget;
	SetActorLocation(inOwner->GetActorLocation());
}

void AProjectileBase::MoveToTargetDirect()
{
	FVector newLoc;
	newLoc = GetActorLocation() - target->GetActorLocation();
	newLoc.Normalize();
	newLoc = GetActorLocation() - ((newLoc * Speed) * GetWorld()->DeltaTimeSeconds);
	SetActorLocation(newLoc,true);
	
	TArray<AActor*>Overlaps;
	GetOverlappingActors(Overlaps);

	for (int i = 0; i < Overlaps.Num();i++)
	{
		if (Cast<ABattlePawnBase>(Overlaps[i]) == target)
		{
			myOwner->hasHit = true;
			Destroy();
		}
	}
}

