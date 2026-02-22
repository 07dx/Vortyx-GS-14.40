#pragma once
#include "../../pch.h"
#include "FortPlayerControllerAthena.h"
#include "FortQuestManager.h"

enum class EAccoladeEvent : uint8
{
	Kill,
	Search,
	MAX
};

inline UFortAccoladeItemDefinition* GetDefFromEvent(EAccoladeEvent Event, int Count, UObject* Object = nullptr)
{
	UFortAccoladeItemDefinition* Def = nullptr;

	switch (Event)
	{
	case EAccoladeEvent::Kill:
		if (Count == 1)
		{
			Def = const_cast<UFortAccoladeItemDefinition*>(FindObject<UFortAccoladeItemDefinition>(L"/Game/Athena/Items/Accolades/AccoladeId_846_vortyx.AccoladeId_846_vortyx"));
		}
		else if (Count == 4)
		{
			Def = const_cast<UFortAccoladeItemDefinition*>(FindObject<UFortAccoladeItemDefinition>(L"/Game/Athena/Items/Accolades/AccoladeId_015_Elimination_Silver.AccoladeId_015_Elimination_Silver"));
		}
		else if (Count == 8)
		{
			Def = const_cast<UFortAccoladeItemDefinition*>(FindObject<UFortAccoladeItemDefinition>(L"/Game/Athena/Items/Accolades/AccoladeId_016_Elimination_Gold.AccoladeId_016_Elimination_Gold"));
		}
		break;
	case EAccoladeEvent::Search:
		if (Count == 3)
		{
			printf("[Accolades] Looking for AccoladeId_008_SearchChests_Bronze for count %d\n", Count);
			Def = const_cast<UFortAccoladeItemDefinition*>(FindObject<UFortAccoladeItemDefinition>(L"/Game/Athena/Items/Accolades/AccoladeId_846_vortyx.AccoladeId_846_vortyx"));
			if (!Def)
			{
				// Try alternative ID format
				Def = const_cast<UFortAccoladeItemDefinition*>(FindObject<UFortAccoladeItemDefinition>(L"/Game/Athena/Items/Accolades/AccoladeId_008_SearchChests_Bronze"));
			}
			if (Def)
				printf("[Accolades] Found AccoladeId_008_SearchChests_Bronze\n");
			else
				printf("[Accolades] ERROR: Could not find AccoladeId_008_SearchChests_Bronze\n");
		}
		else if (Count == 7)
		{
			printf("[Accolades] Looking for AccoladeId_009_SearchChests_Silver for count %d\n", Count);
			Def = const_cast<UFortAccoladeItemDefinition*>(FindObject<UFortAccoladeItemDefinition>(L"/Game/Athena/Items/Accolades/AccoladeId_009_SearchChests_Silver.AccoladeId_009_SearchChests_Silver"));
			if (!Def)
			{
				// Try alternative ID format
				Def = const_cast<UFortAccoladeItemDefinition*>(FindObject<UFortAccoladeItemDefinition>(L"/Game/Athena/Items/Accolades/AccoladeId_009_SearchChests_Silver"));
			}
			if (Def)
				printf("[Accolades] Found AccoladeId_009_SearchChests_Silver\n");
			else
				printf("[Accolades] ERROR: Could not find AccoladeId_009_SearchChests_Silver\n");
		}
		else if (Count == 12)
		{
			printf("[Accolades] Looking for AccoladeId_010_SearchChests_Gold for count %d\n", Count);
			Def = const_cast<UFortAccoladeItemDefinition*>(FindObject<UFortAccoladeItemDefinition>(L"/Game/Athena/Items/Accolades/AccoladeId_010_SearchChests_Gold.AccoladeId_010_SearchChests_Gold"));
			if (!Def)
			{
				// Try alternative ID format
				Def = const_cast<UFortAccoladeItemDefinition*>(FindObject<UFortAccoladeItemDefinition>(L"/Game/Athena/Items/Accolades/AccoladeId_010_SearchChests_Gold"));
			}
			if (Def)
				printf("[Accolades] Found AccoladeId_010_SearchChests_Gold\n");
			else
				printf("[Accolades] ERROR: Could not find AccoladeId_010_SearchChests_Gold\n");
		}
		break;
	case EAccoladeEvent::MAX:
		break;
	default:
		break;
	}

	return Def;
}

void GiveAccolade(AFortPlayerControllerAthena* PC, UFortAccoladeItemDefinition* Def, UFortQuestItemDefinition* QuestDef = nullptr);
