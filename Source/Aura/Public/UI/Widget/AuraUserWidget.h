// copy whatever u like

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//C29
	//用於設置WidgetController變量 在BP中使用後會覆蓋WidgetControllerSet()
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject>	WidgetController;

protected:

	//用於類似BeginPlay Event
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
