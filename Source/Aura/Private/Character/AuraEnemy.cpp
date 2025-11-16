// copy whatever u like


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/AuraUserWidget.h"
#include "Components/WidgetComponent.h"

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
	//C22
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	//C21
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	//C125
	HealthBarOnHead = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidget");
	HealthBarOnHead->SetupAttachment(GetRootComponent());
	HealthBarOnHead->SetWidgetSpace(EWidgetSpace::Screen);
	
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}


void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	//C54改
	/*
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	*/
	InitAbilityActorInfo();
	//C125
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBarOnHead->GetUserWidgetObject());
	if (AuraUserWidget)
	{
		AuraUserWidget->SetWidgetController(this);
	}
	
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
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
}

void AAuraEnemy::InitAbilityActorInfo()
{
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	//C124
	InitializeDefaultAttributes();
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



	