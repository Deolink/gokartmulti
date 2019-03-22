// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY()
	float Throttle;
	UPROPERTY()
	float SteeringThrow;

	UPROPERTY()
	float DeltaTime;

	UPROPERTY()
	float Time;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

	UFUNCTION()
	void SimulateMove(const FGoKartMove& Move);

	FGoKartMove CreateMove(float DeltaTime);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector GetVelocity() { return Velocity; };
	void SetVelocity(FVector Val) { Velocity = Val; };

	void SetThrottle(float Val) { Throttle = Val; };
	void SetSteeringThrow(float Val) { SteeringThrow = Val; };
private:

	FVector GetAirResistance();
	FVector GetRollingResistance();
	void UpdateLocationFromVelocity(float DeltaTime);
	void ApplyRotation(float DeltaTime, float SteeringThrow);

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

	FVector Velocity;

	float Throttle;

	float SteeringThrow;


		
};
