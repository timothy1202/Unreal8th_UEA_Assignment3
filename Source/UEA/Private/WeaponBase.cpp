// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/ArrowComponent.h"


AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(RootComponent);
	
	AmmoPerFire = 1;
	CurrentAmmo = 0;
	MaxAmmo = 12;
	RoF = 1.f;
	CanFire = true;
	Range = 1000.f;
	DamagePerHit = 100.f;
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmo;
	
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Fire()
{
	CanFire = false;
	GetWorld()->GetTimerManager().SetTimer(TimerFireDelay, this, &AWeaponBase::HandleFireDelay, 1.f/RoF, false);
}

void AWeaponBase::HandleFireDelay()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerFireDelay);
	CanFire = true;
}