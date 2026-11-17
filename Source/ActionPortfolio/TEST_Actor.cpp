// Fill out your copyright notice in the Description page of Project Settings.


#include "TEST_Actor.h"



// Sets default values
ATEST_Actor::ATEST_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LockOn = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOn"));
}

// Called when the game starts or when spawned
void ATEST_Actor::BeginPlay()
{
	Super::BeginPlay();

	//GetWorldTimerManager().SetTimer(LogTimerHandle, this, &ATEST_Actor::LogTargets, 1.0f, true);
	//ObjectPtr_TEST->OnDestroyed.AddDynamic(this, &ATEST_Actor::HandleTargetDestroyed);
	//LockOn->SetTarget(nullptr);
	//LockOn->SetTarget(ObjectPtr_TEST_A);
	//LockOn->SetTarget(ObjectPtr_TEST_A);
	//LockOn->SetTarget(nullptr);
	//LockOn->SetTarget(ObjectPtr_TEST_B);

}

// Called every frame
void ATEST_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATEST_Actor::LogTargets()
{
	//OnTimerTick.Broadcast();

	//if (IsValid(ObjectPtr_TEST))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("StrongPtr_IS_VALID_Timer"));
	//}
	//else if (!IsValid(ObjectPtr_TEST))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("StrongPtr_IS_NOT_VALID_Timer"));
	//}

	//if (WeakObjectPtr_TEST.IsValid())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("WeakPtr_Is_Valid_Timer"));
	//}
	//else if (!WeakObjectPtr_TEST.IsValid())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("WeakPtr_is_Not_Valid_Timer"));
	//}
}

void ATEST_Actor::HandleTargetDestroyed(AActor* DestroyedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Target Destroyed"));

	//if (IsValid(ObjectPtr_TEST))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("StrongPtr_IS_VALID_OnDestroyed"));
	//}
	//else if (!IsValid(ObjectPtr_TEST))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("StrongPtr_IS_NOT_VALID_OnDestroyed"));
	//}

	//if (WeakObjectPtr_TEST.IsValid())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("WeakPtr_Is_Valid_OnDestroyed"));
	//}
	//else if (!WeakObjectPtr_TEST.IsValid())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("WeakPtr_is_Not_Valid_OnDestroyed"));
	//}
}

