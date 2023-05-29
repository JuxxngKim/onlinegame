#pragma once
#include "GameObject.h"
#include "Enum.pb.h"

struct PlayerDBData
{
	string name;
	int32 level;
	int32 gold;
};

class Player : public GameObject
{
public:
	Player(uint64 Id, Protocol::GameObjectType objectType, weak_ptr<class Room> room);

public:
	void SetPlayerInfo(PlayerDBData data);
	GameSessionRef GetOwnerSession() const { return _ownerSession.lock(); }
	const string& GetName() const { return _name; }
	
public:
	string					_name;
	weak_ptr<GameSession>	_ownerSession; // Cycle
};