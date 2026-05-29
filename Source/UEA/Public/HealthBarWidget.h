// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class UEA_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// OnHealthDamaged 델리게이트 시그니처와 동일한 파라미터
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float NewHealth, float MaxHealth, float HealthChange);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthText;
};