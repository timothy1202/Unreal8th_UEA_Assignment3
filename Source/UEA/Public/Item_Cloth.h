// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "TestMyInterface.h"
#include "Item_Cloth.generated.h"

/**
 * 
 */
UCLASS()
class UEA_API AItem_Cloth : public AItemBase, public ITestMyInterface
{
	GENERATED_BODY()
public:
	virtual void OnFireDetected_Implementation(float Temperature, FVector HitLocation) override;
	
protected:
	//겸사겸사 불 파티클 넣을 공간도 만들어주고
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* FireEffect;

};
