// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Gun.h"

// Sets default values
ABP_Gun::ABP_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABP_Gun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABP_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

