// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Generated files must be last on the includes

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float Deltatime) override;
	void AimTowardsChrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetHitVectorLookLocation(FVector LookDirection, FVector& HitLocation) const;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = .5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = .33333;

};
