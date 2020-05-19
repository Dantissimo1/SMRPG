// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEGridBase.h"
#include "AOEPoint.h"



// Sets default values for this component's properties
UAOEGridBase::UAOEGridBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
		
	smallAOEPoints1 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 1"));
	smallAOEPoints2 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 2"));
	smallAOEPoints3 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 3"));
	smallAOEPoints4 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 4"));
	smallAOEPoints5 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 5"));
	smallAOEPoints6 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 6"));
	smallAOEPoints7 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 7"));
	smallAOEPoints8 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 8"));
	smallAOEPoints9 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 9"));
	smallAOEPoints10 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 10"));
	smallAOEPoints11 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 11"));
	smallAOEPoints12 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 12"));
	smallAOEPoints13 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 13"));
	smallAOEPoints14 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 14"));
	smallAOEPoints15 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 15"));
	smallAOEPoints16 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 16"));
	smallAOEPoints17 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 17"));
	smallAOEPoints18 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 18"));
	smallAOEPoints19 = CreateDefaultSubobject<UAOEPoint>(TEXT("Small AOE Point 19"));


	// ...
}


// Called when the game starts
void UAOEGridBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAOEGridBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

