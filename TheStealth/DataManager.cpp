#include "DXUT.h"
#include "DataManager.h"
#include "Server\ServerManager.h"

DataManager::DataManager(){
	IsStarted = false;
}

DataManager::~DataManager() { SAFE_DELETE(thread_); }

void DataManager::ReadPacket()
{
	CThreadSync Sync;

	USER_MOVE_TO_DATA Data[8];

	memcpy(Data, mPacket.USER, sizeof(USER_MOVE_TO_DATA) * 8);

	for (int i = 0; i < 8; i++)
	{
		//if (Data[i].isAlive == false) { continue; scene->player[i]->isExist = false; }
		if (ServerManager::getInstance().Oid == Data[i].Oid)
		{
			scene->jet->info.HP = Data[i].HP;
			scene->jet->info.Oid = Data[i].Oid;
			scene->jet->info.IsAlive = Data[i].IsAlive;

			scene->player[i]->isExist = false;	
			scene->jet->slot = i;
			continue;
		}

		if (Data[i].Oid >= 1)
		{
			scene->player[i]->info = Data[i];
			scene->player[i]->isExist = true;
		}
		else
		{
			scene->player[i]->isExist = false;
		}
	}
}

void DataManager::SetPacket(S_PU_C2U_MOVE_TO Packet)
{
	CThreadSync Sync;

	mPacket = Packet;
}

void DataManager::Process()
{
	while (TRUE)
	{
		if (mPacket.USER[0].Oid != NULL && SceneManager->currentSceneNum == INGAME)
		{
			if (!isGetScene)
			{
				scene = (InGameScene*)SceneManager->GetCurrentScene();
				isGetScene = true;
			}
			ReadPacket();
		}
	}
}

void DataManager::run()
{
	thread_ = MAKE_THREAD(DataManager, Process);
	isGetScene = false;
}
