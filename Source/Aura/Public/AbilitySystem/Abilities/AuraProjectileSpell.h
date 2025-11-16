// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()
	//C110
	protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);


	
	//C111
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;

	//C114 C120改
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

	//C124
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

};
