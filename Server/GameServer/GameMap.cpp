#include "pch.h"
#include "GameMap.h"

Vector2Int Vector2Int::up{ 0, 1 };
Vector2Int Vector2Int::down{ 0, -1 };
Vector2Int Vector2Int::left{ -1, 0 };
Vector2Int Vector2Int::right{ 1, 0 };

GameMap::GameMap(int32 mapId)
{
	LoadMap(mapId);
}

bool GameMap::CanGo(Vector2Int cellPos, bool checkObjects = true)
{
	if (cellPos.X < _minX || cellPos.X > _maxX)
		return false;
	if (cellPos.Y < _minY || cellPos.Y > _maxY)
		return false;

	int x = cellPos.X - _minY;
	int y = _maxX - cellPos.Y;
	//return !_collision[y][x] && (!checkObjects || _objects[y][x] == nullptr);
	return false;
}


void GameMap::LoadMap(int mapId)
{
	
}
