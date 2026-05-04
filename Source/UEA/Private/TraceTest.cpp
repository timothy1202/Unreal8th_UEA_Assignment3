// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceTest.h"
#include "kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyTestDamageType.h"



// Sets default values
ATraceTest::ATraceTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATraceTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATraceTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StartAsyncTrace();
}

void ATraceTest::StartAsyncTrace()
{
	FTraceDelegate TraceDelegate;
	TraceDelegate.BindUObject(this, &ATraceTest::OnAsyncTraceComplete);
	
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.WorldDynamic = ECR_Overlap;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = false;
	
	GetWorld()->AsyncLineTraceByChannel(
		EAsyncTraceType::Multi,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 1000,
		ECC_Visibility,
		QueryParams,
		ResponseParams,
		&TraceDelegate
	);
}

void ATraceTest::OnAsyncTraceComplete(const FTraceHandle& Handle, FTraceDatum& Data)
{
	for (const FHitResult& Hit : Data.OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("Hit Actor: %s"), *HitActor->GetName()));
		
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 20, 12, FColor::Green, false, 2.f);
		
		UGameplayStatics::ApplyPointDamage(
			HitActor,
			50.0f,
			GetActorForwardVector(),
			Hit,
			GetInstigatorController(),
			this,
			UMyTestDamageType::StaticClass()
		);
	}
}

