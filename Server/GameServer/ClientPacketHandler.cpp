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