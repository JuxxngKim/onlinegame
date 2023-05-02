#pragma once
#include "GameObject.h"
#include "Enum.pb.h"

class Player : public GameObject
{
public:
	Player(uint64 Id, Protocol::GameObjectType objectType, weak_ptr<class Room> room);

public:
	GameSessionRef GetOwnerSession() const { return _ownerSession.lock(); }
	
public:
	string					_name;
	weak_ptr<GameSession>	_ownerSession; // Cycle
};