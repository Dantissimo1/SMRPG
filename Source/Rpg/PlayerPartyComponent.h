// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerPartyComponent.generated.h"


class ABattlePawnBase;
class UCharacterDataSheet;
class ADungeonCharacterBase;
class ADungeonControllerBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UPlayerPartyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerPartyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	ADungeonControllerBase* MyController;


	bool DoIHaveAPartyFormation();
	//void SetInitialParty();


	//////Current party members
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Members")
	class ACharacterDataSheet* ActivePartyMembersDataSheet = NULL;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Members")
	TArray<TSubclassOf<class ACharacterDataSheet>>PlayersPartyMembers;
		///need to change to an arrya of piointers that get loaded in on game start this will do for testing for now maby

	/*  ///////**LOAD REPLACE**///////// T Subclasses might need replagin with this once saving loading and party picking hapens not sure yet

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Members")
		TArray<TSubclassOf<class ACharacterDataSheet>> PartyFormationFrontLineSub;

		TArray<ACharacterDataSheet*>PartyFormationFrontLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party Members")
		TArray<TSubclassOf<class ACharacterDataSheet>> PartyFormationBackLineSub;

		TArray<ACharacterDataSheet*>PartyFormationBackLine;


};
