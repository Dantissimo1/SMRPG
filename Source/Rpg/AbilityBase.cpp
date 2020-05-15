// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "DamageLibary.h"
#include "BattlePawnBase.h"
#include "EffectSource.h"
#include "Effect.h"

UAbilityBase::UAbilityBase()
{


}

void UAbilityBase::AbilitysInstructions()
{

}


void UAbilityBase::passOnEffects(ABattlePawnBase* inPawn, ABattlePawnBase* causeingPawn)
{
	if (AbilitysEffect != NULL)
	{
		UEffectSource* EffectScource = NewObject<UEffectSource>(AbilitysEffect->StaticClass(), TEXT("Effect Source"));
		causeingPawn->activeEffectSources.Add(EffectScource);

		UEffect* Effect = NewObject<UEffect>(Effect->StaticClass(), TEXT("Effect"));
		EffectScource->activeEffects.Add(Effect);
		inPawn->activeEffects.Add(Effect);
		

	}
	////UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn"));

}

void UAbilityBase::passOnEffects(TArray<ABattlePawnBase*> inPawns, ABattlePawnBase* causeingPawn)
{
	if (AbilitysEffect != NULL)
	{
		UEffectSource* EffectScource = NewObject<UEffectSource>(AbilitysEffect->StaticClass() , TEXT("Effect Source"));
		causeingPawn->activeEffectSources.Add(EffectScource);
		for (int i = 0; i < inPawns.Num();i++)
		{
			UEffect* Effect = NewObject<UEffect>(Effect->StaticClass(), TEXT("Effect"));
			EffectScource->activeEffects.Add(Effect);
			inPawns[i]->activeEffects.Add(Effect);
		}

	}
	////UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn"));

}

void UAbilityBase::passOnEffects(FVector* Location, ABattlePawnBase* causeingPawn)
{



}
