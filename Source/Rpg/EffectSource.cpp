// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectSource.h"

UEffectSource::UEffectSource()
{


}

void UEffectSource::InitialRun()
{
}

void UEffectSource::EndEffect()
{
	for (int w = 0; w < activeEffects.Num();w++)
	{
		activeEffects[w]->MarkPendingKill();
	}
	MarkPendingKill();
}
