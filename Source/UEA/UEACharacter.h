// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "UEACharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UMyActorComponent;
class UQuestComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AUEACharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AUEACharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMyActorComponent> HealthComponent;

	// 퀘스트 컴포넌트 - 100마리 몬스터 처치 퀘스트 추적
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UQuestComponent> QuestComponent;

	virtual void BeginPlay() override;

	// OnHealthDamaged 델리게이트 콜백 - UI 업데이트
	UFUNCTION()
	void HandleHealthDamaged(float NewHealth, float MaxHealth, float HealthChange);

	// OnHealthDead 델리게이트 콜백 - 실제 사망 처리
	UFUNCTION()
	void HandleActorDead(AController* InstigatorController);

	// 퀘스트 진행도 변경 콜백 - 퀘스트 UI 업데이트
	UFUNCTION()
	void HandleQuestProgressChanged(int32 CurrentKills, int32 GoalKills);

	// 퀘스트 완료 콜백
	UFUNCTION()
	void HandleQuestComplete();

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};