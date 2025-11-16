// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AuraProjectile.generated.h"

class UNiagaraSystem;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()

public:

	AAuraProjectile();
	
	//C109
	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	//124
	UPROPERTY(BlueprintReadWrite,meta=(ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

protected:

	virtual void BeginPlay() override;
	//C122
	virtual void Destroyed() override;

	//C109
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlapedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

private:
	//C109
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	//C122
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	bool bHit = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;
	UPROPERTY(EditAnywhere)
	float LifeSpan = 5.f;
};
