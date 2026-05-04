// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "FireDamageType.generated.h"

/**
 * 
 */
UCLASS()
class UEA_API UFireDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:
	UFireDamageType();
	
	//화상 지속 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BurnDuration;
	
	//방어구 관통
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ArmorPenetration;
};
