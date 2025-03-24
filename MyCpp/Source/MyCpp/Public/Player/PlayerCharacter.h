// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class MYCPP_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void Attack();

	UFUNCTION(BlueprintCallable, Category = "Action")
	void ResetAttack();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	bool PlayerIsAttacking = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// UFUNCTION TEST 
	UFUNCTION(BlueprintCallable)
	void CallableFunction();
	UFUNCTION(BlueprintPure)
	bool PureFunction();

	//BlueprintImplementableEvent
	UFUNCTION(BlueprintImplementableEvent)
	void MyBlueprintFunction();

	// UPROPERTY TEST
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "U|test")
	float testLen;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCamera;

	// UPROPERTY TEST
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "U|test", meta = (AllowPrivateAccess = "true"))
	float privateLen;

	// Input
	// ����һ�� UInputMappingContext ���͵�ָ�룬���ڴ洢����ӳ�������ġ�
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMapping;
	// ����һ�� UInputAction ���͵�ָ�룬���ڴ洢�ƶ����붯����
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	// ����һ�� UInputAction ���͵�ָ�룬���ڴ洢�ӽ����붯����
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	// ����һ�� UInputAction ���͵�ָ�룬���ڴ洢�������붯����
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(EditDefaultsOnly, Category = "Timer")
	FTimerHandle AttackResetTimer;  // �����Ƕ�ʱ������


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
