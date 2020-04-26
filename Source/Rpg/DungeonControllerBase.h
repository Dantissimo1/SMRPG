// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonControllerBase.generated.h"


class ADungeonCharacterBase;
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

	///////Movement
	void ForwardsInput(float Value);
	void HorizontalInput(float Value);
	void JumpInput();

	/////Camera
	void CameraYawInput(float Value);
	void CameraPitchInput(float Value);
	void ScrollInput(float Value);
	
};
