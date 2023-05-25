#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"
#include "GameLogic.h"
#include "DBConnectionPool.h"
#include "DBTransaction.h"

enum
{
	WORKER_TICK = 64
};

void DoWorkerJob(ServerServiceRef& service)
{
	while (true)
	{
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;

		// 네트워크 입출력 처리 -> 인게임 로직까지 (패킷 핸들러에 의해)
		service->GetIocpCore()->Dispatch(10);

		// 예약된 일감 처리
		ThreadManager::DistributeReservedJobs();

		// 글로벌 큐
		ThreadManager::DoGlobalQueueWork();
	}
}

void DoDBWorkerJob()
{
	 ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=ServerDb;Trusted_Connection=Yes;"));

	 //// Create Table
	 //{
	 //	auto query = L"									\
	 //		DROP TABLE IF EXISTS [dbo].[Gold];			\
	 //		CREATE TABLE [dbo].[Gold]					\
	 //		(											\
	 //			[id] INT NOT NULL PRIMARY KEY IDENTITY, \
	 //			[gold] INT NULL							\
	 //		);";

	 //	DBConnection* dbConn = GDBConnectionPool->Pop();
	 //	ASSERT_CRASH(dbConn->Execute(query));
	 //	GDBConnectionPool->Push(dbConn);
	 //}

	 while (true)
	 {
		 GDBTransaction.Execute();
	 }
}

int main()
{
	ClientPacketHandler::Init();

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, // TODO : SessionManager 등
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([&service]()
		{
			DoWorkerJob(service);
		});
	}

	// DB Thread
	GThreadManager->Launch([]()
	{
		DoDBWorkerJob();
	});
	
	GGameLogic.AddRoom(1);
	
	// GameLogic Thread
	while (true)
	{
		GGameLogic.Update();
	}

	// Join
	GThreadManager->Join();
}