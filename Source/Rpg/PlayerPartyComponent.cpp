// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPartyComponent.h"
#include "BattlePawnBase.h"
#include "CharacterDataSheet.h"
#include "DungeonControllerBase.h"
#include "DungeonCharacterBase.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPlayerPartyComponent::UPlayerPartyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	PartyFormationFrontLine.Add(NULL);
	PartyFormationFrontLine.Add(NULL);
	PartyFormationFrontLine.Add(NULL);
	PartyFormationFrontLine.Add(NULL);
	PartyFormationBackLine.Add(NULL);
	PartyFormationBackLine.Add(NULL);
	PartyFormationBackLine.Add(NULL);
	PartyFormationBackLine.Add(NULL);

	// ...
}


// Called when the game starts
void UPlayerPartyComponent::BeginPlay()
{
	Super::BeginPlay();


	for (int i = 0;i < PartyFormationFrontLineSub.Num();i++)
	{
		if (PartyFormationFrontLineSub[i] != NULL)
		{
			FActorSpawnParameters SpawnParams;
			PartyFormationFrontLine[i] = GetWorld()->SpawnActor<ACharacterDataSheet>(PartyFormationFrontLineSub[i], FVector(0.f,0.f,0.f), FRotator(0.f, .0f, 0.f), SpawnParams);

			if (PartyFormationFrontLine[i]->BattlePawnToUse)
			{
				UE_LOG(LogTemp, Warning, TEXT("BattlePartyFormationFrontLinePawn"));
			}
		}

	}

	for (int i = 0;i < PartyFormationBackLineSub.Num();i++)
	{
		if (PartyFormationBackLineSub[i] != NULL)
		{
			FActorSpawnParameters SpawnParams;
			PartyFormationBackLine[i] = GetWorld()->SpawnActor<ACharacterDataSheet>(PartyFormationBackLineSub[i], FVector(0.f, 0.f, 0.f), FRotator(0.f, .0f, 0.f), SpawnParams);

			if (PartyFormationBackLine[i]->BattlePawnToUse)
			{
				UE_LOG(LogTemp, Warning, TEXT("BattlePartyFormationBackLinePawn"));
			}
		}

	}

}


// Called every frame
void UPlayerPartyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPlayerPartyComponent::DoIHaveAPartyFormation()
{
	for (int i = 0; i < PartyFormationFrontLine.Num();i++)
	{
		if (PartyFormationFrontLine[i] !=NULL )
		{
			return true;
		}
		if (PartyFormationBackLine[i] != NULL)
		{
			return true;
		}
	}

	return false;
}

