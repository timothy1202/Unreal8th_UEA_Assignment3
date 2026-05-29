// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UEAGameMode.generated.h"

class AUEACharacter;

UCLASS(minimalapi)
class AUEAGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUEAGameMode();

	// 몬스터가 사망했을 때 호출 - 파티원 전체 퀘스트 달성도 증가
	UFUNCTION(BlueprintCallable)
	void NotifyMonsterKilled(AController* KillerController);

	// 파티원 등록 (플레이어 참가 시 자동 호출됨)
	void RegisterPartyMember(AUEACharacter* Character);

	// 파티원 해제 (플레이어 사망/퇴장 시)
	void UnregisterPartyMember(AUEACharacter* Character);

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

private:
	// 현재 파티원 목록 (모든 플레이어)
	UPROPERTY()
	TArray<TWeakObjectPtr<AUEACharacter>> PartyMembers;
};