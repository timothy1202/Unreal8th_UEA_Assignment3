// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEACharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MyActorComponent.h"
#include "QuestComponent.h"
#include "UEA_HUD.h"
#include "UEAGameMode.h"
#include "HealthBarWidget.h"
#include "QuestWidget.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AUEACharacter::AUEACharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("HealthComponent"));

	// 퀘스트 컴포넌트 생성
	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));
}

void AUEACharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent)
	{
		// 필수 과제 1: OnHealthDamaged → UI 업데이트
		HealthComponent->OnHealthDamaged.AddDynamic(this, &AUEACharacter::HandleHealthDamaged);

		// 필수 과제 2: OnHealthDead → 실제 사망 처리
		HealthComponent->OnHealthDead.AddDynamic(this, &AUEACharacter::HandleActorDead);
	}

	// GameMode에 파티원으로 등록
	if (AUEAGameMode* GameMode = Cast<AUEAGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->RegisterPartyMember(this);
	}

	// 퀘스트 진행도 변경 시 UI 업데이트
	if (QuestComponent)
	{
		QuestComponent->OnQuestProgressChanged.AddDynamic(this, &AUEACharacter::HandleQuestProgressChanged);
		QuestComponent->OnQuestComplete.AddDynamic(this, &AUEACharacter::HandleQuestComplete);
	}
}

void AUEACharacter::HandleHealthDamaged(float NewHealth, float MaxHealth, float HealthChange)
{
	// HUD에서 헬스바 위젯을 가져와 업데이트
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	AUEA_HUD* HUD = Cast<AUEA_HUD>(PC->GetHUD());
	if (!HUD) return;

	if (UHealthBarWidget* HealthBar = HUD->GetHealthBarWidget())
	{
		HealthBar->UpdateHealth(NewHealth, MaxHealth, HealthChange);
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
		FString::Printf(TEXT("HP: %.0f / %.0f (-%0.f)"), NewHealth, MaxHealth, HealthChange));
}

void AUEACharacter::HandleActorDead(AController* InstigatorController)
{
	UE_LOG(LogTemp, Warning, TEXT("[사망] %s 사망!"), *GetName());

	// 입력 비활성화
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->DisableInput(PC);
	}

	// 캡슐 콜리전 비활성화
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 이동 중지
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopMovementImmediately();

	// 래그돌 활성화 - 실제 사망 모습 연출
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->bBlendPhysics = true;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("플레이어 사망!"));
}

void AUEACharacter::HandleQuestProgressChanged(int32 CurrentKills, int32 GoalKills)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	AUEA_HUD* HUD = Cast<AUEA_HUD>(PC->GetHUD());
	if (!HUD) return;

	if (UQuestWidget* QuestUI = HUD->GetQuestWidget())
	{
		QuestUI->UpdateQuestProgress(CurrentKills, GoalKills);
	}
}

void AUEACharacter::HandleQuestComplete()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	AUEA_HUD* HUD = Cast<AUEA_HUD>(PC->GetHUD());
	if (!HUD) return;

	if (UQuestWidget* QuestUI = HUD->GetQuestWidget())
	{
		QuestUI->ShowQuestComplete();
	}
}

void AUEACharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AUEACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUEACharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUEACharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
}

void AUEACharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AUEACharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}