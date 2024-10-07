#pragma once

#include <DXUT.h>
class CRoom;
// CPacketSession을 상속받은 CConnectedUser
class CConnectedUser : public CPacketSession
{
public:
	CConnectedUser(VOID);
	virtual ~CConnectedUser(VOID);

private:
	TCHAR				mUserID[32];

	TCHAR				mVirtualAddress[32];
	TCHAR				mRealAddress[32];

	USHORT				mVirtualPort;
	USHORT				mRealPort;

	USER_STATUS			mStatus;

	CRoom				*mEnteredRoom;

	BOOL				mIsConnected;

	TCHAR				mNickName[32];

	BOOL				mIsReady;
	BOOL				mIsLoadComplete;
	BOOL				mIsIntroComplete;

	// ---------------In Game Member-------------------
	
	float x;
	float y;
	float z;
	
	//----------------------------------------------------

public:
	BOOL				Begin(VOID);
	BOOL				End(VOID);

	BOOL				Reload(SOCKET listenSocket);

	inline BOOL			SetIsConnected(BOOL isConnected){ CThreadSync Sync; mIsConnected = isConnected; return TRUE; }
	inline BOOL			GetIsConnected(VOID){ CThreadSync Sync; return mIsConnected; }
	inline BOOL			SetPosition(float x, float y, float z = 0){ this->x = x; this->y = y; this->z = z; }
	inline BOOL			SetIsReady(BOOL isReady){ CThreadSync Sync; mIsReady = isReady; return TRUE; }
	inline BOOL			GetIsReady(VOID){ CThreadSync Sync; return mIsReady; }
	inline BOOL			SetIsLoadComplete(BOOL isLoadComplete){ CThreadSync Sync; mIsLoadComplete = isLoadComplete; return TRUE; }
	inline BOOL			GetIsLoadComplete(VOID){ CThreadSync Sync; return mIsLoadComplete; }
	inline BOOL			SetIsIntroComplete(BOOL isIntroComplete){ CThreadSync Sync; mIsIntroComplete = isIntroComplete; return TRUE; }
	inline BOOL			GetIsIntroComplete(VOID){ CThreadSync Sync; return mIsIntroComplete; }

	inline BOOL			SetVirtualInformation(LPTSTR virtualAddress, USHORT virtualPort){ CThreadSync Sync; if (!virtualAddress || virtualPort <= 0)return FALSE; _tcsncpy(mVirtualAddress, virtualAddress, 32); mVirtualPort = virtualPort; return TRUE; }
	inline BOOL			SetRealInformation(LPTSTR realAddress, USHORT realPort){ CThreadSync Sync; if (!realAddress || realPort <= 0)return FALSE; _tcsncpy(mRealAddress, realAddress, 32); mRealPort = realPort; return TRUE; }
	inline BOOL			SetUserID(LPTSTR userID){ CThreadSync Sync; if (!userID)return FALSE; _tcsncpy(mUserID, userID, 32); return TRUE; }
	inline BOOL			SetStatus(USER_STATUS status){ CThreadSync Sync; mStatus = status; return TRUE; }
	inline USER_STATUS	GetStatus(VOID){ CThreadSync Sync; return mStatus; }
	inline BOOL			SetEnteredRoom(CRoom *room){ CThreadSync Sync; mEnteredRoom = room; return TRUE; }
	inline CRoom*		GetEnteredRoom(VOID){ CThreadSync Sync; return mEnteredRoom; }
	inline LPTSTR		GetUserID(VOID){ CThreadSync Sync; return mUserID; }
	inline LPTSTR		GetRealAddress(VOID){ CThreadSync Sync; return mRealAddress; }
	inline LPTSTR		GetVirtualAddress(VOID){ CThreadSync Sync; return mVirtualAddress; }
	inline USHORT		GetRealPort(VOID){ CThreadSync Sync; return mRealPort; }
	inline USHORT		GetVirtualPort(VOID){ CThreadSync Sync; return mVirtualPort; }

};
