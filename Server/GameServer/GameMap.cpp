#include "pch.h"
#include "GameMap.h"
#include <iostream>
#include <fstream>
#include <string>
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

	for(int i = 0; i < yCount; ++i)
	{
		delete[] _collision[i];
		delete[] _objects[i];
	}

	delete[] _collision;
	delete[] _objects;
}

bool GameMap::CanGo(Vector2Int cellPos, bool checkObjects)
{
	if (cellPos.X < _minX || cellPos.X > _maxX)
		return false;
	if (cellPos.Y < _minY || cellPos.Y > _maxY)
		return false;

	int x = cellPos.X - _minY;
	int y = _maxX - cellPos.Y;
	return !_collision[y][x] && (!checkObjects || _objects[y][x] == 0);
	return false;
}

uint64 GameMap::Find(Vector2Int cellPos)
{
	if (cellPos.X < _minX || cellPos.X > _maxX)
		return 0;
	if (cellPos.Y < _minY || cellPos.Y > _maxY)
		return 0;

	int x = cellPos.X - _minX;
	int y = _maxY - cellPos.Y;
	return _objects[y][x];
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
	if(_objects[y][x] == 0)
		return false;
	
	if (_objects[y][x] == gameObject->GetID())
		_objects[y][x] = 0;

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
		_objects[y][x] = gameObject->GetID();
	}
	return true;
}

void GameMap::LoadMap(int mapId)
{
	string line;
	string path = "../../Common/MapData/Map" + mapId;
	path.append(".txt");
	ifstream file(path);
	if (!file.is_open())
	{
		cout << "Unable to open map file";
		return;
	}

	getline(file, line);
	_minX = std::stoi(line);

	getline(file, line);
	_maxX = std::stoi(line);

	getline(file, line);
	_minY = std::stoi(line);

	getline(file, line);
	_maxX = std::stoi(line);

	const int xCount = _maxX - _minX + 1;
	const int yCount = _maxY - _minY + 1;

	_collision = new bool*[yCount];
	for (int i = 0; i < yCount; ++i)
		_collision[i] = new bool[xCount];

	_objects = new uint64*[yCount];
	for (int i = 0; i < yCount; ++i)
		_objects[i] = new uint64[xCount]{0,};

	for (int y = 0; y < yCount; y++)
	{
		getline(file, line);
		for (int x = 0; x < xCount; x++)
		{
			_collision[y][x] = (line[x] == '1' ? true : false);
		}
	}

	file.close();
}
