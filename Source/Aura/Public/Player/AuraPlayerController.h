// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

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

	//C14
	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
};
