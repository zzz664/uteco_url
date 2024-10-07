#include "DXUT.h"
#include "ConnectedUser.h"

CConnectedUser::CConnectedUser(VOID)
{
	ZeroMemory(mUserID, sizeof(mUserID));
	ZeroMemory(mVirtualAddress, sizeof(mVirtualAddress));
	ZeroMemory(mRealAddress, sizeof(mRealAddress));
	ZeroMemory(mNickName, sizeof(mNickName));

	mVirtualPort = 0;
	mRealPort = 0;

	mStatus = US_NONE;

	mEnteredRoom = NULL;

	mIsConnected = FALSE;
	mIsReady = FALSE;

	mIsLoadComplete = FALSE;
	mIsIntroComplete = FALSE;

	x = y = z = 0;

}

CConnectedUser::~CConnectedUser(VOID)
{

}

BOOL CConnectedUser::Begin(VOID)
{
	CThreadSync Sync;

	ZeroMemory(mUserID, sizeof(mUserID));
	ZeroMemory(mVirtualAddress, sizeof(mVirtualAddress));
	ZeroMemory(mRealAddress, sizeof(mRealAddress));
	ZeroMemory(mNickName, sizeof(mNickName));

	mVirtualPort = 0;
	mRealPort = 0;

	mStatus = US_NONE;

	mEnteredRoom = NULL;

	mIsConnected = FALSE;
	mIsReady = FALSE;

	mIsLoadComplete = FALSE;
	mIsIntroComplete = FALSE;

	return CPacketSession::Begin();
}

BOOL CConnectedUser::End(VOID)
{
	CThreadSync Sync;

	ZeroMemory(mUserID, sizeof(mUserID));
	ZeroMemory(mVirtualAddress, sizeof(mVirtualAddress));
	ZeroMemory(mRealAddress, sizeof(mRealAddress));
	ZeroMemory(mNickName, sizeof(mNickName));

	mVirtualPort = 0;
	mRealPort = 0;

	mStatus = US_NONE;

	mEnteredRoom = NULL;

	mIsConnected = FALSE;
	mIsReady = FALSE;

	mIsLoadComplete = FALSE;
	mIsIntroComplete = FALSE;

	return CPacketSession::End();
}

BOOL CConnectedUser::Reload(SOCKET listenSocket)
{
	CThreadSync Sync;

	End();

	if (!Begin())
		return FALSE;

	if (!CNetworkSession::Accept(listenSocket))
		return FALSE;

	return TRUE;
}