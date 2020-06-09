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
			else if (isDamageing == true)
			{
				inAtTarg->TakeBattleDamage(DamageToDeal);
			}
			if (AbilitysEffect.Num()>0)
			{
				//UE_LOG(LogTemp, Warning, TEXT("passOnEffects"));
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
					else if (isDamageing == true)
					{
						Cast<ABattlePawnBase>(Overlaps[n])->TakeBattleDamage(DamageToDeal);
					}
					targets.Add(Cast<ABattlePawnBase>(Overlaps[n]));
				}
			}
			if (AbilitysEffect.Num() > 0)
			{
				//UE_LOG(LogTemp, Warning, TEXT("passOnEffects"));
				passOnEffects(targets, sourcePawn);
			}
			DamageSphere->DestroyComponent();
			//UE_LOG(LogTemp, Warning, TEXT(" Attack magic 2 %d"), Overlaps.Num());

		}
		if (attackType == EAttackType::aoePartywide)
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
	if (AbilitysEffect.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 9"));
		for (int k = 0;k < AbilitysEffect.Num();k++)
		{
			UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 10"));
			int No = 0;
			for (TObjectIterator<AEffectSource> Itr; Itr; ++Itr)
			{
				No++;
			}
			No += 1;

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 11"));
			AEffectSource* EffectScource = GetWorld()->SpawnActor<AEffectSource>(AbilitysEffect[k], FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);
			UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 12"));
			causeingPawn->activeEffectSources.Add(EffectScource);
			EffectScource->InitialRun(causeingPawn, this);
			UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 12"));

			for (int i = 0; i < inPawns.Num();i++)
			{

				AEffect* Effect = GetWorld()->SpawnActor<AEffect>(EffectScource->EfectToUse, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);
				//UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 2"));

				for (int y = 0; y < inPawns[i]->activeEffects.Num();y++)
				{
					UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 11111111111111111111111111111111111111111111111111111111111111111111111111111"));
					if (inPawns[i]->activeEffects[y]->statToBuff == Effect->statToBuff)
					{
						UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 222222222222222222222222222222222222222222222222222222222222222222222222222222222"));
						inPawns[i]->activeEffects[y]->DestructBuffs();
						UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 3"));
						AEffectSource* SourceToCheck = inPawns[i]->activeEffects[y]->mySource;
						UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 4"));
						SourceToCheck->activeEffects.Remove(inPawns[i]->activeEffects[y]);
						UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 5"));
						inPawns[i]->RemoveEffect(inPawns[i]->activeEffects[y]);
						UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 7"));
						SourceToCheck->CheckIfEffectsRemain();
						UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn 8"));
					}
				}
				EffectScource->activeEffects.Add(Effect);
				inPawns[i]->activeEffects.Add(Effect);
				Effect->InitialRun(EffectScource, inPawns[i], this);
			}
		}
	}
	////////UE_LOG(LogTemp, Warning, TEXT("TestFuntion runn"));

}

