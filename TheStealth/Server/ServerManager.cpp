#include "DXUT.h"
#include "ServerManager.h"
#include "HostUdpIocp.h"
#include "../SceneManager.h"
#include "../RoomScene.h"
#include "../Def.h"

ServerManager::ServerManager()
{
	StartServer();
	reader = new TCPReader(mUserSession);
	reader->run();
	Initialize();
	ZeroMemory(UserId, sizeof(sizeof(WCHAR)* 32));
	isFired = false;
}
ServerManager::~ServerManager() {}
VOID ServerManager::Release()
{
	WSACleanup();
	mUserSession->End();
	SAFE_DELETE(reader);
	delete mUserSession;
}
VOID ServerManager::Initialize()
{
	*WriteBuffer = { 0, };
	dwProtocol = dwPacketLength = 0;
	*Packet = { 0, };
}
BOOL ServerManager::Login(WCHAR* id, WCHAR* pwd)
{
	Initialize();
	mUserSession->WritePacket(PT_LOGIN_USER,
		WriteBuffer,
		WRITE_PT_LOGIN_USER(
		WriteBuffer,
		id,
		pwd));

	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_LOGIN_USER_SUCC_U) {
				printf("Success\n");
				memcpy(this->UserId, id, sizeof(UserId));
				READ_PACKET(PT_LOGIN_USER_SUCC_U);
				this->Oid = Data.OID;
				return TRUE;
			}
			else if (dwProtocol == PT_LOGIN_USER_FAIL_U){
				printf("ばばばばばばばばばばば\n");
				return FALSE;
			}
			else continue;
		}
	}
}
BOOL ServerManager::Query(WCHAR* id)
{
	Initialize();
	mUserSession->WritePacket(PT_QUERY_USER, WriteBuffer,
		WRITE_PT_QUERY_USER(WriteBuffer,
		id));

	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_QUERY_USER_SUCC_U) {
				printf("Query Success");
				return TRUE;
			}
			else if (dwProtocol == PT_QUERY_USER_FAIL_U){
				printf("Query Fail");
				return FALSE;
			}
			else continue;
		}

	}
	return NULL;
}
BOOL ServerManager::SIGNUP(WCHAR* id, WCHAR* pwd)
{
	Initialize();
	mUserSession->WritePacket(PT_SIGN_UP_USER,
		WriteBuffer,
		WRITE_PT_SIGN_UP_USER(
		WriteBuffer,
		id,
		pwd));

	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_SIGN_UP_USER_SUCC_U) {
				printf("SUCKSEXX\n");
				return TRUE;
			}
			else if (dwProtocol == PT_SIGN_UP_USER_FAIL_U){
				printf("ばばばばばばばばばばばば\n");
				return FALSE;
			}
			else continue;
		}
	}

	return FALSE;
}


BOOL ServerManager::CreateRoom(WCHAR* title)
{
	mUserSession->WritePacket(PT_ROOM_CREATE,
		WriteBuffer,
		WRITE_PT_ROOM_CREATE(WriteBuffer,
		title));

	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_ROOM_CREATE_SUCC_U) {
				_tprintf(_T("SUCCESS!!"));
				READ_PACKET(PT_ROOM_CREATE_SUCC_U);

				return TRUE;
			}
			else if (dwProtocol == PT_ROOM_CREATE_FAIL_U){
				_tprintf(_T("Fail to create room"));
				return FALSE;
			}
			else continue;
		}
	}
	return NULL;
}

BOOL ServerManager::EnterLobby()
{
	mUserSession->WritePacket(PT_LOBBY_ENTER,
		WriteBuffer,
		WRITE_PT_LOBBY_ENTER(
		WriteBuffer));

	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_LOBBY_ENTER_SUCC_U){
				_tprintf(_T("SUCCESS!"));
				return TRUE;
			}
			else if (dwProtocol == PT_LOBBY_ENTER_FAIL_U)
			{
				_tprintf(_T("Fail to enter room"));
				return FALSE;
			}
			else continue;
		}
	}

	return FALSE;

}

BOOL ServerManager::EnterRoom(DWORD roomId)
{
	mUserSession->WritePacket(PT_ROOM_ENTER,
		WriteBuffer,
		WRITE_PT_ROOM_ENTER(
		WriteBuffer,
		roomId));

	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_ROOM_ENTER_SUCC_U){
				READ_PACKET(PT_ROOM_ENTER_SUCC_U);

				printf("\na\n");
				_tprintf(_T("SUCCESS!"));
				return TRUE;
			}
			else if (dwProtocol == PT_ROOM_ENTER_FAIL_U)
			{
				_tprintf(_T("Fail to enter room"));
				return FALSE;
			}
			else continue;
		}
	}
	return FALSE;
}

BOOL ServerManager::TeamChange(BOOL Team, USHORT& slotIndex)
{
	mUserSession->WritePacket(PT_ROOM_TEAM_CHANGE,
		WriteBuffer,
		WRITE_PT_ROOM_TEAM_CHANGE(
		WriteBuffer,
		Team));

	while (TRUE)
	{
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_ROOM_TEAM_CHANGE_SUCC_U) {
				_tprintf(_T("SUCCESS to change team"));
				READ_PACKET(PT_ROOM_TEAM_CHANGE_SUCC_U);
				slotIndex = Data.SLOT_INDEX;
				return TRUE;
			}
			else if (dwProtocol == PT_ROOM_TEAM_CHANGE_FAIL_U){
				_tprintf(_T("Fail to change team"));
				return FALSE;
			}
			else continue;
		}
	}
	return NULL;
}

ROOM_INFO_DATA* ServerManager::GetRoomsInfo()
{
	mUserSession->WritePacket(PT_ROOM_INFO_REQ,
		WriteBuffer,
		WRITE_PT_ROOM_INFO_REQ(WriteBuffer));

	while (TRUE)
	{
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_ROOM_INFO_REQ_SUCC_U) {
				_tprintf(_T("SUCCESS to room req info"));
				READ_PACKET(PT_ROOM_INFO_REQ_SUCC_U);
				return Data.ROOMS;
			}
			else if (dwProtocol == PT_ROOM_INFO_REQ_FAIL_U){
				_tprintf(_T("Fail to Req info"));
				return NULL;
			}
			else continue;
		}
	}
	return NULL;
}

BOOL ServerManager::GameStart()
{
	mUserSession->WritePacket(PT_ROOM_START,
		WriteBuffer,
		WRITE_PT_ROOM_START(WriteBuffer));

	return TRUE;
}

BOOL ServerManager::ReadyRoom(BOOL isReady)
{
	mUserSession->WritePacket(PT_ROOM_READY,
		WriteBuffer,
		WRITE_PT_ROOM_READY(
		WriteBuffer,
		isReady));

	while (TRUE)
	{
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_ROOM_READY_SUCC_U) {
				_tprintf(_T("SUCCESS to room req info"));
			}
			else if (dwProtocol == PT_ROOM_READY_FAIL_U){
				_tprintf(_T("Fail to Req info"));
				return NULL;
			}
			else continue;
		}
	}
}

BOOL ServerManager::LeaveRoom()
{
	mUserSession->WritePacket(PT_ROOM_LEAVE,
		WriteBuffer,
		WRITE_PT_ROOM_LEAVE(
		WriteBuffer));

	while (TRUE)
	{
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_ROOM_LEAVE_SUCC_U) {
				_tprintf(_T("SUCCESS to leave succ"));
				return TRUE;
			}
			else if (dwProtocol == PT_ROOM_LEAVE_FAIL_U){
				_tprintf(_T("Fail to leave room"));
				return NULL;
			}
			else continue;
		}
	}
}

BOOL ServerManager::LobbyChatting(WCHAR* chatting)
{
	mUserSession->WritePacket(PT_CHANNEL_CHATTING,
		WriteBuffer,
		WRITE_PT_CHANNEL_CHATTING(WriteBuffer,
		chatting));

	return TRUE;
}

BOOL ServerManager::RoomChatting(WCHAR* chatting)
{
	mUserSession->WritePacket(PT_ROOM_CHATTING,
			WriteBuffer,
			WRITE_PT_ROOM_CHATTING(
			WriteBuffer,
			chatting));
	
	printf("Chatting\n");


	return TRUE;
}

USER_INFO_DATA* ServerManager::GetUsersInfo()
{
	mUserSession->WritePacket(PT_USER_INFO_REQ,
		WriteBuffer,
		WRITE_PT_USER_INFO_REQ(WriteBuffer));

	while (TRUE)
	{
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_USER_INFO_REQ_SUCC_U) {
				_tprintf(_T("SUCCESS to room req info"));
				READ_PACKET(PT_USER_INFO_REQ_SUCC_U);
				return Data.DATA;
			}
			else if (dwProtocol == PT_USER_INFO_REQ_FAIL_U){
				_tprintf(_T("Fail to Req info"));
				return NULL;
			}
			else continue;
		}
	}

}

BOOL ServerManager::GetReqInfo()
{
	mUserSession->WritePacket(PT_ROOM_REQ_INFO,
		WriteBuffer,
		WRITE_PT_ROOM_REQ_INFO(WriteBuffer));

	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_ROOM_REQ_INFO_SUCC_U) {
				_tprintf(_T("SUCCESS to req info"));
				READ_PACKET(PT_ROOM_REQ_INFO_SUCC_U);
				//CLog::WriteLog(L"Title : %s, %d, %d", Data.TITLE, Data.CURRENT_USER_COUNT, Data.ROOM_INDEX);
				int i = -1;

				RoomScene* p = (RoomScene*)SceneManager->GetCurrentScene();

				p->SetTitle(wstToStr(Data.TITLE));

				for each (SLOT_USER_DATA user in Data.DATA)
				{
					i++;

					string name = wstToStr(user.NickName);
					
					if (name.length() <= 1)
					{
						p->GetSlot(i)->SetSlotCaption("");
						
						// Set Oid Zero
						p->GetSlot(i)->SetUserId(NULL);
						continue;
					}
					if (i == 0)
					{
						p->GetSlot(i)->SetHost(true);
					}

					p->GetSlot(i)->SetSlotCaption(name.c_str());
					lstrcpy(matches[user.Oid], user.NickName);
					//matches.insert(map<INT, WCHAR[16]>::value_type(user.Oid, user.NickName));
					
					// Set User Oid
					p->GetSlot(i)->SetUserId(user.Oid);
					
					if (user.Oid == this->Oid) continue;
				}
				return TRUE;
			}
			else if (dwProtocol == PT_ROOM_REQ_INFO_FAIL_U){
				_tprintf(_T("Fail to Req info"));
				return FALSE;
			}
			else continue;
		}
	}
	return NULL;
}


BOOL ServerManager::GetNickName()
{
	mUserSession->WritePacket(PT_CHANNEL_NICKNAME,
		WriteBuffer,
		WRITE_PT_CHANNEL_NICKNAME(
		WriteBuffer,
		this->UserId));


	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_CHANNEL_NICKNAME_SUCC_U){
				READ_PACKET(PT_CHANNEL_NICKNAME_SUCC_U);
				_tprintf(_T("SUCCESS!"));
				printf("%s", Data.NICK_NAME);
				memcpy(this->NickName, Data.NICK_NAME, sizeof(WCHAR) * 32);
				return TRUE;
			}
			else if (dwProtocol == PT_CHANNEL_NICKNAME_FAIL_U)
			{
				READ_PACKET(PT_CHANNEL_NICKNAME_FAIL_U);
				_tprintf(_T("Fail to channel nickname"));
				return FALSE;
			}
			else continue;
		}
	}
	return NULL;
}

BOOL ServerManager::QueryNickName(WCHAR* nick)
{
	mUserSession->WritePacket(PT_QUERY_NICKNAME,
		WriteBuffer,
		WRITE_PT_QUERY_NICKNAME(WriteBuffer,
		nick));

	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_QUERY_NICKNAME_SUCC_U){
				_tprintf(_T("SUCCESS!"));
				return TRUE;
			}
			else if (dwProtocol == PT_QUERY_NICKNAME_FAIL_U)
			{
				_tprintf(_T("Fail to enter room"));
				return FALSE;
			}
			else continue;
		}
	}
}

BOOL ServerManager::InsertNickName(WCHAR* nick)
{
	mUserSession->WritePacket(PT_INSERT_NICKNAME,
		WriteBuffer,
		WRITE_PT_INSERT_NICKNAME(WriteBuffer,
		UserId,
		nick));


	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_INSERT_NICKNAME_SUCC_U){
				memcpy(this->NickName, nick, sizeof(WCHAR) * 32);
				_tprintf(_T("SUCCESS!"));
				return TRUE;
			}
			else if (dwProtocol == PT_INSERT_NICKNAME_FAIL_U)
			{
				_tprintf(_T("Fail to enter room"));
				return FALSE;
			}
			else continue;
		}
	}
}

BOOL ServerManager::WriteToPacket(LPCSTR remoteAddress, DWORD remotePort, DWORD Protoocol, const BYTE *packet, DWORD packetLength)
{
	if (isHost)
	{
		return hostIocp->mUdpSession.WriteToPacket(remoteAddress, remotePort, Protoocol, packet, packetLength);
	}
	else
	{
		return userIocp->mUdpSession.WriteToPacket(remoteAddress, remotePort, Protoocol, packet, packetLength);
	}
}


BOOL ServerManager::WriteToPacket(DWORD Protoocol, const BYTE *packet, DWORD packetLength)
{
	return mUserSession->WriteToPacket(DEFAULT_ADDRESS, DEFAULT_PORT, Protoocol, packet, packetLength);
}

BOOL ServerManager::GameIntroComplete()
{
	mUserSession->WritePacket(PT_GAME_INTRO_COMPLETE,
		WriteBuffer,
		WRITE_PT_GAME_INTRO_COMPLETE(
		WriteBuffer));


	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_GAME_INTRO_COMPLETE_SUCC_U)
			{
				_tprintf(_T("SUCCESS!"));
				return TRUE;
			}
			else if (dwProtocol == PT_GAME_INTRO_COMPLETE_FAIL_U)
			{
				_tprintf(_T("Fail to intro game"));
				return FALSE;
			}
			else continue;
		}
	}
}

BOOL ServerManager::Regen()
{
	mUserSession->WritePacket(PT_U2C_REGEN_USER,
		WriteBuffer,
		WRITE_PT_U2C_REGEN_USER(
		WriteBuffer));

	while (TRUE){
		if (!mUserSession->ReadPacket(dwProtocol, Packet, dwPacketLength)){
			if (dwProtocol == PT_C2U_REGEN_USER_SUCC_U)
			{
				_tprintf(_T("SUCCESS!"));
				return TRUE;
			}
			else if (dwProtocol == PT_C2U_REGEN_USER_FAIL_U)
			{
				_tprintf(_T("Fail to Regen User"));
				return FALSE;
			}
			else continue;
		}
	}
}