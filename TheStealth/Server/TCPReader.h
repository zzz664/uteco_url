#pragma once
#include "DXUT.h"
#include "UserSession.h"
#include "Thread.h"

class TCPReader : public CMultiThreadSync<TCPReader>
{
public:
	TCPReader(CUserSession* session);
	~TCPReader();

	void run();
private:
	BYTE Packet[MAX_BUFFER_LENGTH];
	DWORD dwProtocol, dwPacketLength;
	CUserSession*				mSession;
	Thread						*thread_;
	void process();
	void excute();
};