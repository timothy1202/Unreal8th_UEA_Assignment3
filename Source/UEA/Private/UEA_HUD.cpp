// Fill out your copyright notice in the Description page of Project Settings.

#include "UEA_HUD.h"
#include "HealthBarWidget.h"
#include "QuestWidget.h"

AUEA_HUD::AUEA_HUD()
{
	HealthBarWidget = nullptr;
	QuestWidget = nullptr;
}

void AUEA_HUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetOwningPlayerController();
	if (!PC) return;

	if (HealthBarWidgetClass)
	{
		HealthBarWidget = CreateWidget<UHealthBarWidget>(PC, HealthBarWidgetClass);
		if (HealthBarWidget)
		{
			HealthBarWidget->AddToViewport(0);
		}
	}

	if (QuestWidgetClass)
	{
		QuestWidget = CreateWidget<UQuestWidget>(PC, QuestWidgetClass);
		if (QuestWidget)
		{
			QuestWidget->AddToViewport(1);
		}
	}
}