// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	//C12
	AAuraCharacter();

	//C23
	//For Server init set ASC
	virtual void PossessedBy(AController* NewController) override;
	//For Client int set ASC
	virtual void OnRep_PlayerState() override;

	// CombatInterface //
	//C73
	virtual int32 GetPlayerLevel() override;
	// EndCombatInterface //

private:
	
protected:
	//C23 C54改
	virtual void InitAbilityActorInfo() override;
};
