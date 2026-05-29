// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UQuestWidget::UpdateQuestProgress(int32 CurrentKills, int32 GoalKills)
{
	if (QuestTitleText)
	{
		QuestTitleText->SetText(FText::FromString(TEXT("[퀘스트] 몬스터 사냥꾼")));
	}

	if (QuestProgressText)
	{
		FString ProgressStr = FString::Printf(TEXT("몬스터 처치: %d / %d"), CurrentKills, GoalKills);
		QuestProgressText->SetText(FText::FromString(ProgressStr));
	}

	if (QuestProgressBar)
	{
		float Ratio = (GoalKills > 0) ? (float)CurrentKills / (float)GoalKills : 0.f;
		QuestProgressBar->SetPercent(FMath::Clamp(Ratio, 0.f, 1.f));
	}
}

void UQuestWidget::ShowQuestComplete()
{
	if (QuestTitleText)
	{
		QuestTitleText->SetText(FText::FromString(TEXT("[퀘스트 완료!] 몬스터 사냥꾼")));
	}

	if (QuestProgressText)
	{
		QuestProgressText->SetText(FText::FromString(TEXT("100마리 처치 완료!")));
	}

	if (QuestProgressBar)
	{
		QuestProgressBar->SetPercent(1.f);
		QuestProgressBar->SetFillColorAndOpacity(FLinearColor::Yellow);
	}
}