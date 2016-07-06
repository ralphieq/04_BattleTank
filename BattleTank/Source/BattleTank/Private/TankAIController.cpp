// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

// Sets default values
void ATankAIController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	//UE_LOG(LogTemp, Warning, TEXT("AI Controller Tick"));
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Cannot Find Player Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Found Player Tank As ID: %s"), *(PlayerTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)	{ return nullptr; }
	return Cast<ATank>(PlayerPawn);
}