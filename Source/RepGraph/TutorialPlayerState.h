#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TutorialPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTeamChangeDelegate, int32, Team);

UCLASS()
class REPGRAPH_API ATutorialPlayerState : public APlayerState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FTeamChangeDelegate OnTeamChange;
	
public:
	//UPROPERTY(BlueprintReadOnly, Replicated) // orig
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_Team)//, Setter=SetTeam)
	int32 Team = -1;

	UFUNCTION()
	void OnRep_Team(int32 OldTeam) const;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetTeam(int32 InTeam);
	/*{
		Team = InTeam;
	}*/

	// on server
	void SetTeam_Implementation(int32 InTeam);

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
