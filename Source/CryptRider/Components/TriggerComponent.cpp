// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "Components/PrimitiveComponent.h"
UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Trigger Component Alive"));

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor !=nullptr)
	{
		//UnLock
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
		// Actor를 부모 컴포넌트에 부착합니다.
		Actor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		// Actor의 월드 좌표계 기준 위치를 설정합니다.
		Actor->SetActorRelativeLocation(FVector(), false);

		// Actor의 월드 좌표계 기준 회전을 설정합니다.
		Actor->SetActorRotation(FRotator(this->GetComponentRotation()), ETeleportType::TeleportPhysics);
		
		Mover->SetbShouldMove(true);

		
	}
	else
	{
		//ReLock
		Mover->SetbShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*>Actors;
	GetOverlappingActors(Actors);

	for (auto Actor : Actors)
	{
		bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if (Actor->ActorHasTag(AcceptableActorTag)&& !Actor->ActorHasTag("Grabbed"))
		{
			return Actor;
		}

	}
	return nullptr;
}

