#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "GameSession.h"
#include "GameMap.h"

Room::Room(int32 Id)
{
	InitMap(Id);
}

void Room::Enter(GameObjectRef object)
{
	auto objectType = object->GetObjectType();
}

void Room::Leave(GameObjectRef object)
{
	if (object->GetObjectType() == Protocol::GameObjectType::PLAYER)
	{

	}
	else if (object->GetObjectType() == Protocol::GameObjectType::MONSTER)
	{

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

void Room::InitMap(int32 Id)
{
	_map = MakeShared<GameMap>(Id);
}