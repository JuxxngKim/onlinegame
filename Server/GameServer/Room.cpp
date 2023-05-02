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
		const PlayerRef playerRef = static_pointer_cast<Player>(objectRef);
		_map->ApplyMove(playerRef, Vector2Int(0, 0));
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
	if (objectType == Protocol::PLAYER)
	{
		_players.erase(objectRef->GetID());
	}
	else if (objectType == Protocol::MONSTER)
	{
		_monsters.erase(objectRef->GetID());
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

	if(posInfo.posx() != movePosInfo.posx() ||
		posInfo.posy() != movePosInfo.posy())
	{
		Vector2Int vector2_int = Vector2Int(movePosInfo.posx(), movePosInfo.posy());
		if(_map->CanGo(vector2_int, true) == false)
			return;
	}

	player->_posInfo.set_posx(movePosInfo.posx());
	player->_posInfo.set_posy(movePosInfo.posy());
	player->_posInfo.set_state(pkt.posinfo().state());
	player->_posInfo.set_movedir(pkt.posinfo().movedir());

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
