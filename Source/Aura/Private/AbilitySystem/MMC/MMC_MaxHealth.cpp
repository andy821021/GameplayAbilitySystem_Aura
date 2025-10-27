// copy whatever u like


#include "AbilitySystem/MMC/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigerDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigerDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigerDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigerDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather Tag from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigerDef,Spec,EvaluateParams,Vigor);
	Vigor = FMath::Max<float>(Vigor,0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 150.f + Vigor * 2.5f + 10.f * PlayerLevel;
}
