// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestDamageType.h"

UMyTestDamageType::UMyTestDamageType()
{
	//물리적으로 충격을 이만큼 주겠다!!
	DamageImpulse = 5000.0f;
	
	//무게에 따른 밀림을 만들겠다
	bScaleMomentumByMass = true;
	
	//데미지 환경 여부 (낙사,부비트랩,AI가 범인을 찾지 못하게 할 때)
	bCausedByWorld =  true;
}
