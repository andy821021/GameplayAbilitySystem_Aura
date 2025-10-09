// copy whatever u like


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GES,
                                                FActiveGameplayEffectHandle AGEH)
{
	//C55 類似Array只是更優化
	FGameplayTagContainer TagContainer;
	GES.GetAllAssetTags(TagContainer);
	//C56 移動到OverlayWidgetController內的AddLambda()中
	/*
	for (const FGameplayTag& tag : TagContainer)
	{
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"),*tag.ToString());
		//要boradcast(廣播) tag 給 Widget Controller
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Blue,Msg);
	}
	*/
	//C56
	EffectAssetTags.Broadcast(TagContainer);
	
}
