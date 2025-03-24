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
	//������ŵ�����
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player Camera");
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	//1��Ҫ�ý�ɫ���ſ�������ת
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	//2�������ת���������ת
	CameraBoom->bUsePawnControlRotation = true;
	PlayerCamera->bUsePawnControlRotation = true;
	//3��ɫҪ�������˶����������ת
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
}

void APlayerCharacter::Attack()
{
	//UE_LOG(LogTemp, Warning, TEXT("Attack from character"))
	PlayerIsAttacking = true;
	// �ӳ�һ��ʱ������� bIsAttacking����ֹ����״̬һֱ����
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
	// ��ȡ��ǰ����ĵ�һ���������
	if (const ULocalPlayer* Player = (GEngine&&GetWorld())? GEngine->GetFirstGamePlayer(GetWorld()):nullptr)
	{
		// ��ȡ Enhanced Input ��ϵͳ
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		// ��� DefaultMapping ��Ч��������ӵ���ϵͳ��
		if (DefaultMapping)
		{
			//������ӳ����������ӵ���ϵͳ��
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
	FVector2D MoveVector = Value.Get<FVector2D>(); // ��ȡ����ֵ����ά������
	if (Controller) {
		const FRotator Rotation = Controller->GetControlRotation(); // ��ȡ����������ת
		const FRotator YawRotation(0, Rotation.Yaw, 0); // ������ Yaw��ˮƽ��ת��
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // ǰ����
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // ������
		AddMovementInput(ForwardDirection, MoveVector.X); // ǰ���ƶ�
		AddMovementInput(RightDirection, MoveVector.Y); // �����ƶ�
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>(); // ��ȡ����ֵ����ά������
	if (Controller) {
		AddControllerYawInput(-LookVector.X); // ���� Yaw��������ת��
		AddControllerPitchInput(LookVector.Y); // ���� Pitch��������ת��
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
		// �� LookAction �� Look ����
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		// �� MoveAction �� Move ����
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		// �� AttackAction �� Move ����
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
	}
}

