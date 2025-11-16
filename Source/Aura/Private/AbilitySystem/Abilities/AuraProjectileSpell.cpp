// copy whatever u like


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"


#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//C111改
	//UKismetSystemLibrary::PrintString(GetWorld(), "Active Ability C++");

	//C114改
	/*
	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		//TODO: Set Rotation
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(FVector(CombatInterface->GetSocketLocation()));
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,SpawnTransform,GetOwningActorFromActorInfo(),Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: give the projectile a gameplay effect spec for causing damage
		
		Projectile->FinishSpawning(SpawnTransform);
	}
	*/

}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(FVector(CombatInterface->GetSocketLocation()));
		
		//TODO: Set Rotation
		//C120
		FRotator Rotator = (ProjectileTargetLocation-CombatInterface->GetSocketLocation()).Rotation();
		Rotator.Pitch = 0.0f;
		SpawnTransform.SetRotation(Rotator.Quaternion());
		
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,SpawnTransform,GetOwningActorFromActorInfo(),Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: give the projectile a gameplay effect spec for causing damage
		//C124
		UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),SourceASC->MakeEffectContext());
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
