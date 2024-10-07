#pragma once

#include "../../libs/DXUT/Core/DXUT.h"
#include "Singleton.h"
#include "UserSession.h"
#include "TCPManager.h"
#include "UserUdpIocp.h"
#include "HostUdpIocp.h"
#include "../DxObject.h"
#include "../MyJet.h"
#include <map>

class ServerManager : public Singleton<ServerManager>
{

public:
	ServerManager();
	~ServerManager();


	CHostUdpIocp*			hostIocp;
	CUserUdpIocp*			userIocp;
	CUserSession*			mUserSession;
	BOOL					isHost;
	INT						mySlot;
	WCHAR					UserId[32];
	WCHAR					NickName[32];
	INT						Oid;
	MyJet*					Player;
	BOOL					isFired;
	map<INT, WCHAR[16]>		matches;

	VOID	Release();
	VOID	Initialize();
	BOOL	StartServer(){
		WSADATA WsaData;
		WSAStartup(MAKEWORD(2, 2), &WsaData);
		mUserSession = new CUserSession();
		if (mUserSession->BeginTcp("211.189.19.92", DEFAULT_PORT))
			return TRUE; 
		else return FALSE;
	}


	USER_STATUS GetStatus(){ return mStatus; }
	BOOL	SetPlayer(MyJet* player){ this->Player = player; return TRUE; }
	MyJet*  GetPlayer(){ return this->Player; }
	BOOL	SetStatus(USER_STATUS status){ this->mStatus = status; return TRUE; }
	BOOL	Login(WCHAR* id, WCHAR* pwd);
	BOOL	SIGNUP(WCHAR* id, WCHAR* pwd);
	BOOL	Query(WCHAR* id);
	BOOL	GetNickName();
	BOOL	QueryNickName(WCHAR* nick);
	BOOL	InsertNickName(WCHAR* nick);
	BOOL	EnterLobby();
	BOOL	CreateRoom(WCHAR* title);
	BOOL	EnterRoom(DWORD roomId);
	BOOL	LeaveRoom();
	BOOL	GetReqInfo();
	BOOL	WriteToPacket(LPCSTR remoteAddress, DWORD remotePort, DWORD Protocol, const BYTE *packet, DWORD packetLength);
	BOOL	WriteToPacket(DWORD Protoocol, const BYTE *packet, DWORD packetLength);
	BOOL	StartHostUdpIocp(){ SetIsHost(true); this->hostIocp = new CHostUdpIocp(1820); if (!hostIocp->Begin()) {/*CLog::WriteLogNoDate(L"Host Server Open Error!");*/ } else { /*CLog::WriteLogNoDate(L"Host Server OPEN Success!!!!!!!!!!\n");*/  return TRUE; } }
	BOOL	StartUserUdpIocp(){ if (!isHost) { /*CLog::WriteLogNoDate(L"Create UserIocp");*/ this->userIocp = new CUserUdpIocp(1820); } else return FALSE; if (!userIocp->Begin()) {/*CLog::WriteLogNoDate(L"User Server Open Error!");*/ } else return TRUE; }
	ROOM_INFO_DATA*	GetRoomsInfo();
	BOOL	LobbyChatting(WCHAR* chatting);
	BOOL	RoomChatting(WCHAR* chatting);
	BOOL	GameIntroComplete();
	BOOL	GameStart();
	USER_INFO_DATA*	GetUsersInfo(); //
	BOOL	TeamChange(BOOL Team, USHORT& slotIndex);
	BOOL	ReadyRoom(BOOL isReady);
	VOID	SetIsHost(BOOL isHost){ this->isHost = isHost; }

	BOOL	Regen();

private:
	BYTE					WriteBuffer[MAX_BUFFER_LENGTH];
	BYTE					Packet[MAX_BUFFER_LENGTH];
	DWORD					dwProtocol;
	DWORD					dwPacketLength;
	TCPReader*				reader;
	USER_STATUS				mStatus;
};