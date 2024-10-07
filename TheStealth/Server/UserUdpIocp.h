#pragma once
#include "DXUT.h"

class CUserUdpIocp : public CIocp
{
public:
	CUserUdpIocp(DWORD port){ this->port = port; }
	~CUserUdpIocp();

private:
	HANDLE				mReset2ThreadHandle;
	HANDLE				mReset2ThreadDestroyEvent;
	DWORD_PTR			mSessionId;
	DWORD				port;

	HANDLE				mMoveThreadHandle;
	HANDLE				mMoveThreadDestroyEvent;

	BYTE				WriteBuffer[MAX_BUFFER_LENGTH];
	BYTE				Packet[MAX_BUFFER_LENGTH];
	DWORD				dwProtocol;
	DWORD				dwPacketLength;

	bool				isStart;
public:
	BOOL				Begin(VOID);
	BOOL				End(VOID);

	
	LPCSTR				RemoteAddress;
	DWORD				RemotePort;
	VOID				Initializing(VOID);
	VOID				Reset2ThreadCallback(VOID);
	VOID				MoveThreadCallback(VOID);
	VOID				StartMoveThread(VOID);
	VOID				SetRemoteInfo(LPCSTR RemoteAddress, DWORD RemotePort){ this->RemoteAddress = RemoteAddress; this->RemotePort = RemotePort; }
	BOOL				WriteToPacketForRoot(DWORD protocol, BYTE* packet, DWORD dwLength);
	CPacketSession		mUdpSession;
	VOID				SetSessionId(DWORD_PTR session){ this->mSessionId = session; }
	DWORD_PTR			GetSessionId(){ return mSessionId; }
	void				StartGame();
protected:
	VOID				OnIoRead(VOID* object, DWORD dataLength);
	VOID				OnIoWrote(VOID* object, DWORD dataLength);
	VOID				OnIoConnected(VOID* object);
	VOID				OnIoDisconnected(VOID* object);
};