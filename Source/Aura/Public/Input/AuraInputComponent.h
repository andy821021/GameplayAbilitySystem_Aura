// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
/*
public:
	// Sets default values for this component's properties
	UAuraInputComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,

	                           FActorComponentTickFunction* ThisTickFunction) override;
	 */

	//C101
public:
	template<class UserClass,typename PressedFuncType,typename ReleaseFuncType,typename HeldFuncType>
	void BindAbilityActions(UAuraInputConfig* InputConfig,UserClass* Object,PressedFuncType PressedFunc,ReleaseFuncType ReleaseFunc,HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleaseFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(UAuraInputConfig* InputConfig, UserClass* Object,PressedFuncType PressedFunc, ReleaseFuncType ReleaseFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	for (const FAuraInputAction& InputAction : InputConfig->InputActions)
	{
		if (InputAction.InputAction && InputAction.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(InputAction.InputAction,ETriggerEvent::Started,Object,PressedFunc,InputAction.InputTag);
			}
			if (ReleaseFunc)
			{
				BindAction(InputAction.InputAction,ETriggerEvent::Completed,Object,ReleaseFunc,InputAction.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(InputAction.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,InputAction.InputTag);
			}
		}
	};
}
