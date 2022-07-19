// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GUN.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
	Gun=GetWorld()->SpawnActor<AGUN>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}


bool AShooterCharacter::Qdeath() const
{
	return Health <= 0;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Moveright"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	return DamageApplied;


}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}
