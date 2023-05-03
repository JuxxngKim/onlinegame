#pragma once

struct Pos
{
public:
	Pos(int32 y, int32 x) { Y = y; X = x; }

public:
	int32 Y;
	int32 X;
};

struct Vector2Int
{
public:
	Vector2Int(int32 x, int32 y) { Y = y; X = x; }

	static Vector2Int up;
	static Vector2Int down;
	static Vector2Int left;
	static Vector2Int right;

public:
	friend Vector2Int operator+(const Vector2Int& a, const Vector2Int& b)
	{
		return Vector2Int(a.X + b.X, a.Y + b.Y);
	}

	friend Vector2Int operator-(const Vector2Int& a, const Vector2Int& b)
	{
		return Vector2Int(a.X - b.X, a.Y - b.Y);
	}

public:
	int32 Y;
	int32 X;
};

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
	uint64 Find(Vector2Int cellPos);
	bool ApplyLeave(GameObjectRef gameObject);
	bool ApplyMove(GameObjectRef gameObject, Vector2Int dest);
	Tile* GetTileAt(Vector2Int pos);

private:
	void LoadMap(int mapId);

private:
	vector<vector<Tile>> _tiles;
	//bool** _collision;
	//uint64** _objects;

	int _minX;
	int _minY;
	int _maxX;
	int _maxY;

	Vector2Int _mapSize = {0, 0};
};