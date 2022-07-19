// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GUN.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGUN : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGUN();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzelFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	float MaxRange = 5000;
	UPROPERTY(EditAnywhere)
	float Damage = 10;
};
