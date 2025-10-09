// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
struct FOnAttributeChangeData;

//C59
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag MessageTag = FGameplayTag();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Message = FText();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image = nullptr;
};

//C62
/*
//C34
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignture,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignture,float,NewMaxHealth);
//C36
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignture,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignture,float,NewMaxMana);
*/
//C59
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignture,FUIWidgetRow,Row);

//C62
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignture,float,NewAttribute);

/**
 * 
 */

//C57 C59要寫在 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageSignture,FUIWidgetRow,Row); 之前
/*
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag MessageTag = FGameplayTag();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Message = FText();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image = nullptr;
};
*/

//C34為了在BP內可新增與編輯
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	//C34
public:
	virtual void BroadcastInitialValues() override;

	//C62改
	/*
	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnHealthChangedSignture OnHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnMaxHealthChangedSignture OnMaxHealthChanged;

	//C36
	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnManaChangedSignture OnManaChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnMaxManaChangedSignture OnMaxManaChanged;
	*/
	//C35
	virtual void BindCallbacksToDependencies() override;
	//C59
	UPROPERTY(BlueprintAssignable,Category="GAS|Message")
	FMessageWidgetRowSignture MessageWidgetRowDelegate;

	//C62
	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnAttributeChangedSignture OnHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnAttributeChangedSignture OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnAttributeChangedSignture OnManaChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnAttributeChangedSignture OnMaxManaChanged;
	//C63
	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnAttributeChangedSignture OnGhostHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attrbutes")
	FOnAttributeChangedSignture OnGhostManaChanged;
	
	//C35
protected:
	//C62
	/*
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	//C36
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
	*/
	//C57
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="WidgetData")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	//C58
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag);
	//C63
	FTimerHandle TimerHandle_DelayGlostBar;
};

//C58
template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
