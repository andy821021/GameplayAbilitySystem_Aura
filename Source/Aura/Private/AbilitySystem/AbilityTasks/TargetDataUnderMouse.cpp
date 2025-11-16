// copy whatever u like


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	//Super::Activate();
	//APlayerController* APC = Cast<APlayerController>(GetAvatarActor()->GetController());

	//C117
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		//TODO We are on the server, so listen for target data
		
		//C118
		FGameplayAbilitySpecHandle DataHandle = GetAbilitySpecHandle();
		FPredictionKey PredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(DataHandle,PredictionKey).AddUObject(this,&UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(DataHandle,PredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
	//C117改
	/*
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if (PC == nullptr) return;
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	ValueData.Broadcast(CursorHit.ImpactPoint);
	*/
	//DrawDebugSphere(GetWorld(),CursorHit.ImpactPoint,8.f,8.f,FColor::Blue,false,5.f);
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey(),DataHandle,FGameplayTag(),AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValueData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValueData.Broadcast(DataHandle);
	}
}
