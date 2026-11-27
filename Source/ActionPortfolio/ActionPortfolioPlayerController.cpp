// Copyright Epic Games, Inc. All Rights Reserved.


#include "ActionPortfolioPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "ActionPortfolio.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widgets/Input/SVirtualJoystick.h"


AActionPortfolioPlayerController::AActionPortfolioPlayerController()
{
	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AActionPortfolioPlayerController::ToggleLockOn()
{
	//테스트중.
	
	LockOnComponent->ToggleLockOn(GetPawn()->GetActorLocation());
}

void AActionPortfolioPlayerController::BeginPlay()
{
	
	Super::BeginPlay();
	// only spawn touch controls on local player controllers
	if (IsLocalPlayerController() && ShouldUseTouchControls())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogActionPortfolio, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}

	if (IsValid(LockOnComponent))
	{
		LockOnComponent->OnLockOnChanged.AddDynamic(this, &AActionPortfolioPlayerController::HandleLockOnChanged);
	}
	
}

void AActionPortfolioPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LockOnComponent->GetLockOnActor() != nullptr)
	{
		if (GetPawn() != nullptr)
		{
			//컨트롤러회전 Pitch 클램프 제한.
			FRotator ControllerRotator = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(),
				LockOnComponent->GetLockOnLocation());

			ControllerRotator.Pitch = ControllerRotator.Pitch + CameraPitchOffset;
			ControllerRotator.Pitch = FMath::Clamp(ControllerRotator.Pitch, CameraPitchClamp_Min, CameraPitchClamp_Max);
			
			SetControlRotation(
				FMath::RInterpTo(GetControlRotation(), ControllerRotator, DeltaTime, LockOnCameraMoveSpeed)
			);
		}
	}
}

void AActionPortfolioPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
				
			}

			UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
			EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Started, this, &AActionPortfolioPlayerController::ToggleLockOn);

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool AActionPortfolioPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

void AActionPortfolioPlayerController::HandleLockOnChanged(AActor* OldTarget, AActor* NewTarget)
{	
	if (OldTarget != nullptr && NewTarget == nullptr)
	{

		UE_LOG(LogTemp, Warning, TEXT("LOCK ON END"));
		SetIgnoreLookInput(false);

		ACharacter* PlayerCharacter = Cast<ACharacter>(GetPawn());
		if (PlayerCharacter != nullptr)
		{
			PlayerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
			PlayerCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		}
		
		return;
	}

	if (OldTarget == nullptr&& NewTarget != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("LOCK ON START"));
		SetIgnoreLookInput(true);

		ACharacter* PlayerCharacter = Cast<ACharacter>(GetPawn());
		if (PlayerCharacter != nullptr)
		{
			PlayerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
			PlayerCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		}

		return;
	}

	if (OldTarget != nullptr && NewTarget != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Switching LOCK ON"));
		return;
	}
}
