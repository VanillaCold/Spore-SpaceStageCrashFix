// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
//#include "CheatToTestCrash.h"

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
	//CheatManager.AddCheat("CheatToTestCrash", new CheatToTestCrash());
}

void Dispose()
{
	// This method is called when the game is closing
}

member_detour(RelationshipManagerFixDetour, Simulator::cRelationshipManager, bool(Simulator::cEmpire*, Simulator::cEmpire*))
{
	bool detoured(Simulator::cEmpire* param1, Simulator::cEmpire * param2)
	{
		if (param1 == nullptr || param2 == nullptr)
		{
			App::ConsolePrintF("Avoided possible crash?");
			return false;
		}
		else
		{
			return original_function(this, param1, param2);
		}
	}
};

void AttachDetours()
{
	RelationshipManagerFixDetour::attach(GetAddress(Simulator::cRelationshipManager, IsAllied));
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

