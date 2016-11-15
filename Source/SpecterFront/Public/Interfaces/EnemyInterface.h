// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyInterface.generated.h"


UINTERFACE(BlueprintType)
class UEnemyInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// ���ׂĂ̓G�͂������������
class IEnemyInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void Enemy();

};