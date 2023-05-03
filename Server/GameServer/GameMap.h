#pragma once

struct Tile
{
	uint64 object = 0;
	bool collision = false;
};

class GameMap
{
public:
	GameMap(int32 mapId);
	~GameMap();

public:
	bool CanGo(Vector2Int cellPos, bool checkObjects = true);
	bool ApplyLeave(GameObjectRef gameObject);
	bool ApplyMove(GameObjectRef gameObject, Vector2Int dest);
	Tile* GetTileAt(Vector2Int pos);

private:
	void LoadMap(int mapId);

private:
	Vector2Int _mapSize = { 0, 0 };
	vector<vector<Tile>> _tiles;

	int _minX;
	int _minY;
	int _maxX;
	int _maxY;
};