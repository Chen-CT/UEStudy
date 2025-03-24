// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacter.h"
#include "Warrior.generated.h"

/**
 * 
 */
UCLASS()
class MYCPP_API AWarrior : public APlayerCharacter
{
	GENERATED_BODY()
public:
	virtual void Attack() override;
	
};
