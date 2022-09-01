#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CreatureOasis/Interfaces/CreatureComponentLoadableInterface.h"
#include "CreatureAppearanceComponent.generated.h"

struct FGradualEvolutionDataSingleEntry;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREATUREOASIS_API UCreatureAppearanceComponent : public UActorComponent, public ICreatureComponentLoadableInterface
{
	GENERATED_BODY()

public:	
	UCreatureAppearanceComponent();

protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SetEvolutionStateTag(const FGameplayTag InEvolutionStateTag, const bool bRegenerateMesh = true);
	
	UFUNCTION(BlueprintCallable)
	FGameplayTag GetEvolutionStateTag() const;
	
	void SetSkeletalMesh(USkeletalMeshComponent* NewMesh);

	void RegenerateMesh();
	void ClearAttributeListeners();
	
	UMaterialInstanceDynamic* CreateAndSetMaterialInstanceDynamic(const FName MaterialName) const;
	void PrepareMaterialInstances();

	void AlterMaterialUsingData(const FGradualEvolutionDataSingleEntry& InDataEntry, const float Scale) const;
	
	// Begin ICreatureComponentLoadableInterface
	virtual void LoadCreatureData_Implementation(const FCreatureDataLoad& CreatureDataLoad) override;
	virtual void GatherCreatureData_Implementation(FCreatureDataLoad& CreatureDataLoad) override;
	// End ICreatureComponentLoadableInterface
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> DefaultChaoAnimClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> DefaultEggAnimClass;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetColorTag(const FGameplayTag InColorTag, const FLinearColor InCustomPrimaryColor = FLinearColor(0.f, 0.f, 0.f, 0.f), const FLinearColor InCustomSecondaryColor = FLinearColor(0.f, 0.f, 0.f, 0.f));

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetColorTag() const;
	
	UFUNCTION(BlueprintCallable)
	void SetPrimaryColor(const FLinearColor NewColor) const;
	
	UFUNCTION(BlueprintCallable)
	void SetSecondaryColor(const FLinearColor NewColor) const;

	
private:
	UPROPERTY()
	class ACreatureCharacter* CreatureCharacter;

	UPROPERTY()
	class USkeletalMeshComponent* CreatureMesh;

	UPROPERTY()
	FLinearColor InitialPrimaryColor;
	
	UPROPERTY()
	FLinearColor InitialSecondaryColor;
	
	UPROPERTY(EditInstanceOnly, Category="Overrideables")
	FGameplayTag ColorTag;
	UPROPERTY(EditInstanceOnly, Category="Overrideables")
	FGameplayTag EvolutionStateTag;
	
	UPROPERTY()
	FGameplayTag EggStateTag;

	TArray<FDelegateHandle> AttributeListenerHandles;

	UPROPERTY()
	UMaterialInstanceDynamic* BellyMaterialInstance;
};
