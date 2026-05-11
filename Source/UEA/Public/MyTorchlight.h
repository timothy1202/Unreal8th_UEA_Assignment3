// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTorchlight.generated.h"

UCLASS()
class UEA_API AMyTorchlight : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyTorchlight();
	
	UPROPERTY(EditAnywhere)
	TArray<TWeakObjectPtr<AActor>> Items;
	
protected:
	virtual void BeginPlay() override;

};
