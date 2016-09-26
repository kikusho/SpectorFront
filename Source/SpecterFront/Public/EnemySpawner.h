// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "BaseEnemy.h"
#include "EnemySpawner.generated.h"

// �G�̐������I���������Ƃ�ʒm����
DECLARE_DYNAMIC_DELEGATE(FFinishSpawnDelegate);

/**
 * �G�̏o���ʒu���w�肷�邽�߂̃I�u�W�F�N�g
 */
UCLASS(Blueprintable, BlueprintType)
class SPECTERFRONT_API AEnemySpawner : public ATargetPoint
{
	GENERATED_BODY()

public:
	// �����B�u���[�v�����g���ŃI�[�o�[���C�h����ꍇ�̓I�[�o�[���C�h�����ĂԂ���
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void BeginSpawn(AActionPhaseController* spawnController);

public: // UPROPERTY
	// �X�|�[���𐧌䂷��I�u�W�F�N�g
	UPROPERTY(BlueprintReadOnly)
		AActionPhaseController* spawnController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ABaseEnemy> spawnEnemyType;

	// ���g���Ǘ�����G
	UPROPERTY(BlueprintReadOnly)
		TArray<ABaseEnemy*> spawnedEnemies;

	//UPROPERTY(BlueprintReadWrite)
	//	FCompleteDelegate completeEvent;

	// �����\�B�G�����ׂē|���Ȃ��Ă���֐i�ނ��Ƃ��o����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isIgnoreble;

public:
	// ���݂̃X�|�[�i�[���琧����ڂ��ۂɌĂяo��
	UFUNCTION(BlueprintCallable, Category = "EnemySpawn")
		void FinishSpawn();
};
