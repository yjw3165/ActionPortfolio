// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LockOnComponent.h"
#include "LockOnTestActor.h"
#include "ActionPortfolioPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;
class UInputAction;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class AActionPortfolioPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	AActionPortfolioPlayerController();

protected:

	UPROPERTY(BlueprintReadOnly,EditAnywhere) TObjectPtr<ULockOnComponent> LockOnComponent;
	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* LockOnAction;
	UPROPERTY(EditAnywhere, Category = "LockOn Camera") float LockOnCameraMoveSpeed = 7.f;
	UPROPERTY(EditAnywhere, Category = "LockOn Camera") float CameraPitchClamp_Min = -65.f;
	UPROPERTY(EditAnywhere, Category = "LockOn Camera") float CameraPitchClamp_Max = 45.f;
	UPROPERTY(EditAnywhere, Category = "LockOn Camera") float CameraPitchOffset = -20.f;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	void ToggleLockOn();

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Tick*/
	virtual void Tick(float DeltaTime) override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;

	UFUNCTION() void HandleLockOnChanged(AActor* OldTarget, AActor* NewTarget);
};
