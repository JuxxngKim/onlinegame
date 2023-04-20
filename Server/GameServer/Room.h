#pragma once
#include "JobQueue.h"
#include "Enum.pb.h"

class Room : public JobQueue
{
public:
	// 싱글쓰레드 환경인마냥 코딩
	void Enter(PlayerRef player);
	void Leave(PlayerRef player);
	void Broadcast(SendBufferRef sendBuffer);
	void Update();

private:
	map<uint64, PlayerRef> _players;
};

extern shared_ptr<Room> GRoom;