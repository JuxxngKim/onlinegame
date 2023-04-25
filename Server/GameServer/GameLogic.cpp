#include "pch.h"
#include "GameLogic.h"

void GameLogic::AddRoom(int mapId)
{
	_rooms[mapId] = MakeShared<Room>(mapId);
}

void GameLogic::Update()
{
	Execute();

	for (const auto& pair : _rooms)
	{
		pair.second->Update();
	}
}