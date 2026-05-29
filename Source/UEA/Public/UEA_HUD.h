// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UEA_HUD.generated.h"

class UHealthBarWidget;
class UQuestWidget;

UCLASS()
class UEA_API AUEA_HUD : public AHUD
{
	GENERATED_BODY()

public:
	AUEA_HUD();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	UHealthBarWidget* GetHealthBarWidget() const { return HealthBarWidget; }

	UFUNCTION(BlueprintCallable)
	UQuestWidget* GetQuestWidget() const { return QuestWidget; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHealthBarWidget> HealthBarWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UQuestWidget> QuestWidgetClass;

private:
	UPROPERTY()
	UHealthBarWidget* HealthBarWidget;

	UPROPERTY()
	UQuestWidget* QuestWidget;
};