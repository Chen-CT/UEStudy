// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LookComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPROJECT_API ULookComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULookComponent();

	bool LineTrace();
	bool CanSeeActor(FVector Start, FVector End, TArray<const AActor* >IgnoreActors) const;
	TObjectPtr<const AActor> TargetActor;
	bool bCanSee = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//get
	FORCEINLINE void SetTarget(AActor* NewTarget) { TargetActor = NewTarget; }
	//return
	FORCEINLINE bool CanSeetarget() { return bCanSee; }

		
};
