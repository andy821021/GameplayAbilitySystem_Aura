// copy whatever u like


#include "UI/HUD/AuraHUD.h"

//#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		//C35
		OverlayWidgetController->BindCallbacksToDependencies();

		//return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("OverlayWidgetClass uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass uninitialized, please fill out BP_AuraHUD"));


	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);

	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);

	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);

	//C34 在BP綁定後才廣播
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this,AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		//C35
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

/*
void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UAuraUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetWorld(),OverlayWidgetClass);
	Widget->AddToViewport();
}
*/
