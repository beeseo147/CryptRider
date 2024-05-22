// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "ExaminationActor.generated.h"

UCLASS()
class CRYPTRIDER_API AExaminationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExaminationActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent * DefatualtScene;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Gizmo")
	USceneComponent* GizmoScene;
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* Mesh1P;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
