// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterCharacter.h"
#include "MyActorComponent.h"
#include "UEAGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AMonsterCharacter::AMonsterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("HealthComponent"));
	bIsDead = false;
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent)
	{
		HealthComponent->OnHealthDead.AddDynamic(this, &AMonsterCharacter::HandleMonsterDead);
	}
}

void AMonsterCharacter::HandleMonsterDead(AController* KillerController)
{
	if (bIsDead) return;
	bIsDead = true;

	// 캡슐 콜리전 비활성화
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 래그돌 사망 처리
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->bBlendPhysics = true;

	// GameMode에 몬스터 사망 통지 (파티원 퀘스트 달성도 동기화)
	if (AUEAGameMode* GameMode = Cast<AUEAGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->NotifyMonsterKilled(KillerController);
	}

	// 일정 시간 후 액터 제거
	SetLifeSpan(3.f);
}