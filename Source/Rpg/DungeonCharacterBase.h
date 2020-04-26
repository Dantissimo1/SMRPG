// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"



#include "DungeonCharacterBase.generated.h"


class USpringarmComponent;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class RPG_API ADungeonCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADungeonCharacterBase();


	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UWorld* World;





	///////Movement
	void ForwardsInput(float Value);
	void HorizontalInput(float Value);

	/////Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float MaxCamDistance = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float MinCamDistance = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CamScrollSpeed = 2000;

	void CameraYawInput(float Value);
	void CameraPitchInput(float Value);
	void ClampCameraPitch();
	void ScrollCamera(float Value);





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
