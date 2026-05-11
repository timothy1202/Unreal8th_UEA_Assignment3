#include "MyTorchlight.h"
#include "TestMyInterface.h"
#include "Kismet/KismetSystemLibrary.h"

AMyTorchlight::AMyTorchlight()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyTorchlight::BeginPlay()
{
	Super::BeginPlay();
	
	for (const TWeakObjectPtr<AActor>& Item : Items)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(Item.Get(), UTestMyInterface::StaticClass()))
		{
			ITestMyInterface::Execute_OnFireDetected(Item.Get() ,100.0f, FVector::ZeroVector);
		}
	}
}