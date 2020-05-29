// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect.h"
#include "BattlePawnBase.h"
#include "EffectSource.h"
#include "DamageLibary.h"
#include "DrawDebugHelpers.h"


UEffect::UEffect()
{





}


void UEffect::InitialRun(UEffectSource* inSource, ABattlePawnBase* inLinkedPawn)
{
	mySource = inSource;
	linkedPawn = inLinkedPawn;
	DrawDebugPoint(GetWorld(), linkedPawn->GetActorLocation(), 50.f, FColor::White, false, 5.0f);
}

bool UEffect::RunEffect()
{
	return false;
}
