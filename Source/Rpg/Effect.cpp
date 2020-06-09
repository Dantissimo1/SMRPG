// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect.h"
#include "BattlePawnBase.h"
#include "EffectSource.h"
#include "DamageLibary.h"
#include "DrawDebugHelpers.h"
#include "AbilityBase.h"
#include "ParticleHolder.h"
#include "Components/ActorComponent.h"



AEffect::AEffect()
{

	
	


}

void AEffect::BeginPlay()
{
	Super::BeginPlay();
}

void AEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AEffect::RunEffect()
{
	//UE_LOG(LogTemp, Warning, TEXT("bluprintOveride"));
	if (bluprintOveride == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("bluprintOveride 2"));
		ActivationOverride();
		//UE_LOG(LogTemp, Warning, TEXT("bluprintOveride 3"));
		return false;
	}

	if (effectType == EEffectType::buff)
	{
		if (buffActivated != true)
		{
			buffActivated = true;
			RunBuffs();
			SpawnParticle();
		}
		
	}
	if (effectType == EEffectType::damage)
	{
		FDamageTypesToCause damageToDeal;
		float damageModifier = 1;
		if (sourceAbility->AttackStyle == EAttackStyle::Melee)
		{
			damageModifier = mySource->myOwner->OfensiveStats.Strength;
		}
		if (sourceAbility->AttackStyle == EAttackStyle::Magic)
		{
			damageModifier = mySource->myOwner->OfensiveStats.ArcaneAptitude;
		}
		if (sourceAbility->AttackStyle == EAttackStyle::Rganged)
		{
			damageModifier = mySource->myOwner->OfensiveStats.RangeFinesse;
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
		//UE_LOG(LogTemp, Warning, TEXT("TakeEffectDamage %d"),mySource->TurnsRemaning);

		SpawnParticle();
		linkedPawn->TakeBattleDamage(damageToDeal);
	}
	if (effectType == EEffectType::healing)
	{
		float healAmount;
		healAmount = ((linkedPawn->mainCharInfo.MaxHealth / 100) * sourceAbility->healPercent) * (mySource->myOwner->OfensiveStats.ArcaneAptitude / 100);

		linkedPawn->ReciveHealing(healAmount);
	}
	if (effectType == EEffectType::shield)
	{

	}

	return false;
}

void AEffect::RunBuffs()
{
	if (statToBuff == EStatToBuff::Strength)
	{
		BuffStrength();
	}
	if (statToBuff == EStatToBuff::ManaRegen)
	{
		BuffManaRegen();
	}
	if (statToBuff == EStatToBuff::RangedStrength)
	{
		BuffRangedStrength();
	}
	if (statToBuff == EStatToBuff::shield)
	{
		BuffShield();
	}
	if (statToBuff == EStatToBuff::Impact)
	{
		BuffImpact();
	}
	if (statToBuff == EStatToBuff::SlashDamage)
	{
		BuffSlashDamage();
	}
	if (statToBuff == EStatToBuff::PunctureDamage)
	{
		BuffPunctureDamage();
	}
	if (statToBuff == EStatToBuff::FireDamage)
	{
		BuffFireDamage();
	}
	if (statToBuff == EStatToBuff::EarthDamage)
	{
		BuffEarthDamage();
	}
	if (statToBuff == EStatToBuff::WaterDamage)
	{
		BuffWaterDamage();
	}
	if (statToBuff == EStatToBuff::ColdDamage)
	{
		BuffColdDamage();
	}
	if (statToBuff == EStatToBuff::ElectricityDamage)
	{
		BuffElectricityDamage();
	}
	if (statToBuff == EStatToBuff::HolyDamage)
	{
		BuffHolyDamage();
	}
	if (statToBuff == EStatToBuff::VoidDamage)
	{
		BuffVoidDamage();
	}
	if (statToBuff == EStatToBuff::ArcaneDamage)
	{
		BuffArcaneDamage();
	}
}

void AEffect::BuffStrength()
{
	//UE_LOG(LogTemp, Warning, TEXT("BuffStrength 1 %f"), linkedPawn->OfensiveStats.Strength);
	amountBuffed = linkedPawn->OfensiveStatsBase.Strength * statMultiplier;
	linkedPawn->OfensiveStats.Strength += amountBuffed;
	//UE_LOG(LogTemp, Warning, TEXT("BuffStrength 2 %f"), linkedPawn->OfensiveStats.Strength);
}

void AEffect::BuffArcaneStrength()
{
	amountBuffed = linkedPawn->OfensiveStatsBase.ArcaneAptitude * statMultiplier;
	linkedPawn->OfensiveStats.ArcaneAptitude += amountBuffed; 
}

void AEffect::BuffManaRegen()
{
	amountBuffed = linkedPawn->OfensiveStatsBase.Strength * statMultiplier;
	linkedPawn->mainCharInfo.ManaRegenRate += amountBuffed;
}

void AEffect::BuffHealthRegen()
{
	amountBuffed = linkedPawn->mainCharInfo.HealthRegenRate * statMultiplier;
	linkedPawn->mainCharInfo.HealthRegenRate += amountBuffed;
}

void AEffect::BuffRangedStrength()
{
	amountBuffed = linkedPawn->OfensiveStatsBase.RangeFinesse * statMultiplier;
	linkedPawn->OfensiveStats.RangeFinesse += amountBuffed;
}

void AEffect::BuffShield()
{
	//linkedPawn->mainCharInfo.ManaRegenRate += amountBuffed = linkedPawn->OfensiveStatsBase.Strength * statMultiplier;
}

void AEffect::BuffImpact()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.ImpactResistance * statMultiplier;
	linkedPawn->DefensiveStats.ImpactResistance += amountBuffed;
}

void AEffect::BuffSlashDamage()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.ImpactResistance * statMultiplier;
	linkedPawn->DefensiveStats.ImpactResistance += amountBuffed;
}

void AEffect::BuffPunctureDamage()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.PunctureResistance * statMultiplier;
	linkedPawn->DefensiveStats.PunctureResistance += amountBuffed;
}

void AEffect::BuffFireDamage()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.FireResistance * statMultiplier;
	linkedPawn->DefensiveStats.FireResistance += amountBuffed;
}

void AEffect::BuffEarthDamage()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.EarthResistance * statMultiplier;
	linkedPawn->DefensiveStats.EarthResistance += amountBuffed;
}

void AEffect::BuffWaterDamage()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.WaterResistance * statMultiplier;
	linkedPawn->DefensiveStats.WaterResistance += amountBuffed;
}

void AEffect::BuffColdDamage()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.ColdResistance * statMultiplier;
	linkedPawn->DefensiveStats.ColdResistance += amountBuffed;
}

void AEffect::BuffElectricityDamage()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.ElectricityResistance * statMultiplier;
	linkedPawn->DefensiveStats.ElectricityResistance += amountBuffed;
}

void AEffect::BuffHolyDamage()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.HolyResistance * statMultiplier;
	linkedPawn->DefensiveStats.HolyResistance += amountBuffed;
}

void AEffect::BuffVoidDamage()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.VoidResistance * statMultiplier;
	linkedPawn->DefensiveStats.VoidResistance += amountBuffed;
}

void AEffect::BuffArcaneDamage()
{
	amountBuffed = linkedPawn->DefensiveStatsBase.ArcaneResistance * statMultiplier;
	linkedPawn->DefensiveStats.ArcaneResistance += amountBuffed;
}

void AEffect::DestructBuffs()
{
	UE_LOG(LogTemp, Warning, TEXT("DestructBuffs 1 %s"),*GetName());
	if (effectType == EEffectType::buff)
	{
		if (statToBuff == EStatToBuff::Strength)
		{
			DeBuffStrength();
		}
		if (statToBuff == EStatToBuff::ManaRegen)
		{
			DeBuffManaRegen();
		}
		if (statToBuff == EStatToBuff::RangedStrength)
		{
			DeBuffRangedStrength();
		}
		if (statToBuff == EStatToBuff::shield)
		{
			DeBuffShield();
		}
		if (statToBuff == EStatToBuff::Impact)
		{
			DeBuffImpact();
		}
		if (statToBuff == EStatToBuff::SlashDamage)
		{
			DeBuffSlashDamage();
		}
		if (statToBuff == EStatToBuff::PunctureDamage)
		{
			DeBuffPunctureDamage();
		}
		if (statToBuff == EStatToBuff::FireDamage)
		{
			DeBuffFireDamage();
		}
		if (statToBuff == EStatToBuff::EarthDamage)
		{
			DeBuffEarthDamage();
		}
		if (statToBuff == EStatToBuff::WaterDamage)
		{
			DeBuffWaterDamage();
		}
		if (statToBuff == EStatToBuff::ColdDamage)
		{
			DeBuffColdDamage();
		}
		if (statToBuff == EStatToBuff::ElectricityDamage)
		{
			DeBuffElectricityDamage();
		}
		if (statToBuff == EStatToBuff::HolyDamage)
		{
			DeBuffHolyDamage();
		}
		if (statToBuff == EStatToBuff::VoidDamage)
		{
			DeBuffVoidDamage();
		}
		if (statToBuff == EStatToBuff::ArcaneDamage)
		{
			DeBuffArcaneDamage();
		}
	}
	
}

void AEffect::DeBuffStrength()
{
	//linkedPawn->OfensiveStats.Strength += amountBuffed;
	linkedPawn->OfensiveStats.Strength = linkedPawn->OfensiveStatsBase.Strength;
}

void AEffect::DeBuffArcaneStrength()
{
	linkedPawn->OfensiveStats.ArcaneAptitude = linkedPawn->OfensiveStatsBase.ArcaneAptitude;
}

void AEffect::DeBuffManaRegen()
{
	linkedPawn->mainCharInfo.ManaRegenRate = linkedPawn->mainCharInfoBase.ManaRegenRate;
}

void AEffect::DeBuffHealthRegen()
{
	linkedPawn->mainCharInfo.HealthRegenRate = linkedPawn->mainCharInfoBase.HealthRegenRate;
}

void AEffect::DeBuffRangedStrength()
{
	linkedPawn->OfensiveStats.RangeFinesse = linkedPawn->OfensiveStatsBase.RangeFinesse;
}

void AEffect::DeBuffShield()
{

}

void AEffect::DeBuffImpact()
{
	linkedPawn->DefensiveStats.ImpactResistance = linkedPawn->DefensiveStatsBase.ImpactResistance;
}

void AEffect::DeBuffSlashDamage()
{
	linkedPawn->DefensiveStats.SlashResistance = linkedPawn->DefensiveStatsBase.SlashResistance;
}

void AEffect::DeBuffPunctureDamage()
{
	linkedPawn->DefensiveStats.PunctureResistance = linkedPawn->DefensiveStatsBase.PunctureResistance;
}

void AEffect::DeBuffFireDamage()
{
	linkedPawn->DefensiveStats.FireResistance = linkedPawn->DefensiveStatsBase.FireResistance;
}

void AEffect::DeBuffEarthDamage()
{
	linkedPawn->DefensiveStats.EarthResistance = linkedPawn->DefensiveStatsBase.EarthResistance;
}

void AEffect::DeBuffWaterDamage()
{
	linkedPawn->DefensiveStats.WaterResistance = linkedPawn->DefensiveStatsBase.WaterResistance;
}

void AEffect::DeBuffColdDamage()
{
	linkedPawn->DefensiveStats.ColdResistance = linkedPawn->DefensiveStatsBase.ColdResistance;
}

void AEffect::DeBuffElectricityDamage()
{
	linkedPawn->DefensiveStats.ElectricityResistance = linkedPawn->DefensiveStatsBase.ElectricityResistance;
}

void AEffect::DeBuffHolyDamage()
{
	linkedPawn->DefensiveStats.HolyResistance = linkedPawn->DefensiveStatsBase.HolyResistance;
}

void AEffect::DeBuffVoidDamage()
{
	linkedPawn->DefensiveStats.VoidResistance = linkedPawn->DefensiveStatsBase.VoidResistance;
}

void AEffect::DeBuffArcaneDamage()
{
	linkedPawn->DefensiveStats.ArcaneResistance = linkedPawn->DefensiveStatsBase.ArcaneResistance;
}

void AEffect::SpawnParticle()
{
	if (SpawnParticleEachRun != true)
	{
		if (ParticleEffect == NULL){}else { return; }
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnedParticle = GetWorld()->SpawnActor<AParticleHolder>(ParticleEffect, linkedPawn->GetActorLocation(), linkedPawn->GetActorRotation(), SpawnParams);
	//UE_LOG(LogTemp, Warning, TEXT("TakeEffectDamage 2 %s"), *GetName());
	spawnedParticle->SetUp(mySource->myOwner);
	spawnedParticle->AttachToActor(linkedPawn, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AEffect::InitialRun(AEffectSource* inSource, ABattlePawnBase* inLinkedPawn, UAbilityBase* inSourceAbility)
{
	mySource = inSource;
	linkedPawn = inLinkedPawn;
	sourceAbility = inSourceAbility;
	//DrawDebugPoint(GetWorld(), linkedPawn->GetActorLocation(), 50.f, FColor::White, false, 5.0f);



}

