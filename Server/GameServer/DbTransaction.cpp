#include "pch.h"
#include "DBTransaction.h"
#include "DBConnection.h"
#include "DBConnectionPool.h"
#include "ClientPacketHandler.h"
#include "GameSession.h"

DBTransaction GDBTransaction;

void DBTransaction::CreateAccount(PacketSessionRef session, Protocol::C_CreateAccount pkt)
{
    auto idHash = std::hash<string>{}(pkt.id());
    const auto pwHash = std::hash<string>{}(pkt.password());

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
        ASSERT_CRASH(dbConn->Execute(L"SELECT id FROM [dbo].[Account] WHERE Id = (?)"));

        bool containsAccountOrError = false;
        const SQLRETURN ret = dbConn->GetFechResult();
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
        if (containsAccountOrError)
        {
            Protocol::S_CreateAccount createAccountPacket;
            createAccountPacket.set_success(false);
            const auto sendPacket = ClientPacketHandler::MakeSendBuffer(createAccountPacket);
            session->Send(sendPacket);
            return;
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
        ASSERT_CRASH(dbConn->BindParam(2, &password, &pwLen));

        // SQL 실행
        ASSERT_CRASH(dbConn->Execute(L"INSERT INTO [dbo].[Account]([Id], [Password]) VALUES(?, ?)"));

        GDBConnectionPool->Push(dbConn);
    }

    // 플레이어 정보 저장
    {
        DBConnection* dbConn = GDBConnectionPool->Pop();
        dbConn->Unbind();

        int32 accountId = idHash;
        SQLLEN len = 0;

        const wstring strName = to_wstring(accountId);
        const wchar_t* name = strName.c_str();
        SQLLEN nameLen = 0;

        int32 level = 1;
        SQLLEN levelLen = 0;

        int32 gold = 1;
        SQLLEN goldLen = 0;

        // 넘길 인자 바인딩
        ASSERT_CRASH(dbConn->BindParam(1, &accountId, &len));
        ASSERT_CRASH(dbConn->BindParam(2, name, &nameLen));
        ASSERT_CRASH(dbConn->BindParam(3, &level, &levelLen));
        ASSERT_CRASH(dbConn->BindParam(4, &gold, &goldLen));

        // SQL 실행
        ASSERT_CRASH(dbConn->Execute(L"INSERT INTO [dbo].[Player]([Id], [Name], [Level], [Gold]) VALUES(?, ?, ?, ?)"));

        GDBConnectionPool->Push(dbConn);
    }

    Protocol::S_CreateAccount createAccountPacket;
    createAccountPacket.set_success(true);
    const auto sendPacket = ClientPacketHandler::MakeSendBuffer(createAccountPacket);
    session->Send(sendPacket);
}

void DBTransaction::Login(PacketSessionRef session, Protocol::C_Login pkt)
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
		ASSERT_CRASH(dbConn->Execute(L"SELECT id, password FROM [dbo].[Account] WHERE Id = (?)"));

		bool result = dbConn->Fetch();
		GDBConnectionPool->Push(dbConn);

		// 패스워드 검사.
		result &= outPw == pwHash;
		if (!result)
		{
			loginPacket.set_loginok(false);
			const auto sendPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
			session->Send(sendPacket);
			return;
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

		int32 outGold = 0;
		SQLLEN outGoldLen = 0;
		ASSERT_CRASH(dbConn->BindCol(3, SQL_C_LONG, sizeof(outGold), &outGold, &outGoldLen));

		// SQL 실행
		ASSERT_CRASH(dbConn->Execute(L"SELECT name, level gold FROM [dbo].[Player] WHERE Id = (?)"));
		bool result = dbConn->Fetch();
		if (!result)
		{
			loginPacket.set_loginok(false);
			const auto sendPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
			session->Send(sendPacket);
			return;
		}

		// 로그인 성공
		loginPacket.set_loginok(true);
		const auto enterLoginPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
		session->Send(enterLoginPacket);

		// 접속
		wstring wName(outName);
		string name(wName.begin(), wName.end());
		GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
		gameSession->HandleEnterGame(name, outLv, outGold);
	}

}
