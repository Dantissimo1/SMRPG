// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectSource.h"
#include "DamageLibary.h"
#include "Effect.h"
#include "DrawDebugHelpers.h"
#include "BattlePawnBase.h"
#include "AbilityBase.h"


UEffectSource::UEffectSource()
{


}

void UEffectSource::InitialRun(ABattlePawnBase* inOwner, UAbilityBase* inSourceAbility)
{
	myOwner = inOwner;
	TurnsRemaning = lifeInTurns;
	sourceAbility = inSourceAbility;
	UE_LOG(LogTemp, Warning, TEXT("InitialRun"));
	if (effectType == EEffectType::buff)
	{
		activateEffect();
	}
}

void UEffectSource::TriggeredRun()
{
	UE_LOG(LogTemp, Warning, TEXT("TriggeredRun"));
	if (effectType != EEffectType::buff)
	{
		activateEffect();
	}
}

void UEffectSource::decrementTurnCounter()
{
	TurnsRemaning--;
	if (TurnsRemaning <= 0)
	{
		EndEffect();
	}
}

void UEffectSource::activateEffect()
{
	UE_LOG(LogTemp, Warning, TEXT("activateEffect"));
	for (int i = 0; i < activeEffects.Num();i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("activateEffect 2 %s"),*activeEffects[i]->linkedPawn->GetActorLocation().ToString());
		DrawDebugPoint(GetWorld(), activeEffects[i]->linkedPawn->GetActorLocation(), 250.f, FColor::Red, false, 500.0f);
		runEffect(activeEffects[i]);
	}
}

bool UEffectSource::runEffect(UEffect* affectChild)
{
	if (bluprintOveride)
	{
		ActivationOverride();
		return false;
	}

	if (effectType == EEffectType::buff)
	{


	}
	if (effectType == EEffectType::damage)
	{
		FDamageTypesToCause damageToDeal;
		float damageModifier = 1;
		if (sourceAbility->AttackStyle == EAttackStyle::Melee)
		{
			damageModifier = myOwner->OfensiveStats.Strength;
		}
		if (sourceAbility->AttackStyle == EAttackStyle::Magic)
		{
			damageModifier = myOwner->OfensiveStats.ArcaneAptitude;
		}
		if (sourceAbility->AttackStyle == EAttackStyle::Rganged)
		{
			damageModifier = myOwner->OfensiveStats.RangeFinesse;
		}

		damageToDeal.ImpactDamage = sourceAbility->DamageTypes.ImpactDamage * (damageModifier / 100);
		damageToDeal.SlashDamage = sourceAbility->DamageTypes.SlashDamage * (damageModifier / 100);
		damageToDeal.PunctureDamage = sourceAbility->DamageTypes.PunctureDamage * (damageModifier / 100);
		damageToDeal.FireDamage = sourceAbility->DamageTypes.FireDamage * (damageModifier / 100);
		damageToDeal.EarthDamage = sourceAbility->DamageTypes.EarthDamage * (damageModifier / 100);
		damageToDeal.WaterDamage = sourceAbility->DamageTypes.WaterDamage * (damageModifier / 100);
		damageToDeal.ColdDamage = sourceAbility->DamageTypes.ColdDamage * (damageModifier / 100);
		damageToDeal.ElectricityDamage = sourceAbility->DamageTypes.ElectricityDamage * (damageModifier / 100);
		damageToDeal.HolyDamage = sourceAbility->DamageTypes.HolyDamage * (damageModifier / 100);
		damageToDeal.VoidDamage = sourceAbility->DamageTypes.VoidDamage * (damageModifier / 100);
		damageToDeal.ArcaneDamage = sourceAbility->DamageTypes.ArcaneDamage * (damageModifier / 100);
		UE_LOG(LogTemp, Warning, TEXT("TakeEffectDamage"));


		affectChild->linkedPawn->TakeBattleDamage(damageToDeal);
	

	}
	if (effectType == EEffectType::healing)
	{
		float healAmount;
		healAmount = ((affectChild->linkedPawn->mainCharInfo.MaxHealth / 100) * sourceAbility->healPercent) * (myOwner->OfensiveStats.ArcaneAptitude / 100);

		affectChild->linkedPawn->ReciveHealing(healAmount);
	}
	if (effectType == EEffectType::shield)
	{

	}

	return false;
}

void UEffectSource::EndEffect()
{
	for (int w = 0; w < activeEffects.Num();w++)
	{
		activeEffects[w]->MarkPendingKill();
	}
	MarkPendingKill();
}
