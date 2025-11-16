// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UHealthBarOnHeadWidgetController;
struct FWidgetControllerParams;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
protected:

	//C23
	virtual void BeginPlay() override;

	//C54 
	virtual void InitAbilityActorInfo() override;
	
	//C73
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="CharacterClassDefault")
	int32 Level = 1;
	
public:
	
	// EnemyInterface //
	//C13
	 virtual void HighLightActor() override;
	 virtual void UnHighLightActor() override;
	// EndEnemyInterface //
	
	//C14
	// UPROPERTY(BlueprintReadOnly)
	// bool bHighLighted = false;
	
	//C15
	AAuraEnemy();

	// CombatInterface //
	//C73
	virtual int32 GetPlayerLevel() override;
	// EndCombatInterface //
	
	//C125
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> HealthBarOnHead;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignture OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignture OnMaxHealthChanged;
private:
	
};
