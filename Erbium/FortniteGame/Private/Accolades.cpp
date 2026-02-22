#include "pch.h"
#include "../Public/Accolades.h"
#include "../Public/FortKismetLibrary.h"
#include "../Public/FortQuestManager.h"

void GiveAccolade(AFortPlayerControllerAthena* PC, UFortAccoladeItemDefinition* Def, UFortQuestItemDefinition* QuestDef)
{
	if (!PC || !Def || !PC->XPComponent) 
	{
		printf("[Accolades] GiveAccolade: Invalid parameters\n");
		return;
	}

	printf("[Accolades] GiveAccolade called for: %s\n", Def->Name.ToString().c_str());

	auto Info = (FXPEventInfo*)malloc(FXPEventInfo::Size());
	if (!Info)
	{
		printf("[Accolades] ERROR: Failed to allocate FXPEventInfo\n");
		return;
	}
	memset(Info, 0, FXPEventInfo::Size());

	// Get real PrimaryAssetId for this accolade so the client can display it correctly
	FPrimaryAssetId ID = UKismetSystemLibrary::GetPrimaryAssetIdFromObject(Def);
	Info->Accolade = ID;

	float XpValue = Def->XpRewardAmount.Evaluate();
	if (XpValue == 0)
		UDataTableFunctionLibrary::EvaluateCurveTableRow(Def->XpRewardAmount.Curve.CurveTable, FName(L"Default_Medal"), Def->XpRewardAmount.Value, nullptr, &XpValue, FString());

	Info->EventXpValue = (int32)XpValue;
	Info->RestedValuePortion = Info->EventXpValue;
	Info->RestedXPRemaining = Info->EventXpValue;
	Info->TotalXpEarnedInMatch = Info->EventXpValue + PC->XPComponent->TotalXpEarned;
	Info->Priority = Def->Priority;
	Info->SimulatedText = Def->HasDescription() ? Def->Description : Def->ItemDescription;
	if (FXPEventInfo::HasSimulatedName())
		Info->SimulatedName = Def->HasDisplayName() ? Def->DisplayName : Def->ItemName;
	Info->EventName = Def->Name;
	Info->SeasonBoostValuePortion = 20;
	if (FXPEventInfo::HasPlayerController())
		Info->PlayerController = PC;

	PC->XPComponent->MedalBonusXP += 1250;
	PC->XPComponent->MatchXp += Info->EventXpValue;
	PC->XPComponent->TotalXpEarned += Info->EventXpValue + 1250;

	PC->XPComponent->OnXPEvent(*Info);
	free(Info);

	// Handle AccoladeToReplace
	if (Def->AccoladeToReplace.Num() > 0)
	{
		for (auto& SoftAccoladeToReplace : Def->AccoladeToReplace)
		{
			auto AccoladeToReplace = SoftAccoladeToReplace.Get();
			if (!AccoladeToReplace) continue;
			
			auto AthenaAccoladeIndex = PC->XPComponent->PlayerAccolades.SearchIndex([&](FAthenaAccolades& item)
				{ return item.AccoladeDef == AccoladeToReplace; });

			auto MedalIndex = PC->XPComponent->MedalsEarned.SearchIndex([&](UFortAccoladeItemDefinition* item)
				{ return item == AccoladeToReplace; });

			if (AthenaAccoladeIndex >= 0 && AthenaAccoladeIndex < PC->XPComponent->PlayerAccolades.Num())
				PC->XPComponent->PlayerAccolades.Remove(AthenaAccoladeIndex);

			if (MedalIndex >= 0 && MedalIndex < PC->XPComponent->MedalsEarned.Num())
				PC->XPComponent->MedalsEarned.Remove(MedalIndex);
		}
	}

	// Check if accolade already exists and increment count
	for (auto& AthenaAccolade : PC->XPComponent->PlayerAccolades)
	{
		if (AthenaAccolade.AccoladeDef == Def)
		{
			AthenaAccolade.Count++;
			printf("[Accolades] Accolade count incremented to %d\n", AthenaAccolade.Count);
			return;
		}
	}

	// Create new accolade
	FAthenaAccolades AthenaAccolade{};
	AthenaAccolade.AccoladeDef = Def;
	AthenaAccolade.Count = 1;
	auto str = UEAllocatedWString(L"AthenaAccolade:") + Def->Name.ToWString();
	FString TemplateId;
	TemplateId.Reserve((int)str.size() + 1);
	for (auto& c : str)
	{
		TemplateId.Add(c);
	}
	AthenaAccolade.TemplateId = TemplateId;
	PC->XPComponent->PlayerAccolades.Add(AthenaAccolade);

	if (Def->AccoladeType == 2)
	{
		PC->XPComponent->MedalsEarned.Add(Def);
		PC->XPComponent->ClientMedalsRecived(PC->XPComponent->PlayerAccolades);
	}
	
	printf("[Accolades] GiveAccolade completed successfully\n");
}
