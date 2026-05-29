#include "MyActorComponent.h"

UMyActorComponent::UMyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	_MaxHealth = 100.f;
}


void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	_CurrentHealth = _MaxHealth;
	//신호 받기!!
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UMyActorComponent::DamageTake);
	
}

void UMyActorComponent::DamageTake(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* Causer)
{
	float FinalDamage = FMath::Min(Damage, _CurrentHealth);
	_CurrentHealth -= FinalDamage;

	OnHealthDamaged.Broadcast(_CurrentHealth, _MaxHealth, FinalDamage);
	if (_CurrentHealth == 0.f)
	{
		//신호 주기!!
		OnHealthDead.Broadcast(Instigator);
	}

}


void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// OnHealthDamaged 델리게이트로 UI를 업데이트하므로 매 프레임 출력 불필요
}
