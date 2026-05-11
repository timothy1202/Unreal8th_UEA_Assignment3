// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Wood.h"
#include "Kismet/GameplayStatics.h" // 스폰 함수 사용을 위해 필수
#include "Particles/ParticleSystem.h" //파티클 시스템 헤더

void AItem_Wood::OnFireDetected_Implementation(float Temperature, FVector HitLocation)
{
	if (FireEffect)
	{
		// 1. 특정 위치에 고정으로 스폰할 때 (Spawn Emitter at Location)
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			FireEffect,
			GetActorLocation(),
			GetActorRotation(),
			FVector(1.0f) // 스케일
		);
	}
}