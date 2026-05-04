// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponTemplateBase.generated.h"

/**
 * 
 */
UCLASS()
class UEA_API AWeaponTemplateBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	virtual void Fire() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();

protected:
	UFUNCTION(BlueprintNativeEvent) //하이브리드형
	bool CheckAmmo();
	
	//총을 어떻게 쏠지
	UFUNCTION(BlueprintImplementableEvent) //블루프린트로 위임 해줘서 cpp에서 구현하면 안된다.
	void ProcessFiring();
	
	//이펙트 실행
	UFUNCTION(BlueprintImplementableEvent)
	void PlayEffects();
	
	//총알 업데이트
	UFUNCTION(BlueprintNativeEvent)
	void UpdateAmmo();
};
