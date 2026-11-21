// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnComponent.h"
#include "LockOnTarget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	

}


// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULockOnComponent::TargetReleased(AActor* Target)
{
	if (Target != LockOnActor.Get())
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s LockOnReleased."), *Target->GetName());

	ChangeTarget(nullptr, true);
}

AActor* ULockOnComponent::GetLockOnActor()
{
	return LockOnActor.Get();
}

void ULockOnComponent::ChangeTarget(AActor* NewTarget, bool bPreviousTargetIsBeingDestroyed)
{
	FString Name_Old = "NULL";
	FString Name_New = "NULL";

	AActor* Old = LockOnActor.Get();
	if (Old == NewTarget)
	{
		return;
	}
	if (IsValid(Old)&& Old->Implements<ULockOnTarget>())
	{
		Name_Old = Old->GetName();
		if (!bPreviousTargetIsBeingDestroyed)
		{
			ILockOnTarget::Execute_OnLockReleased(Old);
			Old->OnDestroyed.RemoveDynamic(this, &ULockOnComponent::TargetReleased);
			
		}
	}
	LockOnActor = NewTarget;
	if (LockOnActor.IsValid() && LockOnActor.Get()->Implements<ULockOnTarget>())
	{
		Name_New = LockOnActor.Get()->GetName();
		LockOnActor->OnDestroyed.AddDynamic(this, &ULockOnComponent::TargetReleased);
		ILockOnTarget::Execute_OnLockedOn(LockOnActor.Get());
	}
	OnLockOnChanged.Broadcast(Old, LockOnActor.Get());
	
	UE_LOG(LogTemp, Warning, TEXT("Old = %s  ||  New = %s"), *Name_Old, *Name_New);
}

void ULockOnComponent::ToggleLockOn(FVector PlayerPosition)
{
	AActor* NewActor = FindLockOnTarget(PlayerPosition);
	if (!IsValid(NewActor))
	{
		ChangeTarget(nullptr, false);
		return;
	}
	if (NewActor == LockOnActor)
	{
		ChangeTarget(nullptr, false);
		return;
	}

	ChangeTarget(NewActor, false);
}

AActor* ULockOnComponent::FindLockOnTarget(FVector PawnLocation)
{
	FName Tag = FName("LockOnTarget");
	TArray<AActor*> FoundActors;
	AActor* NewLockOnActor = nullptr;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), Tag, FoundActors);
	if (FoundActors.IsValidIndex(0))
	{
		for (AActor* FoundActor : FoundActors)
		{
			if (!IsValid(NewLockOnActor))
			{
				NewLockOnActor = FoundActor;
			}

			double minDist = FVector::Distance(PawnLocation, NewLockOnActor->GetActorLocation());
			double newDist = FVector::Distance(PawnLocation, FoundActor->GetActorLocation());

			if (newDist < minDist)
			{
				NewLockOnActor = FoundActor;
			}
		}
		return NewLockOnActor;
	}
	else
	{
		return nullptr;
	}
}

bool ULockOnComponent::IsLockedOn() const
{
	return LockOnActor.IsValid();
}

