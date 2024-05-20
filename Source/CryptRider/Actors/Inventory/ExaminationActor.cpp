// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Inventory/ExaminationActor.h"

// Sets default values
AExaminationActor::AExaminationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefatualtScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	GizmoScene = CreateDefaultSubobject<USceneComponent>(TEXT("Gizmo"));
	Mesh1P = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));

	RootComponent = DefatualtScene;
	GizmoScene->SetupAttachment(DefatualtScene);
	Mesh1P->SetupAttachment(GizmoScene);
	
}

// Called when the game starts or when spawned
void AExaminationActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExaminationActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	FVector MeshSize = Mesh1P->GetStaticMesh()->GetBounds().GetBox().GetSize();
	GizmoScene->SetRelativeLocation(MeshSize/2);
}

// Called every frame
void AExaminationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

