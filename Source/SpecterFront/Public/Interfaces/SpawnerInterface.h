// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SpawnableInterface.h"
#include "SpawnerInterface.generated.h"


UINTERFACE(BlueprintType)
class USpawnerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// ������S������I�u�W�F�N�g
class ISpawnerInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	// �����J�n
	UFUNCTION(BlueprintImplementableEvent)
		void Begen(FFinishSpawn callBack, UEnemyContainer* spawnedEnemies);
};