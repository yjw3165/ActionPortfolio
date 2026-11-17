// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnComponent.h"
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

void ULockOnComponent::SetTarget(const FVector& FindTargetStartPosition)
{
	AActor* NewLockOnActor = FindLockOnTarget(FindTargetStartPosition);
	if (NewLockOnActor != nullptr)
	{
		//기존의 락온 액터가 이미 있다면
		if (LockOnActor.IsValid())
		{

			//이미 있고 새로 찾은 액터랑 기존 액터가 같다면, 락온 해제
			if (LockOnActor == NewLockOnActor)
			{
				//이미 LockOnActor가 존재하고, 이게 새로들어온 NewLockOnActor랑 같으면 락온 토글 해제
				LockOnActor->OnDestroyed.RemoveDynamic(this, &ULockOnComponent::TargetReleased);
				LockOnActor.Reset();
				OnLockOnChanged.Broadcast(nullptr);
				UE_LOG(LogTemp, Warning, TEXT("SameTarget Lock On OFF"));
				return;
			}
			//이미 있는데 새로 찾은 액터랑 다르다면, 새로찾은 액터로 락온 변경
			else
			{
				//기존의 LockOnActor가있으면 OnDestroy Unbind
				LockOnActor->OnDestroyed.RemoveDynamic(this, &ULockOnComponent::TargetReleased);
				LockOnActor = NewLockOnActor;
				LockOnActor->OnDestroyed.AddDynamic(this, &ULockOnComponent::TargetReleased);
				OnLockOnChanged.Broadcast(GetLockOnActor());
				UE_LOG(LogTemp, Warning, TEXT("Another Target Locked On %s"), *LockOnActor.Get()->GetName());
				return;
			}
		}
		else
		{
			LockOnActor = NewLockOnActor;
			LockOnActor->OnDestroyed.AddDynamic(this, &ULockOnComponent::TargetReleased);
			OnLockOnChanged.Broadcast(GetLockOnActor());
			UE_LOG(LogTemp, Warning, TEXT("New Target Locked On %s"), *GetLockOnActor()->GetName());
		}
	}
}

void ULockOnComponent::TargetReleased(AActor* Target)
{
	UE_LOG(LogTemp, Warning, TEXT("%s LockOnReleased."), *Target->GetName());
	LockOnActor.Reset();

	OnLockOnChanged.Broadcast(nullptr);

	if (!LockOnActor.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LockOnActor is False"));
	}
}

AActor* ULockOnComponent::GetLockOnActor()
{
	return LockOnActor.Get();
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

