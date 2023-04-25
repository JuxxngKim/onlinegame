#pragma once
#include "JobQueue.h"
#include "Room.h"

class GameLogic : JobQueue
{

public:
	void AddRoom(int roomId);
	std::weak_ptr<Room> FindFoom(int roomId);
	void Update();

private:
	map<uint64, RoomRef> _rooms;
};

extern GameLogic GGameLogic;
