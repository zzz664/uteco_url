#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#include "Server/Singleton.h"
#include "../LowLib/MultiThreadSync.h"
#include "Server/Thread.h"
#include "Server/UDP_Structure.h"
#include "MyJet.h"
#include "SceneManager.h"
#include "InGameScene.h"

#define DATAMANAGER DataManager::getInstance()

class DataManager : public Singleton<DataManager>, public CMultiThreadSync<DataManager>
{
private:
	InGameScene* scene;
	bool		isGetScene;

public:
	DataManager();
	~DataManager();

	Thread				*thread_;

	BOOL				IsStarted;

	S_PU_C2U_MOVE_TO	mPacket;

	void				SetStarted(BOOL b){ CThreadSync Sync; this->IsStarted = b; }
	BOOL				GetStarted(){ CThreadSync Sync; return IsStarted; }
	void				ReadPacket();
	void				SetPacket(S_PU_C2U_MOVE_TO Packet);

	void				Process();
	void				run();

};

#endif