// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestComponent.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	KillGoal = 100;
	CurrentKills = 0;
	bQuestComplete = false;
}

void UQuestComponent::AddMonsterKill()
{
	if (bQuestComplete) return;

	CurrentKills = FMath::Min(CurrentKills + 1, KillGoal);

	OnQuestProgressChanged.Broadcast(CurrentKills, KillGoal);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan,
		FString::Printf(TEXT("[퀘스트] 몬스터 처치: %d / %d"), CurrentKills, KillGoal));

	if (CurrentKills >= KillGoal)
	{
		bQuestComplete = true;
		OnQuestComplete.Broadcast();

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
			TEXT("[퀘스트 완료] 몬스터 100마리 처치 달성!"));
	}
}