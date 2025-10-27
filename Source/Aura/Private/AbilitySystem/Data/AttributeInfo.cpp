// copy whatever u like


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfo(const FGameplayTag& GameplayTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.GameplayTag == GameplayTag)
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Can't find Info for Attribute [%s] on AttributeInfo [%s]"),*GameplayTag.ToString(),*GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
