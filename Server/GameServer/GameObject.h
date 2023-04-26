#pragma once
#include "Enum.pb.h"
#include "Struct.pb.h"

class GameObject
{
public:
	GameObject(uint64 Id, Protocol::GameObjectType objectType, weak_ptr<class Room> room);

public:
	uint64 GetID() const { return _Id; }
	Protocol::GameObjectType GetObjectType() const { return _objectType; }

public:
	void SetPosition();

protected:
	Protocol::ObjectInfo _objectInfo;
	Protocol::PositionInfo _posInfo;
	Protocol::StatInfo _statInfo;

protected:
	weak_ptr<class Room> _room;
	Protocol::GameObjectType _objectType;
	uint64 _Id;
};

