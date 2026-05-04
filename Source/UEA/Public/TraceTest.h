// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TraceTest.generated.h"

UCLASS()
class UEA_API ATraceTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATraceTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void StartAsyncTrace();
	
	void OnAsyncTraceComplete(const FTraceHandle& Handle, FTraceDatum& Data);

};
