// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShooterController.h"

#include "Kismet/GameplayStatics.h"


void AAIShooterController::BeginPlay()
{
    Super::BeginPlay();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    SetFocus(PlayerPawn);
}

void AAIShooterController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    MoveToActor(PlayerPawn, 200);
}

