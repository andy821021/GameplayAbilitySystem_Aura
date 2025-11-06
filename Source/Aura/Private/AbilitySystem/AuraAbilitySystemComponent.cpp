// copy whatever u like


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//C108改
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::ClientEffectApplied);
	//C87
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	/*
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Orange,
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString())
		);
	*/
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		//C103
		if (UAuraGameplayAbility* AuraGameplayAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraGameplayAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		};
		//GiveAbility(AbilitySpec);
		//GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	//C103
	if (!InputTag.IsValid()) return;
	for (FGameplayAbilitySpec& AbilitySpec :GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	//C103
	if (!InputTag.IsValid()) return;
	for (FGameplayAbilitySpec& AbilitySpec :GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GES,
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
