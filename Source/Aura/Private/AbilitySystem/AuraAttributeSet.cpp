// copy whatever u like


#include "AbilitySystem/AuraAttributeSet.h"

#include "AuraGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"



UAuraAttributeSet::UAuraAttributeSet()
{
	//C26 C71改 C75改
	//InitHealth(100.f);
	//InitMana(100.f);
	//InitMaxHealth(150.f);
	//InitMaxMana(150.f);
	
	//C95
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	//C95 方法1
	/*
	FAttributeSignature StrengthDelegate;
	StrengthDelegate.BindStatic(UAuraAttributeSet::GetStrengthAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Strength,StrengthDelegate);
	*/
	//C95 方法2 這邊add的value是pointer 不是 function
	//Primary Attributes//
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Strength,GetStrengthAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence,GetIntelligenceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Resilience,GetResilienceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Vigor,GetVigorAttribute);
	//C96
	//Secondary Attributes//
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_Armor,GetArmorAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration,GetArmorPenetrationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance,GetBlockChanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance,GetCriticalHitChanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage,GetCriticalHitDamageAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance,GetCriticalHitResistanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration,GetHealthRegenerationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration,GetManaRegenerationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth,GetMaxHealthAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana,GetMaxManaAttribute);
	
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//後面兩個傳參表示 不用任何condition和總是複製(就算數值沒有變化也複製)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);

	//C65
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Resilience,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Vigor,COND_None,REPNOTIFY_Always);

	//C70
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ArmorPenetration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,BlockChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitDamage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,HealthRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ManaRegeneration,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Armor,OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ArmorPenetration,OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,BlockChance,OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitChance,OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitDamage,OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitResistance,OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,HealthRegeneration,OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ManaRegeneration,OldManaRegeneration);
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Strength,OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Intelligence,OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Resilience,OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const	
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Vigor,OldVigor);
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

