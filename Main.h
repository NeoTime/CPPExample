// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"


UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),

	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName= "ExhaustedRecovering"),

	ESS_MAX UMETA(DisplayName = "DefaultMax")


};

UCLASS()
class ROBOTTIME_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status;  }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;

	// set movement status and running speed
	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintingSpeed;

	bool bShiftKeyDown;

	// press down for sprinting
	void ShiftKeyDown();

	// release to stop sprinting
	void ShiftKeyUp();

	// Camera Boom positioning behind the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAcess = "true"))
	class USpringArmComponent* CameraBoom;

	// Follow Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAcess = "true"))
	class UCameraComponent* FollowCamera;

	// Base turn rates to scale turning functions for the camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/**   
	/* Player STATS
	/*
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Gears;

	void DecrementHealth(float Amount);

	void IncrementGears(int32 Amount);

	void Die();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called forwards/backwards input 
	void MoveForward(float Value);

	// Called for side to side input
	void MoveRight(float Value);

	// call via input to turn at given rate @param rate 1.0 = 100%
	void TurnAtRate(float Rate);

	// look up and down at given rate @param rate 1.0 = 100%
	void LookUpAtRate(float Rate);

	bool bLMBDown;
	void LMBDown();
	void LMBUp();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	class AWeapon* EpuippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	class APickup* ActiveOverlappingItem;

	FORCEINLINE void SetEquippedWeapon(AWeapon* WeaponToSet) { EpuippedWeapon = WeaponToSet; }
	FORCEINLINE void SetActiveOverlappingItem(APickup* Pickup) { ActiveOverlappingItem = Pickup; }

};


