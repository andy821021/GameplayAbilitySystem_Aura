


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"



AAuraCharacterBase::AAuraCharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//C120
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	//C123
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	//C124
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AAuraCharacterBase::GetSocketLocation()
{
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

/*
void AAuraCharacterBase::InitializePrimaryAttributes() const
{
	check(GetAbilitySystemComponent());
	check(DefaultPrimaryAttributes);
	const FGameplayEffectContextHandle GameplayEffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes,1.f,GameplayEffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(),GetAbilitySystemComponent());
}
*/

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const
{
	check(GetAbilitySystemComponent());
	check(GameplayEffectClass);
	
	//C73改
	FGameplayEffectContextHandle GameplayEffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass,level,GameplayEffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(),GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes,1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes,1.f);
	ApplyEffectToSelf(DefaultVitalAttributes,1.f);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->AddCharacterAbilities(StartupAbilities);
}





