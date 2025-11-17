// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
//C21
class UAbilitySystemComponent;
class UAttributeSet;


UCLASS(Abstract)
//C21 C73改
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	//C21
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }


	
	
protected:
	virtual void BeginPlay() override;

	//C7
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//C111
	virtual FVector GetSocketLocation();
	
	UPROPERTY(EditAnywhere,Category="Combat")
	FName WeaponTipSocketName;

	//C21
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//C54 這個函數與ASC自帶的InitAbilityActorInfo()是不同的
	virtual void InitAbilityActorInfo();

	//C66
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	//C71改
	//void InitializePrimaryAttributes() const;

	//C71
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	void  ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass,float level) const;
	//C131改
	virtual void  InitializeDefaultAttributes() const;

	//C75
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	//C98
	void AddCharacterAbilities();

	
	//C98
private:
	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
