#include "EvolutionCore.h"
#include "EvolutionSceneManager.h"

#include "TestScene.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	
	EVSystem->RegisterParameter("EvolutionEngine ver 1.0", 800, 800, true, LOG, true);
	EVSystem->Initialize();

	EVSceneManager->ChangeScene(new TestScene);

	EVSystem->ApplicationLoop();

}