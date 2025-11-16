// copy whatever u like


#include "Actor/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	//C111
	bReplicates = true;
	//C109
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	//C123
	Sphere->SetCollisionObjectType(ECC_Projectile);
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECR_Overlap);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComponent->InitialSpeed = 550.f;
	ProjectileMovementComponent->MaxSpeed = 550.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}


void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AAuraProjectile::OnSphereOverlap);
	//C122
	UGameplayStatics::SpawnSoundAttached(LoopingSound,GetRootComponent(),FName(),GetActorLocation(),FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset,true);
	SetLifeSpan(LifeSpan);
	
}

void AAuraProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation(),GetActorRotation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
	}
	Super::Destroyed();
	
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation(),GetActorRotation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
	if (HasAuthority())
	{
		//C124
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		};
		
		Destroy();
	}
	else
	{
		bHit = true;
	}
}


