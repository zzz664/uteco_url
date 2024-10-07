#pragma once
#include "DXUT.h"

typedef struct _CHARACTER_
{
	WCHAR* UserID;
	int x;
	int y;
	int z;
};

class CHostUdpIocp : public CIocp
{
public:
	CHostUdpIocp(DWORD port);
	~CHostUdpIocp();

private:
	HANDLE				mResetThreadHandle;
	HANDLE				mResetThreadDestroyEvent;
	HANDLE				mMove2ThreadHandle;
	HANDLE				mMove2ThreadDestroyEvent;

	SLOT_USER_DATA		users[8];
	SLOT_USER_DATA		realUsers[8];
	DWORD				userCount;
	DWORD				port;
	DWORD_PTR			mSessionId;
	DWORD				roomId;

	BYTE				WriteBuffer[MAX_BUFFER_LENGTH];
	BYTE				Packet[MAX_BUFFER_LENGTH];
	DWORD				dwProtocol;
	DWORD				dwPacketLength;

public:
	BOOL				Begin(VOID);
	BOOL				End(VOID);

	VOID				ResetThreadCallback(VOID);
	VOID				Move2ThreadCallback(VOID);
	VOID				Initializing(VOID);
	VOID				SetUser(DWORD userCount,SLOT_USER_DATA data[8]);
	VOID				WriteToPacketAll(DWORD protocol, BYTE* packet, DWORD dwPacketLength);
	CPacketSession		mUdpSession;
	VOID				SetSessionId(DWORD_PTR session){ this->mSessionId = session; }
	DWORD_PTR			GetSessionId(){ return mSessionId; }


protected:
	VOID				OnIoRead(VOID* object, DWORD dataLength);
	VOID				OnIoWrote(VOID* object, DWORD dataLength);
	VOID				OnIoConnected(VOID* object);
	VOID				OnIoDisconnected(VOID* object);


};