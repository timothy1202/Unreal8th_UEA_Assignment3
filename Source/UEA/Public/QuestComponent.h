// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FQuestProgressSignature, int32, CurrentKills, int32, GoalKills);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuestCompleteSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEA_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestComponent();

	// GameMode가 파티원 전체에게 호출 - 몬스터 처치 수 증가
	UFUNCTION(BlueprintCallable)
	void AddMonsterKill();

	UFUNCTION(BlueprintPure)
	int32 GetCurrentKills() const { return CurrentKills; }

	UFUNCTION(BlueprintPure)
	int32 GetKillGoal() const { return KillGoal; }

	UFUNCTION(BlueprintPure)
	bool IsQuestComplete() const { return bQuestComplete; }

	// UI 업데이트용 델리게이트
	UPROPERTY(BlueprintAssignable)
	FQuestProgressSignature OnQuestProgressChanged;

	UPROPERTY(BlueprintAssignable)
	FQuestCompleteSignature OnQuestComplete;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	int32 KillGoal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	int32 CurrentKills;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	bool bQuestComplete;
};