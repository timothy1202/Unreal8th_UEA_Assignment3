// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEAGameMode.h"
#include "UEACharacter.h"
#include "UEA_HUD.h"
#include "QuestComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"

AUEAGameMode::AUEAGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// HUD 클래스를 C++에서 직접 지정 (블루프린트 편집 없이 동작)
	HUDClass = AUEA_HUD::StaticClass();
}

void AUEAGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	// 파티 등록은 캐릭터 BeginPlay에서 처리 (폰 스폰 타이밍 보장)
}

void AUEAGameMode::Logout(AController* Exiting)
{
	if (APlayerController* PC = Cast<APlayerController>(Exiting))
	{
		if (AUEACharacter* Character = Cast<AUEACharacter>(PC->GetPawn()))
		{
			UnregisterPartyMember(Character);
		}
	}

	Super::Logout(Exiting);
}

void AUEAGameMode::RegisterPartyMember(AUEACharacter* Character)
{
	if (!Character) return;

	PartyMembers.AddUnique(TWeakObjectPtr<AUEACharacter>(Character));

	UE_LOG(LogTemp, Log, TEXT("[파티] %s 파티 합류. 현재 파티원: %d명"), *Character->GetName(), PartyMembers.Num());
}

void AUEAGameMode::UnregisterPartyMember(AUEACharacter* Character)
{
	if (!Character) return;

	PartyMembers.RemoveAll([Character](const TWeakObjectPtr<AUEACharacter>& Member)
	{
		return Member.Get() == Character;
	});
}

void AUEAGameMode::NotifyMonsterKilled(AController* KillerController)
{
	// 파티원 전체에게 몬스터 처치 카운트 증가
	for (TWeakObjectPtr<AUEACharacter>& MemberPtr : PartyMembers)
	{
		AUEACharacter* Member = MemberPtr.Get();
		if (!Member) continue;

		if (UQuestComponent* Quest = Member->FindComponentByClass<UQuestComponent>())
		{
			Quest->AddMonsterKill();
		}
	}

	// 파티원이 없을 때 킬러 본인에게 직접 적용 (싱글 플레이어 fallback)
	if (PartyMembers.Num() == 0 && KillerController)
	{
		if (AUEACharacter* KillerCharacter = Cast<AUEACharacter>(KillerController->GetPawn()))
		{
			if (UQuestComponent* Quest = KillerCharacter->FindComponentByClass<UQuestComponent>())
			{
				Quest->AddMonsterKill();
			}
		}
	}
}