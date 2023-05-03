#include "pch.h"
#include "GameMap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "GameObject.h"

Vector2Int Vector2Int::up{ 0, 1 };
Vector2Int Vector2Int::down{ 0, -1 };
Vector2Int Vector2Int::left{ -1, 0 };
Vector2Int Vector2Int::right{ 1, 0 };

GameMap::GameMap(int32 mapId)
{
	LoadMap(mapId);
}

GameMap::~GameMap()
{
	const int xCount = _maxX - _minX + 1;
	const int yCount = _maxY - _minY + 1;
}

bool GameMap::CanGo(Vector2Int cellPos, bool checkObjects)
{
	if (cellPos.X < _minX || cellPos.X > _maxX)
		return false;
	if (cellPos.Y < _minY || cellPos.Y > _maxY)
		return false;

	int x = cellPos.X - _minY;
	int y = _maxX - cellPos.Y;
	Tile* tile = GetTileAt({ x, y });
	if (tile == nullptr)
		return false;

	return !tile->collision && (!checkObjects || tile->object != 0);
}

bool GameMap::ApplyLeave(GameObjectRef gameObject)
{
	const weak_ptr<Room> room = gameObject->GetRoom();
	if(room.expired())
		return false;

	const Protocol::PositionInfo posInfo = gameObject->GetPos();
	if (posInfo.posx() < _minX || posInfo.posy() > _maxX)
		return false;
	if (posInfo.posy() < _minY || posInfo.posy() > _maxY)
		return false;

	int x = posInfo.posx() - _minX;
	int y = _maxY - posInfo.posy();
	

	Tile* tile = GetTileAt({ x, y });
	if (tile == nullptr)
		return false;

	if (tile->object == gameObject->GetID())
		tile->object = 0;

	return true;
}

bool GameMap::ApplyMove(GameObjectRef gameObject, Vector2Int dest)
{
	ApplyLeave(gameObject);
	
	const weak_ptr<Room> room = gameObject->GetRoom();
	if(room.expired())
		return false;

	const Protocol::PositionInfo posInfo = gameObject->GetPos();
	if (CanGo(dest, true) == false)
		return false;

	{
		int x = dest.X - _minX;
		int y = _maxY - dest.Y;

		Tile* tile = GetTileAt({ x, y });
		if (tile->object == gameObject->GetID())
			tile->object = gameObject->GetID();
	}

	return true;
}

namespace fs = std::filesystem;

void GameMap::LoadMap(int mapId)
{
	string curPath = fs::current_path().string();

	//string path = "C:\\GameServer\\onlinegame\\Server\\Common\\MapData\\Map_1.txt";
	string path = "../Common/MapData/Map_1.txt";
	ifstream file;
	file.open(path);

	if (!file.is_open())
	{
		cout << "Unable to open map file";
		return;
	}

	file >> _minX >> _maxX;
	file >> _minY >> _maxY;

	const int xCount = _maxX - _minX + 1;
	const int yCount = _maxY - _minY + 1;

	_mapSize = { xCount , yCount };

	_tiles = vector<vector<Tile>>(yCount, vector<Tile>(xCount));
	for (int32 y = 0; y < yCount; y++)
	{
		for (int32 x = 0; x < xCount; x++)
		{
			_tiles[y][x] = Tile{ 0, false };
		}
	}

	for (int32 y = 0; y < yCount; y++)
	{
		string line;
		file >> line;

		for (int32 x = 0; x < xCount; x++)
			_tiles[y][x].collision = line[x] - '0';
	}

	file.close();
}

Tile* GameMap::GetTileAt(Vector2Int pos)
{
	if (pos.X < 0 || pos.X >= _mapSize.X || pos.Y < 0 || pos.Y >= _mapSize.Y)
		return nullptr;

	return &_tiles[pos.Y][pos.X];
}
