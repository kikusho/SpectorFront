// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnerInterface.h"
#include "SpawnDirector.generated.h"

UCLASS()
class SPECTERFRONT_API ASpawnDirector : public AActor, public ISpawnerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnDirector();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void Begin(FFinishSpawn callback, UEnemyContainer* spawnedEnemies);

	// �G�̐����J�n���ɌĂяo�����BBlueprint�ŃI�[�o�[���C�h���ď�������������
	UFUNCTION(BlueprintNativeEvent, Category = "EnemySpawn", meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		void OnBeginSpawn();

	// �N������X�|�[�i�[
	UPROPERTY(EditAnywhere, Category = "EnemySpawner")
		TArray<TSubclassOf<ISpawnerInterface>> spawners;

	// �X�|�[�����
	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected, AllowPrivateAccess = "true"))
		bool isSpawing;

	// ������I������Ƃ��ɌĂяo���f���Q�[�g
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FFinishSpawnDelegate finishSpawnHandler;

	// ���g���Ǘ�����G
	UPROPERTY(BlueprintReadOnly)
		UEnemyContainer* spawnedEnemies;
};
