// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HideableWall.generated.h"

UCLASS()
class HIDEWALLS_API AHideableWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHideableWall();

	UPROPERTY(BlueprintReadOnly, Category = Display)
		bool ShouldHide;

	UPROPERTY(BlueprintReadOnly, Category = Display)
		bool ShouldShow;

	UPROPERTY(EditAnywhere, Category = Display)
		float FinalFadeAmount;

	UPROPERTY(EditAnywhere, Category = Display)
		float CurrentFade;

	UPROPERTY(EditAnywhere, Category = Display)
		float FadeRate;

	UPROPERTY(EditAnywhere, Category = Material)
		UMaterial* transluscentMaterial;

	UPROPERTY(EditAnywhere, Category = Material)
		UMaterial* opaqueMaterial;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetWallMeshComponent() const { return WallMeshComponent; }

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void HideWall();

	virtual void ShowWall();
	
private:
	/** Wall Mesh */
	UPROPERTY(EditAnywhere, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WallMeshComponent;
	
	virtual void ChangeMeshMaterialToOpaque();

	virtual void ChangeMeshMaterialToTransluscent();
};
