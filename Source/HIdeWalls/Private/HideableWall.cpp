// Fill out your copyright notice in the Description page of Project Settings.

#include "HIdeWalls.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "HideableWall.h"


// Sets default values
AHideableWall::AHideableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer")));

	WallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh Component"));

	if (meshToUse && WallMeshComponent) {
		WallMeshComponent->SetStaticMesh(meshToUse);
	}

	ShouldHide = false;
	ShouldShow = false;
	FinalFadeAmount = 0.1f; // Minimum Opacity
	CurrentFade = 1.0f;		// Maximum Opacity by default
	FadeRate = 2.0f;		// Rate at which to fade between max and min opacity

	static ConstructorHelpers::FObjectFinder<UMaterial> t_Mat(TEXT("Material'/Game/Geometry/Meshes/CubeMaterial_Transluscent.CubeMaterial_Transluscent'"));
	if (t_Mat.Object != NULL) {
		transluscentMaterial = t_Mat.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> o_Mat(TEXT("Material'/Game/Geometry/Meshes/CubeMaterial.CubeMaterial'"));
	if (o_Mat.Object != NULL) {
		opaqueMaterial = o_Mat.Object;
	}
}

// Called when the game starts or when spawned
void AHideableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHideableWall::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (ShouldHide) {
		CurrentFade -= DeltaTime * FadeRate;

		if (CurrentFade < FinalFadeAmount) {
			CurrentFade = FinalFadeAmount;
			ShouldHide = false;
		}
		WallMeshComponent->CreateAndSetMaterialInstanceDynamic(0)->SetScalarParameterValue(TEXT("Opacity"), CurrentFade);
	}
	else if (ShouldShow) {
		CurrentFade += DeltaTime * FadeRate;

		if (CurrentFade > 1.0f) {
			CurrentFade = 1.0f;
			ShouldShow = false;
			ChangeMeshMaterialToOpaque();
		}
		WallMeshComponent->CreateAndSetMaterialInstanceDynamic(0)->SetScalarParameterValue(TEXT("Opacity"), CurrentFade);
	}
}

void AHideableWall::ChangeMeshMaterialToOpaque() {
	if (opaqueMaterial) {
		UMaterialInstanceDynamic* opaqueMaterial_Dynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, opaqueMaterial);
		WallMeshComponent->SetMaterial(0, opaqueMaterial_Dynamic);
	}
}

void AHideableWall::ChangeMeshMaterialToTransluscent() {
	if (transluscentMaterial) {
		UMaterialInstanceDynamic* transluscentMaterial_Dynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, transluscentMaterial);
		transluscentMaterial_Dynamic->SetScalarParameterValue(TEXT("Opacity"), CurrentFade);
		WallMeshComponent->SetMaterial(0, transluscentMaterial_Dynamic);
	}
}

void AHideableWall::HideWall() {
	if (!ShouldHide) {
		ShouldShow = false;
		ShouldHide = true;
		
		ChangeMeshMaterialToTransluscent();
	}
}

void AHideableWall::ShowWall() {
	if (!ShouldShow) {
		ShouldShow = true;
		ShouldHide = false;
	}
}