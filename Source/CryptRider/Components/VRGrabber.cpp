// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VRGrabber.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/VR/VRCharacter.h"

// Sets default values for this component's properties
UVRGrabber::UVRGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AActor* Owner = GetOwner();
	if (!Owner) { return; }
	Owner->GetComponents(UPrimitiveComponent::StaticClass(), OwnerPrimitiveComponents);

	OwnerPremitiveInitTransforms.Reserve(OwnerPrimitiveComponents.Num());
	for (UPrimitiveComponent* It : OwnerPrimitiveComponents)
	{
		OwnerPremitiveInitTransforms.Add(It->GetRelativeTransform());
		//It->SetSimulatePhysics(true);
	}
}
void UVRGrabber::Grab(UMotionControllerComponent* NewMotionControllerComponent)
{
	FDestructorBroadcastDelegate<FOnGrabbed> DestructorCallDelegate(OnGrabbed);

	GrabMotionController = NewMotionControllerComponent;

	AActor* Owner = GetOwner();
	Owner->SetActorEnableCollision(false);

	{
		APawn* PawnOwner = Cast<APawn>(GrabMotionController->GetOwner());
		Owner->SetOwner(PawnOwner);
		Owner->SetInstigator(PawnOwner);
	}

	for (UPrimitiveComponent* It : OwnerPrimitiveComponents)
	{
		It->SetSimulatePhysics(false);
		It->AttachToComponent(GrabMotionController, FAttachmentTransformRules::KeepWorldTransform);
	}

	if (bKeepWorld) { return; }

	const FTransform HandRotationTrnasform = FTransform(FRotator(-90., 0., 0.), FVector::ZeroVector, FVector::OneVector);
	const int32 Num = OwnerPrimitiveComponents.Num();

	const FTransform GrabComponentTransform = GetRelativeTransform();
	const FTransform GrabComponentRotationTransform = FTransform(GrabComponentTransform.GetRotation(),
		FVector::ZeroVector, FVector::OneVector);

	for (int32 i = 0; i < Num; ++i)
	{
		UPrimitiveComponent* It = OwnerPrimitiveComponents[i];
		const FTransform OwnerTransform = OwnerPremitiveInitTransforms[i];

		// GrabComponent의 회전값이 보정된 Transform
		const FTransform GrabComponentRotationAdjustedTransform = UKismetMathLibrary::ComposeTransforms(OwnerTransform, GrabComponentRotationTransform);

		const FTransform GrabComponentRotationAndTranslationAdjustedTransform = FTransform(
			GrabComponentRotationAdjustedTransform.GetRotation(),
			GrabComponentRotationAdjustedTransform.GetLocation() - GrabComponentTransform.GetLocation(),
			GrabComponentRotationAdjustedTransform.GetScale3D());

		FTransform FinalTransform = UKismetMathLibrary::ComposeTransforms(GrabComponentRotationAndTranslationAdjustedTransform, HandRotationTrnasform);
		It->SetRelativeTransform(FinalTransform, false, nullptr, ETeleportType::ResetPhysics);

	}
}

void UVRGrabber::ReleaseGrab()
{
	//OnReleaseGrabbed.Broadcast();

	AActor* Actor = GetOwner();
	Actor->SetActorEnableCollision(true);
	Actor->SetOwner(nullptr);
	Actor->SetInstigator(nullptr);

	for (UPrimitiveComponent* It : OwnerPrimitiveComponents)
	{
		It->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		It->SetSimulatePhysics(true);
	}
}

// Called when the game starts
void UVRGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
// Called every frame
void UVRGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}