// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
//C121
UINTERFACE(BlueprintType,Blueprintable)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//C73
	virtual int32 GetPlayerLevel() {return 0;};
	//C111
	virtual FVector GetSocketLocation();

	//C121
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateFacingTarget(const FVector& target);
};
