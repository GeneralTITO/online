// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWIdget.generated.h"

/**
 * 
 */
UCLASS()
class ONLINE_API UOverheadWIdget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayText;


	void SetDisplayText(FString TextToDisplay);


	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* InPawn);


protected:
	virtual void NativeDestruct() override;
};
