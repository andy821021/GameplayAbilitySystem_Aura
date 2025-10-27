// copy whatever u like


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//Super::BroadcastInitialValues();
	//C93
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	//C93 C95改 一個一個數值創建太費事了，因此用了Tmap存 FGameplayTag 和 委託FAttributeSignature 來檢索
	/*
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfo(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AuraAttributeSet->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
	*/
	
	//C95 方法1
	/*
	for (auto& pair :AuraAttributeSet->TagToAttributes )
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfo(pair.Key);
		Info.AttributeValue = pair.Value.Execute().GetNumericValue(AuraAttributeSet);
		AttributeInfoDelegate.Broadcast(Info);
	}
	*/
	
	//C95 方法2
	for (auto& pair :AuraAttributeSet->TagToAttributes )
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfo(pair.Key);
		// pair.Value() 等於是 GetStrengthAttribute()
		Info.AttributeValue = pair.Value().GetNumericValue(AuraAttributeSet);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	//Super::BindCallbacksToDependencies();
	//C96
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& pair :AuraAttributeSet->TagToAttributes )
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(pair.Value()).AddLambda(
		[this,pair,AuraAttributeSet](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(pair.Key,pair.Value());
			/*
			FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfo(pair.Key);
			Info.AttributeValue = pair.Value().GetNumericValue(AuraAttributeSet);
			AttributeInfoDelegate.Broadcast(Info);
			*/
		}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfo(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
