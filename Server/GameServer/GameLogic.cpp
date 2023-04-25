#include "pch.h"
#include "GameLogic.h"

GameLogic GGameLogic;

void GameLogic::AddRoom(int roomId)
{
	_rooms[roomId] = MakeShared<Room>(roomId);
}

std::weak_ptr<Room> GameLogic::FindFoom(int roomId)
{
	return std::weak_ptr<Room>(_rooms[roomId]);
}

void GameLogic::Update()
{
	Execute();

	for (const auto& pair : _rooms)
	{
		pair.second->Update();
	}
}