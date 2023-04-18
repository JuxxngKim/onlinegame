#pragma once
#include "JobQueue.h"
#include "Room.h"

class GameLogic : JobQueue
{
public:
	void Update();

private:
	map<uint64, RoomRef> _rooms;
};

