// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "AbstractEnemySpawner.h"


// Sets default values
AAbstractEnemySpawner::AAbstractEnemySpawner()
	: allEnemies(nullptr)
	, isSpawning(false)
	, isGenerating(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAbstractEnemySpawner::OnEnemyDie_Implementation(TScriptInterface<IEnemyInterface>& enemy)
{
	allEnemies->actors.Remove(Cast<AActor>(enemy.GetObjectRef()));
	NotifiRemoveEnemy();
}

void AAbstractEnemySpawner::TriggerSpawn_Implementation(AAbstractEnemySpawner* parent, FFinishSpawn callback, UActorContainer* allEnemies)
{
	if (isSpawning)
	{
		return;
	}

	this->allEnemies = allEnemies;
	this->parent = parent;
	finishSpawnHandler = callback;
	isSpawning = true;
	isGenerating = true;

	BeginSpawn();
}

int32 AAbstractEnemySpawner::GetSpawnedEnemyCount() const
{
	return managedEnemyCount;
}

void AAbstractEnemySpawner::EndSpawn()
{
	if (!isSpawning)
	{
		return;
	}

	isGenerating = false;

	// BP�ɑ΂��ďI���ʒm
	OnEndSpawn();
}

void AAbstractEnemySpawner::Finish()
{
	if (!isSpawning)
	{
		return;
	}

	isSpawning = false;

	// �e�ɑ΂��ďI���ʒm
	finishSpawnHandler.finishSpawnDelegate.ExecuteIfBound();
}

void AAbstractEnemySpawner::NotifiAddEnemy()
{
	++managedEnemyCount;

	if (parent == nullptr)
		return;

	// �q����e�֏����Ăяo���Ă���
	parent->NotifiAddEnemy();
}

void AAbstractEnemySpawner::NotifiRemoveEnemy()
{
	--managedEnemyCount;

	if (parent == nullptr)
		return;

	// �q����e�֏����Ăяo���Ă���
	parent->NotifiRemoveEnemy();
}
