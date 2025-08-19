// copy whatever u like


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->SetRenderCustomDepth(false);
	if (Weapon)
	{
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
		Weapon->SetRenderCustomDepth(false);
	}

	//C21
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighLightActor()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HighLightActor"));
	//bHighLighted = true;
	//C15
	//GetMesh()->SetCustomDepthStencilValue(250);
	GetMesh()->SetRenderCustomDepth(true);
	if (Weapon)
	{
		//Weapon->SetCustomDepthStencilValue(250);
		Weapon->SetRenderCustomDepth(true);
	}
}

void AAuraEnemy::UnHighLightActor()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UnHighLightActor"));
	//bHighLighted = false;
	//C15
	GetMesh()->SetRenderCustomDepth(false);
	if (Weapon)
	{
		//Weapon->SetCustomDepthStencilValue(250);
		Weapon->SetRenderCustomDepth(false);
	}
}



	