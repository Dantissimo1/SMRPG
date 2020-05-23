// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "DamageLibary.h"
#include "BattlePawnBase.h"
#include "EffectSource.h"
#include "Effect.h"
#include "Components/SphereComponent.h"
#include "ParticleHolder.h"


UAbilityBase::UAbilityBase()
{


}

TArray<ABattlePawnBase*> UAbilityBase::AbilitysInstructions(ABattlePawnBase* sourcePawn, ABattlePawnBase* inAtTarg, float inDamageModifier, FDamageTypesToCause inDamageToAdd)
{
	TArray<ABattlePawnBase*> targets;

	if (attackType != EAttackType::NONE)
	{
		if (attackType == EAttackType::singleTarget)
		{


			FDamageTypesToCause DamageToDeal;
			DamageToDeal = WorkOutDamage(inDamageModifier, inDamageToAdd);
			TArray<ABattlePawnBase*> target;
			target.Add(inAtTarg);
			if (isHealing)
			{
				sourcePawn->HealTarget(inAtTarg);
			}
			else
			{
				inAtTarg->TakeBattleDamage(DamageToDeal);
			}
			if (AbilitysEffect != NULL)
			{
				passOnEffects(target, sourcePawn);
			}
		}
		if (attackType == EAttackType::aoeMed)
		{

			FDamageTypesToCause DamageToDeal;

			DamageToDeal = WorkOutDamage(inDamageModifier, inDamageToAdd);

			DamageSphere = NewObject<USphereComponent>(this, TEXT("Damage Sphere"));
			DamageSphere->SetWorldLocation(inAtTarg->GetActorLocation());
			DamageSphere->SetSphereRadius(DamageSphereSize, true);
			DamageSphere->SetGenerateOverlapEvents(true);
			DamageSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			DamageSphere->RegisterComponent();
			DamageSphere->bHiddenInGame = false;
			FVector newLoc = DamageSphere->GetComponentLocation();
			newLoc.Z += 1;
			DamageSphere->SetWorldLocation(newLoc, true);
			TArray<AActor*> Overlaps;
			DamageSphere->GetOverlappingActors(Overlaps);
			for (int n = 0;n < Overlaps.Num();n++)
			{
				if (Cast<ABattlePawnBase>(Overlaps[n]))
				{
					if (isHealing)
					{
						sourcePawn->HealTarget(Cast<ABattlePawnBase>(Overlaps[n]));
					}
					else
					{
						Cast<ABattlePawnBase>(Overlaps[n])->TakeBattleDamage(DamageToDeal);
					}
					targets.Add(Cast<ABattlePawnBase>(Overlaps[n]));
				}
			}
			if (AbilitysEffect != NULL)
			{
				passOnEffects(targets, sourcePawn);
			}

			UE_LOG(LogTemp, Warning, TEXT(" Attack magic 2 %d"), Overlaps.Num());

		}
		if (attackType == EAttackType::aoePartywide)
		{

		}
	}

	if (buffType != EABuffType::NONE)
	{
		if (buffType != EABuffType::selfBuff)
		{
			if (isHealing)
			{
				sourcePawn->HealTarget(sourcePawn);
			}
			TArray<ABattlePawnBase*>pawnsToBuff;
			pawnsToBuff.Add(sourcePawn);
			passOnEffects(pawnsToBuff, sourcePawn);
		}
		if (buffType != EABuffType::singleTarget)
		{
			if (isHealing)
			{
				sourcePawn->HealTarget(inAtTarg);
			}
			TArray<ABattlePawnBase*>pawnsToBuff;
			pawnsToBuff.Add(inAtTarg);
			passOnEffects(pawnsToBuff, sourcePawn);
		}
		if (buffType != EABuffType::aoeMed)
		{
			TArray<ABattlePawnBase*>pawnsToBuff;

			DamageSphere = NewObject<USphereComponent>(this, TEXT("Damage Sphere"));
			DamageSphere->SetWorldLocation(inAtTarg->GetActorLocation());
			DamageSphere->SetSphereRadius(DamageSphereSize, true);
			DamageSphere->SetGenerateOverlapEvents(true);
			DamageSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			DamageSphere->RegisterComponent();
			DamageSphere->bHiddenInGame = false;
			FVector newLoc = DamageSphere->GetComponentLocation();
			newLoc.Z += 1;
			DamageSphere->SetWorldLocation(newLoc, true);
			TArray<AActor*> Overlaps;
			DamageSphere->GetOverlappingActors(Overlaps);

			for (int n = 0;n < Overlaps.Num();n++)
			{
				if (Cast<ABattlePawnBase>(Overlaps[n]))
				{
					if (isHealing)
					{
						sourcePawn->HealTarget(Cast<ABattlePawnBase>(Overlaps[n]));
					}
					pawnsToBuff.Add(Cast<ABattlePawnBase>(Overlaps[n]));
				}
			}
			pawnsToBuff.Add(inAtTarg);
			passOnEffects(pawnsToBuff, sourcePawn);
		}
		if (buffType != EABuffType::aoePartywide)
		{

		}
		if (buffType != EABuffType::selfAOEBuff)
		{

		}
		if (buffType != EABuffType::selfPartyBuff)
		{

		}

	}




	return targets;
}

void UAbilityBase::DoDamage(ABattlePawnBase* inCause, ABattlePawnBase* inAtTarg)
{
}




FDamageTypesToCause UAbilityBase::WorkOutDamage(float inModifier, FDamageTypesToCause inDamageToAdd)
{
	FDamageTypesToCause finalDamage;

	finalDamage.ImpactDamage = (DamageTypes.ImpactDamage * (inModifier))+ inDamageToAdd.ImpactDamage;
	finalDamage.SlashDamage = (DamageTypes.SlashDamage * (inModifier)) + inDamageToAdd.SlashDamage;
	finalDamage.PunctureDamage = (DamageTypes.PunctureDamage * (inModifier))+ inDamageToAdd.PunctureDamage;
	finalDamage.FireDamage = (DamageTypes.FireDamage * (inModifier))+ inDamageToAdd.FireDamage;
	finalDamage.EarthDamage = (DamageTypes.EarthDamage * (inModifier)) + inDamageToAdd.EarthDamage;
	finalDamage.WaterDamage = (DamageTypes.WaterDamage * (inModifier)) + inDamageToAdd.WaterDamage;
	finalDamage.ColdDamage = (DamageTypes.ColdDamage * (inModifier)) + inDamageToAdd.ColdDamage;
	finalDamage.ElectricityDamage = (DamageTypes.ElectricityDamage * (inModifier))+ inDamageToAdd.ElectricityDamage;
	finalDamage.HolyDamage = (DamageTypes.HolyDamage * (inModifier)) + inDamageToAdd.HolyDamage;
	finalDamage.VoidDamage = (DamageTypes.VoidDamage * (inModifier)) + inDamageToAdd . VoidDamage;
	finalDamage.ArcaneDamage = (DamageTypes.ArcaneDamage * (inModifier)) + inDamageToAdd.ArcaneDamage;

	return finalDamage;
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

