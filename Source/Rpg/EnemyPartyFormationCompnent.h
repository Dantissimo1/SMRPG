// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnemyPartyFormationCompnent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API AEnemyPartyFormationCompnent : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AEnemyPartyFormationCompnent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Members")
		TArray<TSubclassOf<class ABattlePawnBase>> PartyFormationFrontLineSub;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Members")
		TArray<TSubclassOf<class ABattlePawnBase>> PartyFormationBackLineSub;







		
};
