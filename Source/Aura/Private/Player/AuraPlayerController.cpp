// copy whatever u like


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	//C105
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	//C107
	AutoRun();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	//C33改
	//check(Subsystem);
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//C102改
	/*
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	*/
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	//C108改
	//FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	/*
	 * 這邊處理會遇到機個狀況
	 *	A. LastActor is null && ThisActor is null
	 *		- Do nothing
	 *	B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 *	C. LastActor is valid && ThisActor is null
	 *		- Unhighlight LastActor
	 *	D. Both actor are valid, but LastActor != ThisActor
	 *		- Unhighlight LastActor && Highlight ThisActor
	 *	E. Both actor are valid, and LastActor = ThisActor
	 *		- Do nothing
	 */
	//C108改
	/*
	if (LastActor.GetInterface() == nullptr)
	{
		if (ThisActor.GetInterface() != nullptr)
		{
			//B. LastActor is null && ThisActor is valid
			ThisActor->HighLightActor();
		}
		else
		{
			//A. LastActor is null && ThisActor is null
		}
	}
	else
	{
		if (ThisActor.GetInterface()!=nullptr)
		{
			if (ThisActor == LastActor)
			{
				//E. Both actor are valid, and LastActor = ThisActor
			}
			else
			{
				//D. Both actor are valid, but LastActor != ThisActor
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
		}
		else
		{
			//C. LastActor is valid && ThisActor is null
			LastActor->UnHighLightActor();
		}
	}
	*/
	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighLightActor();
		if (ThisActor) ThisActor->HighLightActor();
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//C105
	//GEngine->AddOnScreenDebugMessage(1,2.f,FColor::Red,*InputTag.ToString());
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//C103
	//GEngine->AddOnScreenDebugMessage(2,2.f,FColor::Red,*InputTag.ToString());
	//C106 改
	/*
	if (GetAuraAbilitySystemComponent() ==nullptr) return;
	GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
	*/
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		APawn* ControlledPawn = GetPawn();
		if (FollowTime<=ShortPressThreshold && ControlledPawn)
		{
			 if (UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(),ControlledPawn->GetActorLocation(),CachedDestination))
			 {
			 	Spline->ClearSplinePoints();
			 	for (const FVector& Point : NavigationPath->PathPoints)
			 	{
			 		Spline->AddSplinePoint(Point,ESplineCoordinateSpace::World);
			 		//DrawDebugSphere(GetWorld(),Point,8.f,8,FColor::Yellow,false,5.f);
			 	}
			 	//C107
			 	CachedDestination = NavigationPath->PathPoints.Last();
			 	bAutoRunning = true;
			 };
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//C103
	//GEngine->AddOnScreenDebugMessage(3,2.f,FColor::Red,*InputTag.ToString());
	
	//C105 改
	/*
	if (GetAuraAbilitySystemComponent() ==nullptr) return;
	GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
	*/
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		//C108改
		//FHitResult Hit;
		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}
		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination<= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
