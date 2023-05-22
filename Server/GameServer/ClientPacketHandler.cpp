#include "pch.h"
#include "ClientPacketHandler.h"

#include "DBConnectionPool.h"
#include "Player.h"
#include "Room.h"
#include "GameSession.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];


bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_C_Move(PacketSessionRef& session, Protocol::C_Move& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	PlayerRef playerRef = gameSession->_currentPlayer;
	RoomRef roomRef = playerRef->GetRoom().lock();

	roomRef->DoAsync(&Room::Handle_Move, playerRef, pkt);
	return true;
}

bool Handle_C_Skill(PacketSessionRef& session, Protocol::C_Skill& pkt)
{
	return true;
}

bool Handle_C_Login(PacketSessionRef& session, Protocol::C_Login& pkt)
{
	Protocol::S_Login loginPacket;

	auto idHash = std::hash<string>{}(pkt.id());
	auto pwHash = std::hash<string>{}(pkt.password());

	// 계정 검사
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		dbConn->Unbind();

		SQLLEN len = 0;
		ASSERT_CRASH(dbConn->BindParam(0, SQL_C_LONG, SQL_INTEGER, idHash, &idHash, &len));

		int32 outId = 0;
		SQLLEN outIdLen = 0;
		ASSERT_CRASH(dbConn->BindCol(0, SQL_C_LONG, sizeof(outId), &outId, &outIdLen));

		int32 outPw = 0;
		SQLLEN outPwLen = 0;
		ASSERT_CRASH(dbConn->BindCol(1, SQL_C_LONG, sizeof(outPw), &outPw, &outPwLen));
		
		// SQL 실행
		ASSERT_CRASH(dbConn->Execute(L"SELECT id, password gold FROM [dbo].[Account] WHERE Id = (?)"));

		bool result = dbConn->Fetch();
		GDBConnectionPool->Push(dbConn);
		
		// 패스워드 검사.
		result &= outPw == pwHash; 
		if(!result)
		{
			loginPacket.set_loginok(false);
			const auto sendPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
			session->Send(sendPacket);
			return true;
		}
	}

	// 플레이어 정보 Read
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		dbConn->Unbind();

		SQLLEN len = 0;
		ASSERT_CRASH(dbConn->BindParam(1, SQL_C_LONG, SQL_INTEGER, idHash, &idHash, &len));

		WCHAR outName[100];
		SQLLEN outNameLen = 0;
		ASSERT_CRASH(dbConn->BindCol(1, SQL_C_LONG, sizeof(outName), outName, &outNameLen));

		int32 outLv = 0;
		SQLLEN outLvLen = 0;
		ASSERT_CRASH(dbConn->BindCol(2, SQL_C_LONG, sizeof(outLv), &outLv, &outLvLen));
		
		// SQL 실행
		ASSERT_CRASH(dbConn->Execute(L"SELECT name, level gold FROM [dbo].[Player] WHERE Id = (?)"));
		bool result = dbConn->Fetch();
		if(!result)
		{
			loginPacket.set_loginok(false);
			const auto sendPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
			session->Send(sendPacket);
			return true;
		}

		// 로그인 성공
		loginPacket.set_loginok(true);
		const auto enterLoginPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
		session->Send(enterLoginPacket);

		// 접속
		wstring wName(outName);
		string name(wName.begin(), wName.end());
		GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
		gameSession->HandleEnterGame(name, outLv);
	}

	return true;
}


bool Handle_C_EnterGame(PacketSessionRef& session, Protocol::C_EnterGame& pkt)
{
	// GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	// gameSession->HandleEnterGame(pkt);
	return true;
}

bool Handle_C_Chat(PacketSessionRef& session, Protocol::C_Chat& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	const RoomRef roomRef = gameSession->_room.lock();

	Protocol::S_Chat chatPacket;
	chatPacket.set_objectid(gameSession->_currentPlayer->GetID());
	chatPacket.set_message(pkt.message());
	
	const auto sendPacket = ClientPacketHandler::MakeSendBuffer(chatPacket);
	
	roomRef->DoAsync(&Room::Broadcast, sendPacket);
	return true;
}

bool Handle_C_CreateAccount(PacketSessionRef& session, Protocol::C_CreateAccount& pkt)
{
	auto idHash = std::hash<string>{}(pkt.id());
	auto pwHash = std::hash<string>{}(pkt.password());
	
	// 계정 검사
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		dbConn->Unbind();

		SQLLEN len = 0;
		ASSERT_CRASH(dbConn->BindParam(1, SQL_C_LONG, SQL_INTEGER, idHash, &idHash, &len));

		int32 outId = 0;
		SQLLEN outIdLen = 0;
		ASSERT_CRASH(dbConn->BindCol(1, SQL_C_LONG, sizeof(outId), &outId, &outIdLen));

		// SQL 실행
		ASSERT_CRASH(dbConn->Execute(L"SELECT id, gold FROM [dbo].[Account] WHERE Id = (?)"));

		bool containsAccountOrError = false;
		SQLRETURN ret = dbConn->GetFechResult();
		switch (ret)
		{
		case SQL_NO_DATA:
			containsAccountOrError = false;
		default:
			containsAccountOrError = true;
			break;
		}

		GDBConnectionPool->Push(dbConn);
		
		// 이미 데이터가 존재하거나 에러 발생
		if(containsAccountOrError)
		{
			Protocol::S_CreateAccount createAccountPacket;
			createAccountPacket.set_success(false);
			const auto sendPacket = ClientPacketHandler::MakeSendBuffer(createAccountPacket);
			session->Send(sendPacket);
			return true;
		}
	}

	// 계정 정보 저장
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		dbConn->Unbind();

		int32 accountId = idHash;
		SQLLEN len = 0;
		
		int32 password = pwHash;
		SQLLEN pwLen = 0;
		
		// 넘길 인자 바인딩
		ASSERT_CRASH(dbConn->BindParam(1, &accountId, &len));
		ASSERT_CRASH(dbConn->BindParam(1, &password, &pwLen));

		// SQL 실행
		ASSERT_CRASH(dbConn->Execute(L"INSERT INTO [dbo].[Account]([Id], [password]) VALUES(?, ?)"));

		GDBConnectionPool->Push(dbConn);
	}
	
	// 플레이어 정보 저장
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		dbConn->Unbind();

		int32 accountId = idHash;
		SQLLEN len = 0;

		wstring strName = to_wstring(accountId);
		const wchar_t* name = strName.c_str();
		SQLLEN nameLen = 0;

		int32 level = 1;
		SQLLEN levelLen = 0;
		
		// 넘길 인자 바인딩
		ASSERT_CRASH(dbConn->BindParam(1, &accountId, &len));
		ASSERT_CRASH(dbConn->BindParam(2, name, &nameLen));
		ASSERT_CRASH(dbConn->BindParam(3, &level, &levelLen));

		// SQL 실행
		ASSERT_CRASH(dbConn->Execute(L"INSERT INTO [dbo].[Player]([Id], [name], [level]) VALUES(?, ?, ?)"));

		GDBConnectionPool->Push(dbConn);
	}

	Protocol::S_CreateAccount createAccountPacket;
	createAccountPacket.set_success(true);
	const auto sendPacket = ClientPacketHandler::MakeSendBuffer(createAccountPacket);
	session->Send(sendPacket);
	return true;
}

bool Handle_C_Pong(PacketSessionRef& session, Protocol::C_Pong& pkt)
{
	return true;
}
