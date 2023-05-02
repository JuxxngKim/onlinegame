#include "pch.h"
#include "ClientPacketHandler.h"
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
	return false;
}

bool Handle_C_Skill(PacketSessionRef& session, Protocol::C_Skill& pkt)
{
	return false;
}

bool Handle_C_Login(PacketSessionRef& session, Protocol::C_Login& pkt)
{
	return false;
}

bool Handle_C_CreatePlayer(PacketSessionRef& session, Protocol::C_CreatePlayer& pkt)
{
	return false;
}

bool Handle_C_EnterGame(PacketSessionRef& session, Protocol::C_EnterGame& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	gameSession->HandleEnterGame(pkt);
	return true;
}

bool Handle_C_EquipItem(PacketSessionRef& session, Protocol::C_EquipItem& pkt)
{
	return false;
}

bool Handle_C_Pong(PacketSessionRef& session, Protocol::C_Pong& pkt)
{
	return false;
}

//bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
//{
//	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
//
//	// TODO : Validation üũ
//
//	Protocol::S_LOGIN loginPkt;
//	loginPkt.set_success(true);
//
//	// DB���� �÷��� ������ �ܾ�´�
//	// GameSession�� �÷��� ������ ���� (�޸�)
//
//	// ID �߱� (DB ���̵� �ƴϰ�, �ΰ��� ���̵�)
//	static Atomic<uint64> idGenerator = 1;
//
//	{
//		auto player = loginPkt.add_players();
//		player->set_name(u8"DB�����ܾ���̸�1");
//		player->set_playertype(Protocol::PLAYER_TYPE_KNIGHT);
//
//		PlayerRef playerRef = MakeShared<Player>();
//		playerRef->playerId = idGenerator++;
//		playerRef->name = player->name();
//		playerRef->type = player->playertype();
//		playerRef->ownerSession = gameSession;
//		
//		gameSession->_players.push_back(playerRef);
//	}
//
//	{
//		auto player = loginPkt.add_players();
//		player->set_name(u8"DB�����ܾ���̸�2");
//		player->set_playertype(Protocol::PLAYER_TYPE_MAGE);
//
//		PlayerRef playerRef = MakeShared<Player>();
//		playerRef->playerId = idGenerator++;
//		playerRef->name = player->name();
//		playerRef->type = player->playertype();
//		playerRef->ownerSession = gameSession;
//
//		gameSession->_players.push_back(playerRef);
//	}
//
//	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
//	session->Send(sendBuffer);
//
//	return true;
//}

//bool Handle_C_ENTER_GAME(PacketSessionRef& session, Protocol::C_ENTER_GAME& pkt)
//{
//	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
//
//	uint64 index = pkt.playerindex();
//	// TODO : Validation
//
//	gameSession->_currentPlayer = gameSession->_players[index]; // READ_ONLY?
//	gameSession->_room = GRoom;
//
//	GRoom->DoAsync(&Room::Enter, gameSession->_currentPlayer);
//
//	Protocol::S_ENTER_GAME enterGamePkt;
//	enterGamePkt.set_success(true);
//	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterGamePkt);
//	gameSession->_currentPlayer->ownerSession->Send(sendBuffer);
//
//	return true;
//}
//
//bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt)
//{
//	std::cout << pkt.msg() << endl;
//
//	Protocol::S_CHAT chatPkt;
//	chatPkt.set_msg(pkt.msg());
//	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);
//
//	GRoom->DoAsync(&Room::Broadcast, sendBuffer);
//
//	return true;
//}
