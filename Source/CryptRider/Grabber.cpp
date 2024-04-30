// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhsicsHandle();

	if (PhysicsHandle == nullptr)
	{
		return;
	}
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

UPhysicsHandleComponent* UGrabber::GetPhsicsHandle()
{
	UPhysicsHandleComponent* Result=GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!Result)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent"));
	}
	return Result;
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhsicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhsicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}
	FHitResult HitReuslt;
	if (GetGrabbableInReach(HitReuslt))
	{
		UPrimitiveComponent* HitComponent = HitReuslt.GetComponent();
		HitComponent->WakeAllRigidBodies();

		//DrawDebugSphere(GetWorld(), HitReuslt.ImpactPoint, 10, 10, FColor::Blue, false, 5);

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent, NAME_None, HitReuslt.ImpactPoint,
			GetComponentRotation()
		);
	}

}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult)const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

}

