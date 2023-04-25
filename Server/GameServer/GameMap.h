#pragma once
class GameMap
{
public:
	GameMap(int32 mapId);

private:
	void LoadMap(int mapId);

private:
	int _minX;
	int _minY;
	int _maxX;
	int _maxY;

	int _sizeX;
	int _sizeY;
};