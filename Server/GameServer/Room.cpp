#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "GameSession.h"

shared_ptr<Room> GRoom = make_shared<Room>();

void Room::Enter(GameObjectRef object)
{
	

	
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

}