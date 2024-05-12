#include "stdafx.h"
#include "CheatToTestCrash.h"

CheatToTestCrash::CheatToTestCrash()
{
}


CheatToTestCrash::~CheatToTestCrash()
{
}


void CheatToTestCrash::ParseLine(const ArgScript::Line& line)
{
	auto a = Simulator::SpacePlayerData::Get();

	SporeDebugPrint("%x", a->mPlayerEmpireID);
	SporeDebugPrint("%b", a->mpPlayerEmpire != nullptr);
	//auto a = Simulator::SpacePlayerData::Get()->mpPlayerEmpire;
	//Simulator::SpacePlayerData::Get()->mpPlayerEmpire = nullptr;
	//Simulator::SpacePlayerData::Get()->mPlayerEmpireID = 0x0;
	SporeDebugPrint("%b", RelationshipManager.IsAllied((Simulator::cEmpire*)(nullptr),(Simulator::cEmpire*)(nullptr) ));
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
}

const char* CheatToTestCrash::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "CheatToTestCrash: Elaborate description of what this cheat does.";
	}
}
