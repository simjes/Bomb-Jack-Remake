// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class BOMBJACKIE_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerHp(int Hp);
	UFUNCTION(BlueprintCallable)
	void UpdatePyramidHp(int Hp);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> PyramidHpText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> PlayerHpText;
};
