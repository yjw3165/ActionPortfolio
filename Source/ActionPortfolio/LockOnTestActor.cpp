// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnTestActor.h"

// Sets default values
ALockOnTestActor::ALockOnTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//씬 추가.
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(SceneRoot);

	LockOnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LockOnPoint"));
	LockOnPoint->SetupAttachment(SceneRoot);
	LockOnPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockOnPointMesh"));
	LockOnPointMesh->SetupAttachment(LockOnPoint);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultMaterialAsset(TEXT("/Engine/MapTemplates/Materials/BasicAsset01.BasicAsset01"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> LockOnMaterialAsset(TEXT("/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03"));

	if (DefaultMaterialAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Success to Load Default Material"));
		DefaultMaterial = DefaultMaterialAsset.Object;
		SkeletalMeshComponent->SetMaterial(0, DefaultMaterialAsset.Object);
	}

	if (LockOnMaterialAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Succedd to Load LockedOn Material"));
		LockedOnMaterial = LockOnMaterialAsset.Object;

	}
}

// Called when the game starts or when spawned
void ALockOnTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALockOnTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALockOnTestActor::OnLockedOn_Implementation()
{
	ChangeLockOnMaterial(true);
}

void ALockOnTestActor::OnLockReleased_Implementation()
{
	ChangeLockOnMaterial(false);
}

FVector ALockOnTestActor::GetLockOnPointLocation_Implementation() const
{
	return LockOnPoint->GetComponentLocation();
}

void ALockOnTestActor::ChangeLockOnMaterial(bool IsLockedOn)
{
	if (IsLockedOn)
	{
		SkeletalMeshComponent->SetMaterial(0, LockedOnMaterial);

	}
	else
	{
		SkeletalMeshComponent->SetMaterial(0, DefaultMaterial);
	}
}

