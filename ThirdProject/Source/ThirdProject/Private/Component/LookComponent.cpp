// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/LookComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
ULookComponent::ULookComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool ULookComponent::LineTrace()
{
	if (TargetActor == nullptr) {
		return false;
	}
	FVector Start = GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();
	TArray<const AActor*> IgnoreActors = { GetOwner(), TargetActor };
	if (CanSeeActor(Start, End, IgnoreActors)) {
		FRotator DirectRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
		GetOwner()->SetActorRotation(DirectRotation);
		return true;
	}
	return false;
}

bool ULookComponent::CanSeeActor(FVector Start, FVector End, TArray<const AActor*> IgnoreActors) const
{
	if (TargetActor == nullptr) {
		return false;
	}
	FHitResult Hit;
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	// ignore player and enemy
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(IgnoreActors);
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);
	//GetWorld()->LineTraceMultiByChannel(TArrayResult, Start, End, Channel, QueryParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan);
	return !Hit.bBlockingHit;
}


// Called when the game starts
void ULookComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULookComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bCanSee = LineTrace();
}

