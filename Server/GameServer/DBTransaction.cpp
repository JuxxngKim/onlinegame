#include "pch.h"
#include "DBTransaction.h"

#include <codecvt>

#include "DBConnection.h"
#include "DBConnectionPool.h"
#include "ClientPacketHandler.h"
#include "GameSession.h"

DBTransactionRef GDBTransaction = nullptr;

void DBTransaction::CreateAccount(PacketSessionRef session, string id, string password)
{
    auto idHash = (int)std::hash<string>{}(id);
    const auto pwHash = (int)std::hash<string>{}(password);

    // DB 데이터 검사
    {
        DBConnection* dbConn = GDBConnectionPool->Pop();
        dbConn->Unbind();

        SQLLEN len = 0;
        ASSERT_CRASH(dbConn->BindParam(1, &idHash, &len));

        int32 outId = 0;
        SQLLEN outIdLen = 0;
        ASSERT_CRASH(dbConn->BindCol(1, SQL_C_LONG, sizeof(outId), &outId, &outIdLen));

        // SQL
        ASSERT_CRASH(dbConn->Execute(L"SELECT id FROM [dbo].[Account] WHERE id = (?)"));

        bool containsAccountOrError = false;
        const SQLRETURN ret = dbConn->GetFechResult();
        switch (ret)
        {
        case SQL_NO_DATA:
            containsAccountOrError = false;
            break;
        default:
            containsAccountOrError = true;
            break;
        }

        GDBConnectionPool->Push(dbConn);

        if (containsAccountOrError)
        {
            Protocol::S_CreateAccount createAccountPacket;
            createAccountPacket.set_success(false);
            const auto sendPacket = ClientPacketHandler::MakeSendBuffer(createAccountPacket);
            session->Send(sendPacket);
            return;
        }
    }

    // 계정 생성
    {
        DBConnection* dbConn = GDBConnectionPool->Pop();
        dbConn->Unbind();

        int32 accountId = idHash;
        SQLLEN len = 0;

        int32 password = pwHash;
        SQLLEN pwLen = 0;

        ASSERT_CRASH(dbConn->BindParam(1, &accountId, &len));
        ASSERT_CRASH(dbConn->BindParam(2, &password, &pwLen));

        // SQL
        ASSERT_CRASH(dbConn->Execute(L"INSERT INTO [dbo].[Account]([id], [password]) VALUES(?, ?)"));

        GDBConnectionPool->Push(dbConn);
    }

    // 플레이어 정보 생성
    {
        DBConnection* dbConn = GDBConnectionPool->Pop();
        dbConn->Unbind();

        int32 accountId = idHash;
        SQLLEN len = 0;

        const wstring strName(id.begin(), id.end());
        const wchar_t* name = strName.c_str();
        SQLLEN nameLen = 0;

        int32 level = 1;
        SQLLEN levelLen = 0;

        int32 gold = 1;
        SQLLEN goldLen = 0;

        ASSERT_CRASH(dbConn->BindParam(1, &accountId, &len));
        ASSERT_CRASH(dbConn->BindParam(2, name, &nameLen));
        ASSERT_CRASH(dbConn->BindParam(3, &level, &levelLen));
        ASSERT_CRASH(dbConn->BindParam(4, &gold, &goldLen));

        // SQL
        ASSERT_CRASH(dbConn->Execute(L"INSERT INTO [dbo].[Player]([id], [name], [lv], [gold]) VALUES(?, ?, ?, ?)"));

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

    auto idHash = (int)std::hash<string>{}(pkt.id());
    const auto pwHash = (int)std::hash<string>{}(pkt.password());

	// 계정이 있는지 검사
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		dbConn->Unbind();

		SQLLEN len = 0;
		ASSERT_CRASH(dbConn->BindParam(1, &idHash, &len));

		int32 outId = 0;
		SQLLEN outIdLen = 0;
		ASSERT_CRASH(dbConn->BindCol(1, SQL_C_LONG, sizeof(outId), &outId, &outIdLen));

		int32 outPw = 0;
		SQLLEN outPwLen = 0;
		ASSERT_CRASH(dbConn->BindCol(2, SQL_C_LONG, sizeof(outPw), &outPw, &outPwLen));

		// SQL
		ASSERT_CRASH(dbConn->Execute(L"SELECT id, password FROM [dbo].[Account] WHERE id = (?)"));

		bool result = dbConn->Fetch();
		GDBConnectionPool->Push(dbConn);

		// DB 데이터 여부와 패스워드 비교
		result &= outPw == pwHash;
		if (!result)
		{
			loginPacket.set_loginok(false);
			const auto sendPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
			session->Send(sendPacket);
			return;
		}
	}

	// 플레이어 정보
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		dbConn->Unbind();

		SQLLEN len = 0;
		ASSERT_CRASH(dbConn->BindParam(1, SQL_C_LONG, SQL_INTEGER, sizeof(idHash), &idHash, &len));

		WCHAR outName[100];
		SQLLEN outNameLen = 0;
		ASSERT_CRASH(dbConn->BindCol(1, SQL_C_LONG, sizeof(outName), outName, &outNameLen));

		int32 outLv = 0;
		SQLLEN outLvLen = 0;
		ASSERT_CRASH(dbConn->BindCol(2, SQL_C_LONG, sizeof(outLv), &outLv, &outLvLen));

		int32 outGold = 0;
		SQLLEN outGoldLen = 0;
		ASSERT_CRASH(dbConn->BindCol(3, SQL_C_LONG, sizeof(outGold), &outGold, &outGoldLen));

		// SQL
		ASSERT_CRASH(dbConn->Execute(L"SELECT name, lv gold FROM [dbo].[Player] WHERE id = (?)"));
		bool result = dbConn->Fetch();
		GDBConnectionPool->Push(dbConn);
		if (!result)
		{
			loginPacket.set_loginok(false);
			const auto sendPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
			session->Send(sendPacket);
			return;
		}

		GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
		gameSession->HandleLogin(pkt.id(), outLv, outGold);
		
		// 로그인 성공
		loginPacket.set_loginok(true);
		const auto enterLoginPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
		session->Send(enterLoginPacket);
	}

}
