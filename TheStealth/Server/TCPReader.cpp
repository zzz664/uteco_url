#include "DXUT.h"
#include "TCPReader.h"
#include "ServerManager.h"
#include "../SceneManager.h"
#include "../RoomScene.h"
#include "../Def.h"
#include "../InGameScene.h"
#include "../DataManager.h"

TCPReader::TCPReader(CUserSession* session)
{
	this->mSession = session;
	dwProtocol = dwPacketLength = 0;
	*Packet = { 0, };
}

TCPReader::~TCPReader()
{
	SAFE_DELETE(thread_);
}

void TCPReader::excute()
{
	CThreadSync Sync;

	dwProtocol = dwPacketLength = 0;
	*Packet = { 0, };

	BYTE WriteBuffer[MAX_BUFFER_LENGTH] = { 0, };

	if (mSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
		if (dwProtocol == PT_ROOM_START_M) {
			printf("ROOM_STRT_M");
			READ_PACKET(PT_ROOM_START_M);
			ServerManager::getInstance().StartUserUdpIocp();
			return;
		}
		else if (dwProtocol == PT_GAME_START_M){
			printf("GAME START M");
			ServerManager::getInstance().userIocp->StartMoveThread();
		}
		else if (dwProtocol == PT_GAME_ALL_LOAD_COMPLETE_M)
		{
			printf("GAME ALL LOAD M");

			SceneManager->SetScene(INGAME);
			//MoveThread
			DATAMANAGER.run();
		}
		else if (dwProtocol == PT_C2U_KILL_USER_M)
		{
			printf("KILL M");
			READ_PACKET(PT_C2U_KILL_USER_M);
			printf("Kill : %d Death : %d", Data.USEROID, Data.TARGETID);
			InGameScene* scene = (InGameScene*)SceneManager->GetCurrentScene();
			scene->killLog->SetLog(wstToStr(ServerManager::getInstance().matches[Data.USEROID]), wstToStr(ServerManager::getInstance().matches[Data.TARGETID]));
		}
		else if (dwProtocol == PT_ROOT_GAME_START)
		{
			printf("Root Game Start\n");
		}
		else if (dwProtocol == PT_LOBBY_ENTER_M)
		{
			READ_PACKET(PT_LOBBY_ENTER_M);
			printf("LOBBY ENTER M\n");
			printf("Lobby Enter : %s\n", Data.NICKNAME);
			/*LobbyScene* scene = (LobbyScene*)world.currentScene;

			if (scene);
			{
			scene->addUser(Data.NICKNAME);
			}*/
		}
		else if (dwProtocol == PT_CHANNEL_CHATTING_M)
		{
			printf("CHANNEL_CHATTING_M\n");
			READ_PACKET(PT_CHANNEL_CHATTING_M);
			if (!ServerManager::getInstance().GetStatus() == US_CHANNEL_ENTERED) return;

		}
		else if (dwProtocol == PT_ROOM_ENTER_M)
		{
			printf("ROOM ENter M \n");
			READ_PACKET(PT_ROOM_ENTER_M);

			if (!lstrcmp(ServerManager::getInstance().NickName, Data.NICKNAME)) return;
			RoomScene* p = (RoomScene*)SceneManager->GetCurrentScene();
			p->GetSlot(Data.SLOT_INDEX)->SetSlotCaption(wstToStr(Data.NICKNAME).c_str());

			if (!ServerManager::getInstance().GetStatus() == US_ROOM_ENTERED) return;

		}
		else if (dwProtocol == PT_ROOM_CHATTING_M)
		{
			printf("ROOM CHATTING M \n");
			READ_PACKET(PT_ROOM_CHATTING_M);

			wstring msg;
			msg.append(Data.NICKNAME);
			msg.append(L" :");
			msg.append(Data.CHAT);
			
			printf("%s", msg.c_str());

			if (SceneManager->GetIsIngame())
			{
				InGameScene* p = (InGameScene*)SceneManager->GetCurrentScene();
				p->GetChatForm()->SetChatLog(wstToStr(msg.c_str()));
			}

			else
			{
				RoomScene* p = (RoomScene*)SceneManager->GetCurrentScene();
				p->GetChatForm()->SetChatLog(wstToStr(msg.c_str()));
			}

		}
		else if (dwProtocol == PT_ROOM_TEAM_CHANGE_M)
		{
		}

		else if (dwProtocol == PT_ROOM_READY_M)
		{
			printf("Room Ready M \n");
			READ_PACKET(PT_ROOM_READY_M);

			if (ServerManager::getInstance().GetStatus() != US_ROOM_ENTERED) return;

			if (Data.OID != ServerManager::getInstance().Oid)
			{

			}
			else return;
		}
		else if (dwProtocol == PT_ROOM_LEAVE_M)
		{
			printf("Room Leave");
			READ_PACKET(PT_ROOM_LEAVE_M);

			ServerManager::getInstance().GetReqInfo();
		}
	}
}

void TCPReader::process()
{
	while (TRUE)
	{
		this->excute();
		Sleep(20);
	}
}

void TCPReader::run()
{
	thread_ = MAKE_THREAD(TCPReader, process);
}
