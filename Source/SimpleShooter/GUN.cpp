// Fill out your copyright notice in the Description page of Project Settings.


#include "GUN.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGUN::AGUN()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);


	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGUN::PullTrigger()
{
	//UE_LOG(LogTemp, Warning, TEXT("Pew!"));
	UGameplayStatics::SpawnEmitterAttached(MuzzelFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector()* MaxRange;

	FHitResult Hit;
	bool bSuccess= GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);
	if (bSuccess)
	{
		FVector ShotDirection = Rotation.Vector();
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
	
	
}

// Called when the game starts or when spawned
void AGUN::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGUN::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

