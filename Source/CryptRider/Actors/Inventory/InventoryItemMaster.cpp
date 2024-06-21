// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Inventory/InventoryItemMaster.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Data/Item/ItemData.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/VRGrabber.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/Charter/CryptRiderCharacter.h"
#include "VR/VRCharacter.h"
// Sets default values
AInventoryItemMaster::AInventoryItemMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	Prompt = CreateDefaultSubobject<UWidgetComponent>(TEXT("Prompt"));
	Prompt->SetupAttachment(BaseMesh);
	TSubclassOf<UPickUpPrompt> PickUpPromptClass;
	if (ConstructorHelpers::FClassFinder<UPickUpPrompt> PickUpPromptClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/UI_PickUpPrompt.UI_PickUpPrompt_C'"));
		PickUpPromptClassFinder.Class)
	{
		PickUpPromptClass = PickUpPromptClassFinder.Class;
		Prompt->SetWidgetClass(PickUpPromptClass);
	}
	Prompt->SetVisibility(false);
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(BaseMesh);
	Sphere->SetSphereRadius(220.f);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	//Sphere->SetCollisionResponseToChannel(OverLapALLdY);
	if (GEngine != nullptr)
	{
		const bool bVR = UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled();
		if (bVR)
		{
			if (GEngine != nullptr)
			{
				UVRGrabber* VRGraber = CreateDefaultSubobject<UVRGrabber>(TEXT("VRGraber"));
				if (VRGraber != nullptr)
				{
					VRGraber->SetupAttachment(RootComponent);
				}
				else
				{
					// VRGraber 생성 실패 처리
				}
			}
			else
			{
				// GEngine이 nullptr일 때 처리
			}
		}
	}
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);       // 이 컴포넌트가 무언가에 겹칠 때에 대한 알림 구성
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);       // 이 컴포넌트가 무언가에 겹칠 때에 대한 알림 구성

}

void AInventoryItemMaster::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();

	if (InventoryData.IsNull()) { return; }
	if (InventoryData.RowName == NAME_None) { return; }
	FItemData* Data = InventoryData.GetRow<FItemData>(TEXT(""));
	ensure(Data);
	if (InventoryDataTableRow == Data) { return; }
	InventoryDataTableRow = Data;
	ItemAmount = InventoryDataTableRow->Amount;
}

void AInventoryItemMaster::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();
}

void AInventoryItemMaster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Prompt->SetRelativeLocation(FVector(0, 0, WidgetDistanceAboutMesh), false);
}

// Called when the game starts or when spawned
void AInventoryItemMaster::BeginPlay()
{
	Super::BeginPlay();
}

void AInventoryItemMaster::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	const bool bVR = UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled();

	if (bVR)
	{
		Player = Cast<AVRCharacter>(OtherActor);
	}
	else
	{
		Player = Cast<ACryptRiderCharacter>(OtherActor);
	}
	Prompt->SetVisibility(true);
	UpdateActor = true;
}

void AInventoryItemMaster::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Prompt->SetVisibility(false);
	UpdateActor = false;
	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AInventoryItemMaster::SetInventoryDataTableRow(FItemData* InItemData)
{
	InventoryDataTableRow = InItemData;
}

void AInventoryItemMaster::OnGrab()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn);

	APlayerController* PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
	check(PlayerController);

	bool bBindAction = false;
	if (!InputComponent)
	{
		bBindAction = true;
	}
}

void AInventoryItemMaster::OnReleaseGrab()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn);

	APlayerController* PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
	check(PlayerController);

	DisableInput(PlayerController);
}

// Called every frame
void AInventoryItemMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector BaseMeshLocation = BaseMesh->GetComponentTransform().GetLocation();

	FVector PromptLocation = BaseMeshLocation;
	PromptLocation.Z += InventoryDataTableRow->ExaminationMesh_Offset;
	if (!Player)
	{
		return;
	}
	Prompt->SetWorldLocation(PromptLocation,false,nullptr,ETeleportType::None);
	if (UpdateActor)
	{
		FHitResult HitResult;
		bool Trace = UKismetSystemLibrary::LineTraceSingle(this, GetActorLocation(), Player->GetActorLocation(), ETraceTypeQuery::TraceTypeQuery13, false,
			TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true);
		if (Trace)
		{
			Prompt->SetVisibility(true);
			FRotator PromptRotation = UKismetMathLibrary::FindLookAtRotation(Prompt->GetComponentLocation(), Player->GetActorLocation());
			Prompt->SetWorldRotation(PromptRotation);
			bool CanPickUp = UKismetMathLibrary::VSize(HitResult.TraceStart - HitResult.TraceEnd) <=PickUpDistance ? true : false;
			if (Prompt->GetUserWidgetObject())
			{
				UPickUpPrompt* PickUpPrompt = Cast<UPickUpPrompt>(Prompt->GetUserWidgetObject());
				if (PickUpPrompt)
				{
					PickUpPrompt->TogglePrompt(CanPickUp);
				}
			}
			if (CanPickUp)
			{
				EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			}
			else
			{
				DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			}
		}
		else
		{
			Prompt->SetVisibility(false);
			DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		}
	}

}

