// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"


class ULookComponent;
class ABallProjectile;

UCLASS()
class THIRDPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	//bool LineTraceActor(const AActor* TargetActor);

	//bool CanSeeActor(const AActor* TargetActor, FVector Start, FVector End);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	TObjectPtr<ULookComponent> LookComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABallProjectile> BallProjectileClass;

	bool bCanSeePlayer = false;

	bool bPreviousCanSeePlayer = false;

	int32 cnt = 0;

	FTimerHandle FireTimerHandle;

	float FireInterval = 3.f;
	float FireDelay = 0.5f;

	void Fire();

private:
	TObjectPtr<ACharacter> TargetCharacter;

	UPROPERTY(EditAnywhere)
	TArray<FHitResult> TArrayResult;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
