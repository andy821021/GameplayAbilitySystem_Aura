// copy whatever u like


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	//Super::BroadcastInitialValues();
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	//C36
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	//C63
	OnGhostHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnGhostManaChanged.Broadcast(AuraAttributeSet->GetMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	//Super::BindCallbacksToDependencies();
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	//C62
	/*
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this,&UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this,&UOverlayWidgetController::MaxHealthChanged);
	//C36
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this,&UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this,&UOverlayWidgetController::MaxManaChanged);
	*/
	//C56 用AddLambda做綁定
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& Tags )
	{
		for (const FGameplayTag& tag : Tags)
		{
			//C59
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(TEXT("Message"));
			
			// "A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
			if (tag.MatchesTag(MessageTag))
			{
				/*
				//C56
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"),*tag.ToString());
				//要boradcast(廣播) tag 給 Widget Controller
				GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Blue,Msg);
				*/
				//C58
				FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,tag);
				//C59 綁定在UE內的WBP_Overlay
				MessageWidgetRowDelegate.Broadcast(*Row);
			};
		} 
	}
	);
	//C62
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);
	/*
	//C63
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
		{
			//C63
			if (GetWorld()==nullptr) return;
			const float NewValue = Data.NewValue;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayGlostBar,[this,NewValue](){OnGhostHealthChanged.Broadcast(NewValue);},0.5f,false);
			//OnGhostHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
		{
			//C63
			if (GetWorld()==nullptr) return;
			const float NewValue = Data.NewValue;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayGlostBar,[this,NewValue](){OnGhostManaChanged.Broadcast(NewValue);},0.5f,false);
			//OnGhostHealthChanged.Broadcast(Data.NewValue);
		}
	);
	*/ 
}
//C62
/*
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
} 

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
*/