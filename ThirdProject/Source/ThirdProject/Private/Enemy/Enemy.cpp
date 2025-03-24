// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include "DrawDebugHelpers.h"
#include "Component/LookComponent.h"
#include "Projectile/BallProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LookComponent = CreateDefaultSubobject<ULookComponent>(TEXT("Look Componet"));
	LookComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	TargetCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookComponent->SetTarget(TargetCharacter);
}

void AEnemy::Fire()
{
	if (BallProjectileClass == nullptr)
	{
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 80.f;
	FVector SpawnLocation = GetActorLocation() + ForwardVector * SpawnDistance;
	//ABallProjectile* Projectile = GetWorld()->SpawnActor<ABallProjectile>(BallProjectileClass, SpawnLocation, GetActorRotation());
	//// 确保子弹生成成功
	//if (Projectile)
	//{
	//	// 获取子弹的 ProjectileMovementComponent
	//	UProjectileMovementComponent* ProjectileMovement = Projectile->GetProjectileMovementComponent();

	//	//if (ProjectileMovement)
	//	//{
	//	//	ProjectileMovement->InitialSpeed = 2300.f;
	//	//	ProjectileMovement->MaxSpeed = 2300.f;
	//	//	ProjectileMovement->Velocity = ForwardVector * 2300.f;
	//	//	UE_LOG(LogTemp, Warning, TEXT("Projectile Speed: %f"), ProjectileMovement->Velocity.Size());
	//	//}

	//}
	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
	ABallProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABallProjectile>(BallProjectileClass, SpawnTransform);
	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2300.f;
	Projectile->FinishSpawning(SpawnTransform);

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//bCanSeePlayer = LineTraceActor(TargetCharacter);

	bCanSeePlayer = LookComponent->CanSeetarget();
	//if (bCanSeePlayer) {
	//	if (cnt % 200 == 0) {
	//		Fire();
	//		cnt = 1;
	//	}
	//	else {
	//		cnt++;
	//	}
	//}
	if (bCanSeePlayer != bPreviousCanSeePlayer) {
		if (bCanSeePlayer) {
			GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AEnemy::Fire, FireInterval, true, FireDelay);
		}
		else {
			GetWorldTimerManager().ClearTimer(FireTimerHandle);
		}
	}
	bPreviousCanSeePlayer = bCanSeePlayer;
}

//bool AEnemy::LineTraceActor(const AActor* TargetActor)
//{
//	if (TargetActor == nullptr) {
//		return false;
//	}
//	FVector Start = GetActorLocation();
//	FVector End = TargetActor->GetActorLocation();
//	if (CanSeeActor(TargetActor, Start, End)) {
//		FRotator DirectRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
//		SetActorRotation(DirectRotation);
//		return true;
//	}
//	return false;
//}
//
//bool AEnemy::CanSeeActor(const AActor* TargetActor, FVector Start, FVector End)
//{
//	if (TargetActor == nullptr) {
//		return false;
//	}
//	FHitResult Hit;
//	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;
//
//	// ignore player and enemy
//	FCollisionQueryParams QueryParams;
//	QueryParams.AddIgnoredActor(this);
//	QueryParams.AddIgnoredActor(TargetActor);
//	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);
//	//GetWorld()->LineTraceMultiByChannel(TArrayResult, Start, End, Channel, QueryParams);
//	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan);
//	return !Hit.bBlockingHit;
//}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

