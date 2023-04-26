#pragma once
#include "JobQueue.h"
#include "Enum.pb.h"
#include "GameTypes.h"

class Room : public JobQueue
{
public:
	Room(int32 Id);

public:
	void Enter(GameObjectRef object);
	void Leave(GameObjectRef object);
	void Broadcast(SendBufferRef sendBuffer);
	void Update();

private:
	void InitMap(int32 Id);

private:
	GameMapRef _map;
	map<uint64, PlayerRef> _players;
	map<uint64, PlayerRef> _monsters;
};