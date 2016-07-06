// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Not Possesing Tank"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Controlling Tank %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	AimTowardsChrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Player Controller Tick"));
}

void ATankPlayerController::AimTowardsChrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location %s"), *HitLocation.ToString());

		// TODO tell tank to aim at this location
	}
}
// Get location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetHitVectorLookLocation(LookDirection, HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction %s"), *LookDirection.ToString());
	}
	return true;
}

bool ATankPlayerController::GetHitVectorLookLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.ToString());  // Identify What Was Hit
	}
	return false;

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

