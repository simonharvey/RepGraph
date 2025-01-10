#include "TutorialPlayerState.h"

#include "TutorialRepGraph.h"
#include "Net/UnrealNetwork.h"


void ATutorialPlayerState::OnRep_Team(int32 OldTeam) const
{
	UE_LOG(LogTemp, Warning, TEXT("OnRep_Team %i -> %i"), OldTeam, Team);
	
	OnTeamChange.Broadcast(Team);
}

void ATutorialPlayerState::SetTeam_Implementation(int32 InTeam)
{
	Team = InTeam;
	if (const UWorld* World = GetWorld())
	{
		if (const UNetDriver* NetworkDriver = World->GetNetDriver())
		{
			if (UTutorialRepGraph* RepGraph = NetworkDriver->GetReplicationDriver<UTutorialRepGraph>())
			{
				RepGraph->SetTeamForPlayerController(GetPlayerController(), Team);
			}
		}
	}
}

void ATutorialPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		static int32 NextTeam = 0;

		Team = NextTeam;
		NextTeam = (NextTeam+1)%2;
		
		//Team = FMath::RandBool() ? 0 : 1;
		
		if (const UWorld* World = GetWorld())
		{
			if (const UNetDriver* NetworkDriver = World->GetNetDriver())
			{
				if (UTutorialRepGraph* RepGraph = NetworkDriver->GetReplicationDriver<UTutorialRepGraph>())
				{
					RepGraph->SetTeamForPlayerController(GetPlayerController(), Team);
				}
			}
		}
	}
}

void ATutorialPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Team);
}
