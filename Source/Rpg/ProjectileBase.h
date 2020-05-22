// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class ABattlePawnBase;

UCLASS()
class RPG_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ABattlePawnBase* myOwner;
	ABattlePawnBase* target;
	void SetUp(ABattlePawnBase* inOwner , ABattlePawnBase* inTarget);



	bool LobbedProjectile = false;

	void MoveToTargetDirect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		float Speed = 500;


};
