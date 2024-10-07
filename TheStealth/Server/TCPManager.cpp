#include "DXUT.h"
#include "TCPManager.h"

TCPManager::TCPManager()
{
}
TCPManager::~TCPManager()
{
	for (auto db : readerPool_) {
		SAFE_DELETE(db);
	}
}

void TCPManager::initialize(CUserSession* session)
{
	workerCount_ = 5;
	for (int i = 0; i < workerCount_; ++i) {
		TCPReader *reader = new TCPReader(session);
		readerPool_.push_back(reader);
	}
}

void TCPManager::run()
{
	for (auto reader : readerPool_) {
		reader->run();
	}
}