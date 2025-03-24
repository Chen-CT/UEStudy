// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/PlayerAnim.h"
#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner()); 
	if (PlayerCharacter) {
		PlayerCharacterMovement = PlayerCharacter->GetCharacterMovement();
		bIsAttacking = false;
	}
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (PlayerCharacterMovement) {


		Speed = UKismetMathLibrary::VSizeXY(PlayerCharacterMovement->Velocity);
		bIsAttacking = PlayerCharacter->PlayerIsAttacking;
		if (bIsAttacking)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attacking: TRUE"));
		}
	}
}
