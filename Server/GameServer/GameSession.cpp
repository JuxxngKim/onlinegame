#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"
#include "Player.h"
#include "Room.h"
#include "GameLogic.h"

void GameSession::OnConnected()
{
	GSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));
}

void GameSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<GameSession>(shared_from_this()));

	if (_currentPlayer)
	{
		shared_ptr<GameObject> objPtr;
		objPtr = _currentPlayer;

		if (auto room = _room.lock())
			room->DoAsync(&Room::Leave, objPtr);
	}

	_currentPlayer = nullptr;
}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	ClientPacketHandler::HandlePacket(session, buffer, len);
}

void GameSession::OnSend(int32 len)
{
}

void GameSession::HandleEnterGame(string name, int32 level)
{
	static Atomic<uint64> idGenerator{ 1 };
	_room = GGameLogic.FindFoom(1);

	_currentPlayer = MakeShared<Player>(idGenerator++, Protocol::GameObjectType::PLAYER, _room);

	if (_room.expired())
		return;

	_currentPlayer->_ownerSession = weak_ptr<GameSession>(static_pointer_cast<GameSession>(shared_from_this()));

	const RoomRef roomRef = _room.lock();
	const GameObjectRef objectRef = _currentPlayer;
	roomRef->DoAsync(&Room::Enter, objectRef);
}