// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "DamageLibary.h"
#include "BattlePawnBase.h"
#include "EffectSource.h"
#include "Effect.h"
#include "Components/SphereComponent.h"



UAbilityBase::UAbilityBase()
{


}

TArray<ABattlePawnBase*> UAbilityBase::AbilitysInstructions(ABattlePawnBase* sourcePawn, ABattlePawnBase* inAtTarg)
{
	TArray<ABattlePawnBase*> targets;


	if (attackType == EAttackType::singleTarget)
	{
		targets.Add(inAtTarg);
	}
	if (attackType == EAttackType::aoeMed)
	{
		DamageSphere = NewObject<USphereComponent>(this, TEXT("Damage Sphere"));
		DamageSphere->SetWorldLocation(inAtTarg->GetActorLocation());
		DamageSphere->SetSphereRadius(DamageSphereSize, true);
		DamageSphere->SetGenerateOverlapEvents(true);
		DamageSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		DamageSphere->RegisterComponent();
		DamageSphere->bHiddenInGame = false;
		FVector newLoc= DamageSphere->GetComponentLocation();
		newLoc.Z += 1;
		DamageSphere->SetWorldLocation(newLoc, true);
		TArray<AActor*> Overlaps;
		DamageSphere->GetOverlappingActors(Overlaps);
		for (int n = 0;n < Overlaps.Num();n++)
		{
			if (Cast<ABattlePawnBase>(Overlaps[n]))
			{
				targets.Add(Cast<ABattlePawnBase>(Overlaps[n]));
			}
		}


		UE_LOG(LogTemp, Warning, TEXT(" Attack magic 2 %d"),Overlaps.Num());

	}
	if (attackType == EAttackType::aoePartywide)
	{


	}

	if (attackType == EAttackType::AttackselfBuff)
	{
		TArray<ABattlePawnBase*>effectTarg;
		effectTarg.Add(sourcePawn);
		passOnEffects(effectTarg, sourcePawn);
		targets.Add(inAtTarg);
	}
	else
	{

		passOnEffects(targets, sourcePawn);
	}

	return targets;
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
		EffectScource->InitialRun();
	}
	//////UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn"));

}

