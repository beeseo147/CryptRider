// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInterFace.generated.h"

UINTERFACE(MinimalAPI,Blueprintable)
class UPlayerInterFace : public UInterface
{
    GENERATED_BODY()
};

class IPlayerInterFace
{
    GENERATED_BODY()

public:
    /** 이 오브젝트를 활성화시키는 액션에 반응합니다. 반응에 성공하면 true 를 반환합니다. */
    UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
    void ReactToTrigger();

    void ReactToTrigger_Implementation();
};