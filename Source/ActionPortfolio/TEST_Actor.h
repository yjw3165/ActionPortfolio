// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockOnComponent.h"
#include "TEST_Actor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOntimerTick);

UCLASS()
class ACTIONPORTFOLIO_API ATEST_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATEST_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int TEST_Variable;

	UPROPERTY(EditAnywhere) TObjectPtr<AActor> ObjectPtr_TEST_A;
	UPROPERTY(EditAnywhere) TObjectPtr<AActor> ObjectPtr_TEST_B;
	UPROPERTY(EditAnywhere) TWeakObjectPtr<AActor> WeakObjectPtr_TEST;
	
	UPROPERTY(BlueprintAssignable) FOntimerTick OnTimerTick;

	AActor* RawTarget;

	FTimerHandle LogTimerHandle;

	void LogTargets();

	UFUNCTION()
	void HandleTargetDestroyed(AActor* DestroyedActor);


	//Components
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere) TObjectPtr<ULockOnComponent> LockOn;
};
