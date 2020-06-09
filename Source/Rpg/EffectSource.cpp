// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectSource.h"
#include "DamageLibary.h"
#include "Effect.h"
#include "DrawDebugHelpers.h"
#include "BattlePawnBase.h"
#include "AbilityBase.h"
#include "Components/ActorComponent.h"


AEffectSource::AEffectSource()
{


}

void AEffectSource::Tick(float DeltaTime)
{
}

void AEffectSource::BeginPlay()
{
}

bool AEffectSource::CheckIfEffectsRemain()
{
	if (activeEffects.Num() > 0)
	{
		return true;
	}
	myOwner->activeEffectSources.Remove(this);
	Destroy();
	return false;
}

void AEffectSource::InitialRun(ABattlePawnBase* inOwner, UAbilityBase* inSourceAbility)
{
	myOwner = inOwner;
	TurnsRemaning = lifeInTurns;
	sourceAbility = inSourceAbility;
	//UE_LOG(LogTemp, Warning, TEXT("InitialRun"));

	activateEffect();
	
}

void AEffectSource::TriggeredRun()
{
	//UE_LOG(LogTemp, Warning, TEXT("TriggeredRun"));

	activateEffect();
	decrementTurnCounter();

}

void AEffectSource::decrementTurnCounter()
{
	TurnsRemaning--;
	if (TurnsRemaning <= 0)
	{
		EndEffect();
	}
}

void AEffectSource::activateEffect()
{
	//UE_LOG(LogTemp, Warning, TEXT("activateEffect"));

	if (activeEffects.Num() > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("activateEffect2 %d"),isDead);
		for (int i = 0; i < activeEffects.Num();i++)
		{
			//UE_LOG(LogTemp, Warning, TEXT("activateEffect3"));
			//UE_LOG(LogTemp, Warning, TEXT("activateEffect 3 %s"), *activeEffects[i]->GetName());
			//UE_LOG(LogTemp, Warning, TEXT("activateEffect4"));
			////UE_LOG(LogTemp, Warning, TEXT("activateEffect 2 %s"),*activeEffects[i]->linkedPawn->GetActorLocation().ToString());
			//DrawDebugPoint(GetWorld(), activeEffects[i]->linkedPawn->GetActorLocation(), 250.f, FColor::Red, false, 500.0f);
			activeEffects[i]->RunEffect();
		}
	}
	
}



void AEffectSource::EndEffect()
{
	UE_LOG(LogTemp, Warning, TEXT("EndEffect"));
	for (int w = activeEffects.Num(); w > 0 ;w--)
	{
		int y = w - 1;
		UE_LOG(LogTemp, Warning, TEXT("EndEffect2"));
		activeEffects[y]->DestructBuffs();
		UE_LOG(LogTemp, Warning, TEXT("EndEffect2.1"));
		activeEffects[y]->linkedPawn->activeEffects.Remove(activeEffects[y]);
		UE_LOG(LogTemp, Warning, TEXT("EndEffect2.1"));
		//activeEffects[w]->ConditionalBeginDestroy();// MarkPendingKill();
		activeEffects[y]->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("EndEffect2.3"));
	}
	activeEffects.Empty();
	//UE_LOG(LogTemp, Warning, TEXT("EndEffect3 = %d"),activeEffects.Num());
	//MarkPendingKill();
	myOwner->activeEffectSources.Remove(this);
	//UE_LOG(LogTemp, Warning, TEXT("EndEffect3.1"));
	this->Destroy();
	//UE_LOG(LogTemp, Warning, TEXT("EndEffect3.2"));
}
