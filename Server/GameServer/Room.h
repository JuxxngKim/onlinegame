#pragma once
#include "JobQueue.h"
#include "Enum.pb.h"

class Room : public JobQueue
{
public:
	// �̱۾����� ȯ���θ��� �ڵ�
	void Enter(PlayerRef player);
	void Leave(PlayerRef player);
	void Broadcast(SendBufferRef sendBuffer);
	void Update();

private:
	map<uint64, PlayerRef> _players;
};

extern shared_ptr<Room> GRoom;