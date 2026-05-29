// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterCharacter.generated.h"

class UMyActorComponent;

UCLASS()
class UEA_API AMonsterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMonsterCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMyActorComponent> HealthComponent;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void HandleMonsterDead(AController* KillerController);

	bool bIsDead;
};