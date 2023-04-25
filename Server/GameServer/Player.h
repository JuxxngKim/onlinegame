#pragma once
#include "GameObject.h"
#include "Enum.pb.h"

class Player : public GameObject
{
public:
	Player(uint64 Id, Protocol::GameObjectType objectType, weak_ptr<class Room> room);

public:
	GameSessionRef GetOwnerSession() { return _ownerSession; }
	
public:
	string					_name;
	GameSessionRef			_ownerSession; // Cycle
};