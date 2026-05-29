// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class UEA_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateQuestProgress(int32 CurrentKills, int32 GoalKills);

	UFUNCTION(BlueprintCallable)
	void ShowQuestComplete();

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestTitleText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestProgressText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* QuestProgressBar;
};