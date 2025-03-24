// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));
	//相机附着到杆上
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player Camera");
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	//1不要让角色随着控制器旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	//2相机杆旋转而相机不旋转
	CameraBoom->bUsePawnControlRotation = true;
	PlayerCamera->bUsePawnControlRotation = true;
	//3角色要根据其运动方向进行旋转
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
}

void APlayerCharacter::Attack()
{
	//UE_LOG(LogTemp, Warning, TEXT("Attack from character"))
	PlayerIsAttacking = true;
	// 延迟一段时间后重置 bIsAttacking，防止攻击状态一直开启
	GetWorldTimerManager().SetTimer(AttackResetTimer, this, &APlayerCharacter::ResetAttack, 0.5f, false);
}

void APlayerCharacter::ResetAttack()
{
	PlayerIsAttacking = false;
}
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyBlueprintFunction();
	// 获取当前世界的第一个本地玩家
	if (const ULocalPlayer* Player = (GEngine&&GetWorld())? GEngine->GetFirstGamePlayer(GetWorld()):nullptr)
	{
		// 获取 Enhanced Input 子系统
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		// 如果 DefaultMapping 有效，将其添加到子系统中
		if (DefaultMapping)
		{
			//将输入映射上下文添加到子系统中
			Subsystem->AddMappingContext(DefaultMapping, 0);
		}
	}
}

void APlayerCharacter::CallableFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Callable"));
}

bool APlayerCharacter::PureFunction()
{
	return false;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>(); // 获取输入值（二维向量）
	if (Controller) {
		const FRotator Rotation = Controller->GetControlRotation(); // 获取控制器的旋转
		const FRotator YawRotation(0, Rotation.Yaw, 0); // 仅保留 Yaw（水平旋转）
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 前向方向
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 右向方向
		AddMovementInput(ForwardDirection, MoveVector.X); // 前后移动
		AddMovementInput(RightDirection, MoveVector.Y); // 左右移动
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>(); // 获取输入值（二维向量）
	if (Controller) {
		AddControllerYawInput(-LookVector.X); // 控制 Yaw（左右旋转）
		AddControllerPitchInput(LookVector.Y); // 控制 Pitch（上下旋转）
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		// 绑定 LookAction 到 Look 函数
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		// 绑定 MoveAction 到 Move 函数
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		// 绑定 AttackAction 到 Move 函数
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
	}
}

