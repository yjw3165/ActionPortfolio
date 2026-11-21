// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockOnTarget.h"
#include "LockOnTestActor.generated.h"

class UStaticMeshComponent;
class UMaterialInterface;

UCLASS()
class ACTIONPORTFOLIO_API ALockOnTestActor : public AActor, public ILockOnTarget
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockOnTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category= "Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere , Category = "Material")
	UMaterialInterface* LockedOnMaterial;

	virtual void OnLockedOn_Implementation() override;
	virtual void OnLockReleased_Implementation() override;

private:
	void ChangeLockOnMaterial(bool IsLockedOn);


};
