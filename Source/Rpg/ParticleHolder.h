// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParticleHolder.generated.h"


class ABattlePawnBase;


UCLASS()
class RPG_API AParticleHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticleHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "damage")
	ABattlePawnBase* myOwner;

	void SetUp(ABattlePawnBase* inOwner);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "damage")
	float size = 1;

	UFUNCTION(BlueprintCallable)
		void DoAbilityDamage();
	UFUNCTION(BlueprintCallable)
		void AnimEnd();
};
