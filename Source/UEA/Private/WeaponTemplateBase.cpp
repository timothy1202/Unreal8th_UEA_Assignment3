// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponTemplateBase.h"

void AWeaponTemplateBase::Fire()
{
	if (!CanFire) return;

	if (CheckAmmo())
	{
		//순서를 여기서 저희 맘대로!!!!!!
		PlayEffects();
		ProcessFiring();
		UpdateAmmo();
		
		Super::Fire();
		return;
	}
}

void AWeaponTemplateBase::Reload_Implementation()
{
	CurrentAmmo = MaxAmmo;
}

bool AWeaponTemplateBase::CheckAmmo_Implementation()
{
	return AmmoPerFire <= CurrentAmmo;
}

void AWeaponTemplateBase::UpdateAmmo_Implementation()
{
	CurrentAmmo -= AmmoPerFire;
}




