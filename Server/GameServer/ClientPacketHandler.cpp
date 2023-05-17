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

	// TODO: DB 검증
	loginPacket.set_loginok(true);

	const auto enterLoginPacket = ClientPacketHandler::MakeSendBuffer(loginPacket);
	session->Send(enterLoginPacket);

	if(loginPacket.loginok() == false)
		return true;

	return true;
}


bool Handle_C_EnterGame(PacketSessionRef& session, Protocol::C_EnterGame& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	gameSession->HandleEnterGame(pkt);
	return true;
}

bool Handle_C_Chat(PacketSessionRef& session, Protocol::C_Chat& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	const RoomRef roomRef = gameSession->_room.lock();

	Protocol::S_Chat chatPacket;
	chatPacket.set_objectid(gameSession->_currentPlayer->GetID());
	chatPacket.set_username("test");
	chatPacket.set_message(pkt.message());
	
	const auto sendPacket = ClientPacketHandler::MakeSendBuffer(chatPacket);
	
	roomRef->DoAsync(&Room::Broadcast, sendPacket);
	return true;
}

bool Handle_C_CreateAccount(PacketSessionRef& session, Protocol::C_CreateAccount& pkt)
{
	Protocol::S_CreateAccount createAccountPacket;

	// TODO: DB 검증
	createAccountPacket.set_success(true);

	const auto enterLoginPacket = ClientPacketHandler::MakeSendBuffer(createAccountPacket);
	session->Send(enterLoginPacket);
	
	return true;
}

bool Handle_C_Pong(PacketSessionRef& session, Protocol::C_Pong& pkt)
{
	return true;
}
