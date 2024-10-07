#include "DXUT.h"
#include "HostUdpIocp.h"
#include "ServerManager.h"

DWORD WINAPI ResetThreadCallback(LPVOID parameter)
{
	CHostUdpIocp* Owner = (CHostUdpIocp*)parameter;
	Owner->ResetThreadCallback();

	return 0;
}

DWORD WINAPI Move2ThreadCallback(LPVOID parameter)
{
	CHostUdpIocp* Owner = (CHostUdpIocp*)parameter;
	Owner->Move2ThreadCallback();
	
	return 0;
}

CHostUdpIocp::CHostUdpIocp(DWORD port)
{
	this->port = port;
	ZeroMemory(users, sizeof(users));
	ZeroMemory(realUsers, sizeof(realUsers));
}

CHostUdpIocp::~CHostUdpIocp(VOID)
{

}

VOID CHostUdpIocp::ResetThreadCallback(VOID)
{
	while (TRUE)
	{
		DWORD Result = WaitForSingleObject(mResetThreadDestroyEvent, 1000);

		if (Result == WAIT_OBJECT_0)
			return;

		mUdpSession.ResetUdp();
		/* 사용자 움직임 */
	}
}

VOID CHostUdpIocp::Move2ThreadCallback(VOID)
{
	while (TRUE)
	{
		DWORD Result = WaitForSingleObject(mMove2ThreadDestroyEvent, 20);

		if (Result == WAIT_OBJECT_0)
			return;
	}
}


VOID CHostUdpIocp::Initializing(VOID)
{
	ZeroMemory(WriteBuffer, sizeof(WriteBuffer));
	ZeroMemory(Packet, sizeof(Packet));
	dwPacketLength = dwProtocol = 0;
}

BOOL CHostUdpIocp::Begin(VOID)
{
	if (!CIocp::Begin())
	{
		//CLog::WriteLogNoDate(_T("CIocp::Begin"));
		End();
		return FALSE;
	}

	if (!mUdpSession.Begin())
	{
		//CLog::WriteLogNoDate(_T("mUdpSession.Begin"));
		End();
		return FALSE;
	}

	if (!mUdpSession.UdpBind(port))
	{
		//CLog::WriteLogNoDate(_T("mUdpSession.UdpBind"));
		End();
		return FALSE;
	}

	if (!CIocp::RegisterSocketToIocp(mUdpSession.GetSocket(), (ULONG_PTR)&mUdpSession))
	{
		//CLog::WriteLogNoDate(_T("CIocp::ReginsterSocketToIocp"));
		End();
		return FALSE;
	}

	if (!mUdpSession.InitializeReadFromForIocp())
	{
		//CLog::WriteLogNoDate(_T("mUdpSession.InitializeReadFromForIocp"));
		End();
		return FALSE;
	}

	mResetThreadDestroyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	mResetThreadHandle = CreateThread(NULL, 0, ::ResetThreadCallback, this, 0, NULL);

	mMove2ThreadDestroyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	mMove2ThreadHandle = CreateThread(NULL, 0, ::Move2ThreadCallback, this, 0, NULL);

	return TRUE;
}

BOOL CHostUdpIocp::End(VOID)
{
	SetEvent(mResetThreadDestroyEvent);
	SetEvent(mMove2ThreadDestroyEvent);

	WaitForSingleObject(mResetThreadHandle, INFINITE);
	WaitForSingleObject(mMove2ThreadHandle, INFINITE);

	CloseHandle(mMove2ThreadHandle);
	CloseHandle(mMove2ThreadDestroyEvent);
	CloseHandle(mResetThreadDestroyEvent);
	CloseHandle(mResetThreadHandle);

	CIocp::End();

	mUdpSession.End();

	return TRUE;

}

VOID CHostUdpIocp::OnIoConnected(VOID *object){}
VOID CHostUdpIocp::OnIoDisconnected(VOID* object){}

VOID CHostUdpIocp::OnIoRead(VOID *object, DWORD dataLength)
{
	CPacketSession* PacketSession = (CPacketSession*)object;
	//CLog::WriteLog(L"CHOSTUDPIOCP : OnIoRead!!!!!!!!!\n");

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
			MultiByteToWideChar(CP_ACP,
				0,
				RemoteAddress,
				-1,
				RemoteAddressTCHAR,
				32);

			switch (Protocol)
			{
			case PU_C2U_MOVE_TO:
				//CLog::WriteLog(L"C2U Move To \n\n");
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

VOID CHostUdpIocp::OnIoWrote(VOID* object, DWORD dataLength)
{
	CPacketSession* PacketSession = (CPacketSession*)object;
	PacketSession->WriteComplete();

}

VOID CHostUdpIocp::WriteToPacketAll(DWORD protocol, BYTE* packet, DWORD dwPacketLength)
{
	for (int i = 0; i < userCount; i++)
	{
		this->mUdpSession.WriteToPacket(
			(LPCSTR)realUsers[i].RealAddress,
			realUsers[i].RealPort,
			protocol,
			packet,
			dwPacketLength);
	}
}


VOID CHostUdpIocp::SetUser(DWORD userCount, SLOT_USER_DATA data[8])
{
	this->userCount = userCount;
	for (int i = 0; i < 8; i++) {
		memcpy(users, data, sizeof(data));
		if (data[i].RealAddress != NULL)
			realUsers[i] = data[i];
	}
}