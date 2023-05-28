#include "pch.h"
#include "DBTransaction.h"
#include "DBConnection.h"
#include "DBConnectionPool.h"
#include "ClientPacketHandler.h"
#include "GameSession.h"

DBTransactionRef GDBTransaction = nullptr;

void DBTransaction::CreateAccount(PacketSessionRef session, string id, string password)
{
    auto idHash = (int)std::hash<string>{}(id);
    const auto pwHash = (int)std::hash<string>{}(password);

    // ���� �˻�
    {
        DBConnection* dbConn = GDBConnectionPool->Pop();
        dbConn->Unbind();

        SQLLEN len = 0;
        ASSERT_CRASH(dbConn->BindParam(1, &idHash, &len));

        int32 outId = 0;
        SQLLEN outIdLen = 0;
        ASSERT_CRASH(dbConn->BindCol(1, SQL_C_LONG, sizeof(outId), &outId, &outIdLen));

        // SQL ����
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

        // �̹� �����Ͱ� �����ϰų� ���� �߻�
        if (containsAccountOrError)
        {
            Protocol::S_CreateAccount createAccountPacket;
            createAccountPacket.set_success(false);
            const auto sendPacket = ClientPacketHandler::MakeSendBuffer(createAccountPacket);
            session->Send(sendPacket);
            return;
        }
    }

    // ���� ���� ����
    {
        DBConnection* dbConn = GDBConnectionPool->Pop();
        dbConn->Unbind();

        int32 accountId = idHash;
        SQLLEN len = 0;

        int32 password = pwHash;
        SQLLEN pwLen = 0;

        // �ѱ� ���� ���ε�
        ASSERT_CRASH(dbConn->BindParam(1, &accountId, &len));
        ASSERT_CRASH(dbConn->BindParam(2, &password, &pwLen));

        // SQL ����
        ASSERT_CRASH(dbConn->Execute(L"INSERT INTO [dbo].[Account]([id], [password]) VALUES(?, ?)"));

        GDBConnectionPool->Push(dbConn);
    }

    // �÷��̾� ���� ����
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

        // �ѱ� ���� ���ε�
        ASSERT_CRASH(dbConn->BindParam(1, &accountId, &len));
        ASSERT_CRASH(dbConn->BindParam(2, name, &nameLen));
        ASSERT_CRASH(dbConn->BindParam(3, &level, &levelLen));
        ASSERT_CRASH(dbConn->BindParam(4, &gold, &goldLen));

        // SQL ����
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

	// ���� �˻�
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

		// SQL ����
		ASSERT_CRASH(dbConn->Execute(L"SELECT id, password FROM [dbo].[Account] WHERE id = (?)"));

		bool result = dbConn->Fetch();
		GDBConnectionPool->Push(dbConn);

		// �н����� �˻�.
		result &= outPw == pwHash;
		if (!result)
		{
			loginPacket.set_loginok(false);
			const auto sendPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
			session->Send(sendPacket);
			return;
		}
	}

	// �÷��̾� ���� Read
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

		// SQL ����
		ASSERT_CRASH(dbConn->Execute(L"SELECT name, lv gold FROM [dbo].[Player] WHERE id = (?)"));
		bool result = dbConn->Fetch();
		if (!result)
		{
			loginPacket.set_loginok(false);
			const auto sendPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
			session->Send(sendPacket);
			return;
		}

		// �α��� ����
		loginPacket.set_loginok(true);
		const auto enterLoginPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
		session->Send(enterLoginPacket);

		// ����
		wstring wName(outName);
		string name(wName.begin(), wName.end());
		GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
		gameSession->HandleEnterGame(name, outLv, outGold);
	}

}
