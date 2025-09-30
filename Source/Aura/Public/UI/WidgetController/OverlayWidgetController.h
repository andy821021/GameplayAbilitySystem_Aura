// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
//C34
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignture,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignture,float,NewMaxHealth);
//C36
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignture,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignture,float,NewMaxMana);
/**
 * 
 */

//C34為了在BP內可新增與編輯
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	//C34
public:
	virtual void BroadcastInitialValues() override;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnHealthChangedSignture OnHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnMaxHealthChangedSignture OnMaxHealthChanged;
	//C35
	virtual void BindCallbacksToDependencies() override;
	//C36
	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnManaChangedSignture OnManaChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnMaxManaChangedSignture OnMaxManaChanged;
	
	//C35
protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	//C36
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
