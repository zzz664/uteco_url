#pragma once
#include "DXUT.h"
#include "Singleton.h"
#include "TCPReader.h"

class TCPManager : public Singleton <TCPManager>
{
	int                                 workerCount_;
	std::vector<TCPReader *>             readerPool_;

public:
	TCPManager();
	virtual ~TCPManager();

	void initialize(CUserSession* session);

	void run();
};