// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

//C117改
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature,const FVector&,Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature,const FGameplayAbilityTargetDataHandle&,DataHandle);
/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
	//C115
public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks",meta=(Displayname = "TargetDataUnderMouse",HidePin ="OwningAbility",DefaultToSelf = "OwningAbility",BlueprintInternalOnly = true))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValueData;

private:

	virtual void Activate() override;
	
	//C117
	void SendMouseCursorData();

	//C118
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
