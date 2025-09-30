// copy whatever u like


#include "AbilitySystem/AuraAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	//C26
	InitHealth(100.f);
	InitMana(100.f);
	InitMaxHealth(150.f);
	InitMaxMana(150.f);
	
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//後面兩個傳參表示 不用任何condition和總是複製(就算數值沒有變化也複製)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//用於通知GAS該項變更
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana,OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMana,OldMaxMana);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue , 0.0f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue , 0.0f, GetMaxMana());
	}
}

void UAuraAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue , 0.0f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue , 0.0f, GetMaxMana());
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	/*
	//if(Data.EvaluatedData.Attribute == GetHealthAttribute()){};
	FGameplayEffectContextHandle EffectContextHandle = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* SourceASC = EffectContextHandle.GetInstigatorAbilitySystemComponent();

	//Source的各項資訊
	if (IsValid(SourceASC)&&SourceASC->AbilityActorInfo.IsValid()&&SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		//AActor* SourceAvatarActor = SourceASC->GetAvatarActor();
		AActor* SourceAvatarActor = SourceASC->AbilityActorInfo->AvatarActor.Get();
		AController* SourceController = SourceASC->AbilityActorInfo.Get()->PlayerController.Get();
		if (SourceController == nullptr && SourceAvatarActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(SourceAvatarActor))
			{
				SourceController = Pawn->GetController();
			}
		}
		if (SourceController)
		{
			ACharacter* SourceCharacter = SourceController->GetCharacter();
		}
	}
	//Target的各項資訊
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		AController* TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		ACharacter* TargetCharacter = Cast<ACharacter>(TargetAvatarActor);
		UAbilitySystemComponent* TargetASC = &Data.Target;
	}
	*/
	FEffectProperties Props;
	SetEffectProperties(Props,Data);
}

void UAuraAttributeSet::SetEffectProperties(FEffectProperties& EP, const FGameplayEffectModCallbackData& Data)
{
	EP.GameplayEffectContextHandle = Data.EffectSpec.GetContext();
	EP.SourceASC = EP.GameplayEffectContextHandle.GetInstigatorAbilitySystemComponent();

	//Source的各項資訊
	if (IsValid(EP.SourceASC)&& EP.SourceASC->AbilityActorInfo.IsValid()&& EP.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		//AActor* SourceAvatarActor = EP.SourceASC->GetAvatarActor();
		EP.SourceAvatarActor = EP.SourceASC->AbilityActorInfo->AvatarActor.Get();
		EP.SourceController = EP.SourceASC->AbilityActorInfo.Get()->PlayerController.Get();
		if (EP.SourceController == nullptr && EP.SourceAvatarActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(EP.SourceAvatarActor))
			{
				EP.SourceController = Pawn->GetController();
			}
		}
		if (EP.SourceController)
		{
			EP.SourceCharacter = EP.SourceController->GetCharacter();
		}
	}
	//Target的各項資訊
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EP.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EP.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EP.TargetCharacter = Cast<ACharacter>(EP.TargetAvatarActor);
		EP.TargetASC = &Data.Target;
	}
}

