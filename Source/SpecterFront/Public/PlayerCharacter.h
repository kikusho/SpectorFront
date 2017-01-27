// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCharacter.h"
#include "DamageListenerInterface.h"
#include "PlayerCharacter.generated.h"

// �U���q�b�g���̃f���Q�[�g
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHitDelegate, AActor*, hitActor, float, damage);


UCLASS()
class SPECTERFRONT_API APlayerCharacter : public AMyCharacter, public IDamageListenerInterface
{
	GENERATED_BODY()

private:

	friend class AMyPlayerController;

	///** Pawn mesh: 1st person view (arms; seen only by self) */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//	class USkeletalMeshComponent* Mesh1P;

	///** Gun mesh: 1st person view (seen only by self) */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//	class USkeletalMeshComponent* FP_Gun;

	///** Location on gun mesh where projectiles should spawn. */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//	class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	class UCameraComponent* FirstPersonCameraComponent;
public:
	APlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void Move();

	// ���e�B�N�����W��Ԃ�
	UFUNCTION(BlueprintCallable, Category = "Character")
		FVector2D GetReticleLocation() const;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ASpecterFrontProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	// IDamageListenerInterface�̎���
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void OnDamage(float damage, AController* instigatedBy, AActor* damageCauser);

	// �A�N�V�����t�F�[�Y�J�n���ɌĂяo��
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
		void BeginActionPhase(class AAbstractEnemySpawner* currentSpawner);

	// �A�N�V�����t�F�[�Y�J�n���ɌĂяo�����
	UFUNCTION(BlueprintImplementableEvent, Category = "GameFlow")
		void OnBeginActionPhase(class AAbstractEnemySpawner* currentSpawner);

	// �A�N�V�����t�F�[�Y���A�}�C�t���[���Ăяo��
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
		void TickActionPhase();

	// �A�N�V�����t�F�[�Y���A�}�C�t���[���Ăяo�����
	UFUNCTION(BlueprintImplementableEvent, Category = "GameFlow")
		void OnTickActionPhase();

	// �A�N�V�����t�F�[�Y�I�����ɌĂяo��
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
		void EndActionPhase();

	// �A�N�V�����t�F�[�Y�I�����ɌĂяo�����
	UFUNCTION(BlueprintImplementableEvent, Category = "GameFlow")
		void OnEndActionPhase();

	// ���݂̃J�����R���g���[�����擾
	UFUNCTION(BlueprintCallable, Category = "Player")
		UBaseCameraController* GetCurrentCameraController() { return currentCameraController; }

protected:

	/** Fires a projectile. */
	UFUNCTION(BlueprintNativeEvent, Category = "Player")
		void OnFire();

	void OnFirePressed();
	void OnFireReleased();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	// �}�E�X�̐����ړ�
	void MouseVertical(float rate);

	// �}�E�X�̐����ړ�
	void MouseHorizontal(float rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	* Configures input for touchscreen devices if there is a valid touch interface for doing so
	*
	* @param	InputComponent	The input component pointer to bind controls to
	* @returns true if touch controls were enabled.
	*/
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns FirstPersonCameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float hp;

	// �U����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float power;

	// ���ˊԊu(�b)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		float shootInterval = 0.2f;

	// �Ə����x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		float aimingSpeed;

protected:
	UPROPERTY(BlueprintReadWrite, Category = Camera, meta = (BlueprintProtected))
		class UCameraComponent* cameraComponent;

private:
	// ���ˉ\���Ԃ܂ł��J�E���g�_�E������(0.0f�ȉ��Ȃ甭�ˉ\)
	float shootIntervalCount;

	// ���˓��͂�Tick()�ŏ������邽�߂Ɏg�p
	bool isShootInput;

	// ���e�B�N�����W
	FVector2D reticleLocation;

	// �r���[�|�[�g����}�[�W�����k�߂��G���A���G�C�~���O�G���A�Ƃ���
	const float aimingAreaMargin = 20.0f;

	FVector2D viewPortSize;

	// ���݂̃J�����R���g���[��
	UPROPERTY()
		UBaseCameraController* currentCameraController;

	UPROPERTY()
		class AAbstractEnemySpawner* currentEnemySpawner;

	UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess = "true"))
		FOnHitDelegate onHitDelegate;

	void SetReticleLocation(FVector2D location);
};
