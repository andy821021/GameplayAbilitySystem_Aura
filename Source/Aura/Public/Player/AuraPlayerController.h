// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
class UAuraInputConfig;
//C10
class UInputMappingContext;
//C11
class UInputAction;
struct FInputActionValue;
//C14
class IEnemyInterface;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	//C10
	AAuraPlayerController();
	//C14
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	//C10
	virtual void BeginPlay() override;
	//C11
	virtual void SetupInputComponent() override;
private:
	//C10
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	//C11
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue);

	//C120
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> ShiftAction;

	void ShiftPressed(){bShiftKeyDown = true;};
	void ShiftReleased(){bShiftKeyDown = false;};
	bool bShiftKeyDown = false;

	//C14
	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	//C102
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	//C103
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();

	//C105
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	//C107
	void AutoRun();

	//C108
	FHitResult CursorHit;
	
};
