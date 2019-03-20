// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class KRAZYKARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private:
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveForward(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveRight(float Value);

	
	void MoveForward(float Value);	
	void MoveRight(float Value);

	FVector GetAirResistance();
	FVector GetRollingResistance();
	void UpdateLocationFromVelocity(float DeltaTime);
	void ApplyRotation(float DeltaTime);

	// The mass of the car (kg).
	UPROPERTY(EditAnywhere)
	float Mass = 1000;

	// The force applied to the car when throttle is fully down (N).
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000;

	// The number of degrees rotated per second at full control throw (degrees/s)
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 90;

	// Minimum radius of the car turning circle at full lock (m)
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 10;

	// Higher means more drag (kg/s)
	UPROPERTY(EditAnywhere)
	float DragCoeficient = 16;

	// Higher means more rolling resistance (kg/s)
	UPROPERTY(EditAnywhere)
	float RollingResistanceCoeficient = 0.015;


	UPROPERTY(Replicated)
	FVector Velocity;

	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedTransform)
	FTransform ReplicatedTransform;

	UFUNCTION()
	void OnRep_ReplicatedTransform();

	UPROPERTY(Replicated)
	float Throttle;
	UPROPERTY(Replicated)
	float SteeringThrow;
};
