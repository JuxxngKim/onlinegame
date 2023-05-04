#pragma once
#include "Enum.pb.h"
#include "Struct.pb.h"

class GameObject
{
public:
	GameObject(uint64 Id, Protocol::GameObjectType objectType, weak_ptr<class Room> room);
	virtual ~GameObject();

public:
	weak_ptr<class Room> GetRoom() { return _room; }
	
public:
	uint64 GetID() const { return _Id; }
	Protocol::GameObjectType GetObjectType() const { return _objectType; }
	const Protocol::ObjectInfo& GetObjectInfo() const { return _objectInfo; }
	const Protocol::PositionInfo& GetPos() const { return _posInfo; }
	const Protocol::StatInfo& GetStat() const { return _statInfo; }
	
public:
	void SetPosition(Vector2Int pos);
	void SetMoveDir(Protocol::MoveDir dir);
	void SetState(Protocol::CreatureState state);

public:
	Protocol::ObjectInfo _objectInfo;
	Protocol::PositionInfo _posInfo;
	Protocol::StatInfo _statInfo;

protected:
	weak_ptr<class Room> _room;
	Protocol::GameObjectType _objectType;
	uint64 _Id;
};

