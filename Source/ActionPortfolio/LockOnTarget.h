// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LockOnTarget.generated.h"

//언리얼 인터페이스는 U클래스와 I클래스 두가지 가 만들어진다.
//본체는 I클래스로, 일반 CPP클래스 이며, UObject의 자손클래스가 아님. 구현은 I클래스에서 함.
//구현이 일반 CPP클래스에서 되었기 때문에, 이걸 언리얼이 알아볼 수 있게 UClass로 하나 더 만듦.

// This class does not need to be modified.
//
UINTERFACE(MinimalAPI,Blueprintable)
class ULockOnTarget : public UInterface
{
	GENERATED_BODY()
};


class ACTIONPORTFOLIO_API ILockOnTarget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void OnLockedOn();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void OnLockReleased();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FVector GetLockOnPointLocation() const;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
};
