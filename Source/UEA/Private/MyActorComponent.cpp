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
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UMyActorComponent::DamageTake);

	// 게임 시작 시 초기 HP를 UI에 전달 (1프레임 뒤에 방송해야 위젯이 준비됨)
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		OnHealthDamaged.Broadcast(_CurrentHealth, _MaxHealth, 0.f);
	});
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
