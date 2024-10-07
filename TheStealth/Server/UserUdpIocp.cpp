#include "DXUT.h"
#include "UserUdpIocp.h"
#include "ServerManager.h"
#include "UDP_WritePacket.h"
#include "../DataManager.h"

DWORD WINAPI Reset2ThreadCallback(LPVOID parameter)
{
	CUserUdpIocp* Owner = (CUserUdpIocp*)parameter;
	Owner->Reset2ThreadCallback();

	return 0;
}

DWORD WINAPI MoveThreadCallback(LPVOID parameter)
{
	CUserUdpIocp* Owner = (CUserUdpIocp*)parameter;
	Owner->MoveThreadCallback();

	return 0;
}

CUserUdpIocp::~CUserUdpIocp(VOID)
{

}

VOID CUserUdpIocp::Reset2ThreadCallback(VOID)
{
	while (TRUE)
	{
		DWORD Result = WaitForSingleObject(mReset2ThreadDestroyEvent, 1000);

		if (Result == WAIT_OBJECT_0)
			return;

		mUdpSession.ResetUdp();
	}
}

VOID CUserUdpIocp::MoveThreadCallback(VOID)
{
	while (TRUE)
	{
		DWORD result = WaitForSingleObject(mMoveThreadHandle, 20);

		if (result == WAIT_OBJECT_0)
			return;

		MyJet* player = ServerManager::getInstance().GetPlayer();

		if (player)
		{
			mUdpSession.WriteToPacket(
				DEFAULT_ADDRESS,
				DEFAULT_PORT,
				PU_U2C_MOVE_TO,
				WriteBuffer,
				WRITE_PU_U2C_MOVE_TO(
				WriteBuffer,
				0,
				ServerManager::getInstance().Oid,
				player->GetPosition().x,
				player->GetPosition().y,
				player->GetPosition().z,
				player->GetRotation().w,
				player->GetRotation().x,
				player->GetRotation().y,
				player->GetRotation().z,
				player->info.SPEED,
				player->info.BOOSTTIME,
				//false));
				ServerManager::getInstance().isFired));

		}
		else
		{

			printf("OID : %d", ServerManager::getInstance().Oid);
			mUdpSession.WriteToPacket(
				DEFAULT_ADDRESS,
				DEFAULT_PORT,
				PU_U2C_MOVE_TO,
				WriteBuffer,
				WRITE_PU_U2C_MOVE_TO(
				WriteBuffer,
				0,
				ServerManager::getInstance().Oid,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				false));
		}

	}
}

VOID CUserUdpIocp::Initializing(VOID)
{
	ZeroMemory(WriteBuffer, sizeof(WriteBuffer));
	ZeroMemory(Packet, sizeof(Packet));
	dwPacketLength = dwProtocol = 0;
}

BOOL CUserUdpIocp::Begin(VOID)
{
	isStart = false;
	if (!CIocp::Begin())
	{
		//CLog::WriteLogNoDate(_T("CIocp::Begin\n"));
		End();
		return FALSE;
	}

	if (!mUdpSession.Begin())
	{
		//CLog::WriteLogNoDate(_T("mUdpSession.Begin\n"));
		End();
		return FALSE;
	}

	if (!mUdpSession.UdpBind(DEFAULT_PORT))
	{
		//CLog::WriteLogNoDate(_T("mUdpSession.UdpBind\n"));
		End();
		return FALSE;
	}

	if (!CIocp::RegisterSocketToIocp(mUdpSession.GetSocket(), (ULONG_PTR)&mUdpSession))
	{
		//CLog::WriteLogNoDate(_T("CIocp::ReginsterSocketToIocp\n"));
		End();
		return FALSE;
	}

	if (!mUdpSession.InitializeReadFromForIocp()) //Not From?
	{
		//CLog::WriteLogNoDate(_T("mUdpSession.InitializeReadFromForIocp\n"));
		End();
		return FALSE;
	}

	mUdpSession.WriteToPacket(
		DEFAULT_ADDRESS, 
		DEFAULT_PORT,
		PU_TUNNELING,
		WriteBuffer, 
		WRITE_PU_TUNNELING(
		WriteBuffer,
		ServerManager::getInstance().UserId,
		L"192.168.1.1",
		1820));

	mReset2ThreadDestroyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	mReset2ThreadHandle = CreateThread(NULL, 0, ::Reset2ThreadCallback, this, 0, NULL);

	return TRUE;
}

BOOL CUserUdpIocp::End(VOID)
{
	SetEvent(mReset2ThreadDestroyEvent);
	SetEvent(mMoveThreadDestroyEvent);

	WaitForSingleObject(mReset2ThreadHandle, INFINITE);
	WaitForSingleObject(mMoveThreadHandle, INFINITE);

	CloseHandle(mReset2ThreadDestroyEvent);
	CloseHandle(mReset2ThreadHandle);

	CloseHandle(mMoveThreadDestroyEvent);
	CloseHandle(mMoveThreadHandle);

	CIocp::End();

	mUdpSession.End();

	return TRUE;

}

BOOL CUserUdpIocp::WriteToPacketForRoot(DWORD protocol, BYTE* packet, DWORD dwLength)
{
	return mUdpSession.WriteToPacket("168.126.12.131", RemotePort, protocol, packet, dwLength);
}

VOID CUserUdpIocp::OnIoConnected(VOID *object){}
VOID CUserUdpIocp::OnIoDisconnected(VOID* object){}

VOID CUserUdpIocp::OnIoRead(VOID *object, DWORD dataLength)
{
	CPacketSession* PacketSession = (CPacketSession*)object;

	DWORD	Protocol = 0;
	BYTE	Packet[MAX_BUFFER_LENGTH] = { 0, };
	DWORD	PacketLength = 0;
	CHAR	RemoteAddress[32] = { 0, };
	USHORT	RemotePort = 0;
	TCHAR	RemoteAddressTCHAR[32] = { 0, };
	BYTE	WriteBuffer[MAX_BUFFER_LENGTH] = { 0, };

	if (PacketSession->ReadFromPacketForIocp(RemoteAddress, RemotePort, dataLength))
	{
		while (PacketSession->GetPacket(RemoteAddress, RemotePort, Protocol, Packet, PacketLength))
		{
			mUdpSession.WriteToPacket(RemoteAddress, RemotePort, 0, 0, 0);


			MultiByteToWideChar(CP_ACP,
				0,
				RemoteAddress,
				-1,
				RemoteAddressTCHAR,
				32);

			switch (Protocol)
			{
			case PU_TUNNELING_SUCC_U:
				if (isStart == false)
					StartGame();
				break;

			case PU_C2U_MOVE_TO:
				//CLog::WriteLog(L" Success!");
				S_PU_C2U_MOVE_TO data;
				READ_PU_C2U_MOVE_TO(Packet, data);
				DATAMANAGER.SetPacket(data);
				break;
			}
		}
	}


	if (!PacketSession->InitializeReadFromForIocp())
	{

		End();

		return;
	}
}

VOID CUserUdpIocp::OnIoWrote(VOID* object, DWORD dataLength)
{
	CPacketSession* PacketSession = (CPacketSession*)object;
	PacketSession->WriteComplete();

}

void CUserUdpIocp::StartGame()
{
	printf("Tunneling succ");
	ServerManager::getInstance().GameIntroComplete();
	isStart = true;
}

VOID CUserUdpIocp::StartMoveThread(VOID)
{
	mMoveThreadDestroyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	mMoveThreadHandle = CreateThread(NULL, 0, ::MoveThreadCallback, this, 0, NULL);
	printf("Thread Open!!");
}