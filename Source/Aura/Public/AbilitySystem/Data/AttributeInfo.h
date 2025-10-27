// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

/**
 * 
 */
//C89
USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag GameplayTag = FGameplayTag();
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};


UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
//C89
public:

	FAuraAttributeInfo FindAttributeInfo(const FGameplayTag& GameplayTag,bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
	
};
