// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnTestActor.h"

// Sets default values
ALockOnTestActor::ALockOnTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("LockOnTarget"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultMaterialAsset(TEXT("/Engine/MapTemplates/Materials/BasicAsset01.BasicAsset01"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> LockOnMaterialAsset(TEXT("/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03"));

	if (DefaultMaterialAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Success to Load Default Material"));
		DefaultMaterial = DefaultMaterialAsset.Object;
		MeshComponent->SetMaterial(0, DefaultMaterialAsset.Object);
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

void ALockOnTestActor::ChangeLockOnMaterial(bool IsLockedOn)
{
	if (IsLockedOn)
	{
		MeshComponent->SetMaterial(0, LockedOnMaterial);

	}
	else
	{
		MeshComponent->SetMaterial(0, DefaultMaterial);
	}
}

