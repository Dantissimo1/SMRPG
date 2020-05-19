// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AOEGridBase.generated.h"



class UAOEPoint;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UAOEGridBase : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAOEGridBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
	TArray<UAOEPoint*>medAOEPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
	TArray<UAOEPoint*> PartyWidePoint;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints9;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints11;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints12;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints13;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints14;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints16;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints17;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints18;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		UAOEPoint* smallAOEPoints19;




};
