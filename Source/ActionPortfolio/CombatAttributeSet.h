// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONPORTFOLIO_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UCombatAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	FGameplayAttributeData GuardGauge;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet, GuardGauge);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	FGameplayAttributeData MaxGuardGauge;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet, MaxGuardGauge);
	
};
