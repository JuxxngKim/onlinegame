#include "pch.h"
#include "Room.h"

#include "ClientPacketHandler.h"
#include "Player.h"
#include "GameSession.h"
#include "GameMap.h"

Room::Room(int32 Id)
{
	InitMap(Id);
}

void Room::Enter(GameObjectRef objectRef)
{
	Protocol::GameObjectType objectType = objectRef->GetObjectType();
	if(objectType == Protocol::PLAYER)
	{
		if (_players.contains(objectRef->GetID()))
			return;

		const PlayerRef playerRef = static_pointer_cast<Player>(objectRef);
		auto spawnPos = Vector2Int(2, 3);

		playerRef->SetMoveDir(Protocol::MoveDir::DOWN);
		playerRef->SetPosition(spawnPos);
		playerRef->SetState(Protocol::CreatureState::IDLE);

		_players[playerRef->GetID()] = playerRef;

		// 본인한테 정보 전송
		{
			Protocol::S_EnterGame enterPacket;
			Protocol::ObjectInfo* objectInfo = enterPacket.mutable_player();
			*objectInfo = playerRef->GetObjectInfo();
			const auto enterSendBuffer = ClientPacketHandler::MakeSendBuffer(enterPacket); 
			playerRef->GetOwnerSession()->Send(enterSendBuffer);

			Protocol::S_Spawn spawnPacket;
			for (auto& p : _players)
			{
				Protocol::ObjectInfo* info = spawnPacket.add_objects();
				*info = p.second->GetObjectInfo();
			}
			
			for (auto& p : _monsters)
			{
				Protocol::ObjectInfo* info = spawnPacket.add_objects();
				*info = p.second->GetObjectInfo();
			}

			const auto spawnSendBuffer = ClientPacketHandler::MakeSendBuffer(spawnPacket); 
			playerRef->GetOwnerSession()->Send(spawnSendBuffer);
		}
	}

	// 타인한테 정보 전송
	{
		Protocol::S_Spawn spawnPacket;
		for (auto& p : _players)
		{
			if(p.second->GetID() == objectRef->GetID())
				continue;
			
			Protocol::ObjectInfo* info = spawnPacket.add_objects();
			*info = objectRef->GetObjectInfo();
			p.second->GetOwnerSession()->Send(ClientPacketHandler::MakeSendBuffer(spawnPacket));
		}
	}
}

void Room::Leave(GameObjectRef objectRef)
{
	Protocol::GameObjectType objectType = objectRef->GetObjectType();
	uint64 objId = objectRef->GetID();

	if (objectType == Protocol::PLAYER)
	{
		if (_players.contains(objId))
			_players.erase(objId);
	}
	else if (objectType == Protocol::MONSTER)
	{
		if (_monsters.contains(objId))
			_monsters.erase(objId);
	}

	{
		Protocol::S_Despawn despawnPacket;
		despawnPacket.add_objectids(objectRef->GetID());
		Broadcast(ClientPacketHandler::MakeSendBuffer(despawnPacket));
	}
}

void Room::Broadcast(SendBufferRef sendBuffer)
{
	for (auto& p : _players)
	{
		p.second->GetOwnerSession()->Send(sendBuffer);
	}
}

void Room::Update()
{
	Execute();
}

void Room::Handle_Move(PlayerRef player, Protocol::C_Move pkt)
{
	Protocol::PositionInfo movePosInfo = pkt.posinfo(); 
	Protocol::PositionInfo posInfo = player->_posInfo;

	Vector2Int vector2_int = { movePosInfo };
	if (posInfo.posx() != movePosInfo.posx() ||
		posInfo.posy() != movePosInfo.posy())
	{
		if(_map->CanGo(vector2_int, true) == false)
			return;
	}

	player->SetPosition(vector2_int);
	player->SetMoveDir(pkt.posinfo().movedir());
	player->SetState(pkt.posinfo().state());

	{
		Protocol::S_Move pkt;
		pkt.set_objectid(player->GetID());
		Protocol::PositionInfo* sendPosInfo = pkt.mutable_posinfo();
		*sendPosInfo = player->_posInfo;
		
		Broadcast(ClientPacketHandler::MakeSendBuffer(pkt));
	}
}

void Room::InitMap(int32 Id)
{
	_map = MakeShared<GameMap>(Id);
}
