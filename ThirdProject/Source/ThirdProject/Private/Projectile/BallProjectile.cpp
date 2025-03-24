// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BallProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ThirdProject/ThirdProjectCharacter.h"

// Sets default values
ABallProjectile::ABallProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SphereComponent->SetSphereRadius(35.f);
	//SphereComponent->SetCollisionProfileName("Ball");
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true); 

	SphereComponent->OnComponentHit.AddDynamic(this, &ABallProjectile::OnHit);
	//SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABallProjectile::OnBeginOverlap);


	SetRootComponent(SphereComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovement->InitialSpeed = 2300.f;



}

// Called when the game starts or when spawned
void ABallProjectile::BeginPlay()
{
	Super::BeginPlay();

	//if (ProjectileMesh)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("ProjectileMesh Speed:"));

	//	// 确保物理模拟已启用
	//	ProjectileMesh->SetSimulatePhysics(true);

	//	// 设定线性速度
	//	FVector LaunchVelocity = GetActorForwardVector() * 2300.f;
	//	ProjectileMesh->SetAllPhysicsLinearVelocity(LaunchVelocity);
	//}

	SetLifeSpan(4.f); 

}

// Called every frame
void ABallProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//UE_LOG(LogTemp, Warning, TEXT("InitialSpeed: %f"), ProjectileMovement->InitialSpeed);
	//FVector CurrentVelocity = ProjectileMovement->Velocity;
	//UE_LOG(LogTemp, Warning, TEXT("velocity: %s"), *CurrentVelocity.ToString());

}

void ABallProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hit Component: %s, OtherActor: %s"), *HitComponent->GetOwner()->GetName(), *OtherActor->GetName());
	AThirdProjectCharacter* Player = Cast<AThirdProjectCharacter>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Player!"));
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit something else: %s"), *OtherActor->GetName());
	}
}
//void ABallProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
//	const FHitResult& SweepResult)
//{
//	AThirdProjectCharacter* Player = Cast<AThirdProjectCharacter>(OtherActor);
//	if (Player)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Overlap with Player!"));
//		Destroy();
//	}
//}

