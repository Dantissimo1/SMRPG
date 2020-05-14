// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonControllerBase.generated.h"


class ADungeonCharacterBase;
class EncounterVolumeBase;
class ABattleZoneBase;
class UPlayerPartyComp;
class UCharacterDataSheet;
class UDungeonHUD;
class UBattleHUD;


/**
 * 
 */
UCLASS()
class RPG_API ADungeonControllerBase : public APlayerController
{
	GENERATED_BODY()

	ADungeonControllerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	ADungeonCharacterBase* MyChar;

	//////players party Detials
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	class UPlayerPartyComponent* PlayersParty;


	////balte mode speific things
	UPROPERTY()
	bool bIsInBattleMode = false;
	ABattleZoneBase* CurrentBattleArea;
	void BeginBattle(ABattleZoneBase* InBattleZone);
	void EndBattle();



	/////////////////////////////////////////inputs for all modes///////////////////
	///////Movement
	void ForwardsInput(float Value);
	void HorizontalInput(float Value);
	void JumpInput();

	/////Camera
	void CameraYawInput(float Value);
	void CameraPitchInput(float Value);
	void ScrollInput(float Value);
	





	////////////////////////HUD/////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		TSubclassOf< UDungeonHUD> DungeonHUDClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		TSubclassOf< UBattleHUD> BattleHUDClass;


	void SpawnDungeonHUD();
	void ToggleDungeonHUD(bool hudOn);
	void BattleHUDSpawn();
	void BattleHUDDespawn();

	UDungeonHUD* DungeonHUD;
	UBattleHUD* BattleHUD;


};
