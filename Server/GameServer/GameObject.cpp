#include "pch.h"
#include "GameObject.h"
#include "GameMap.h"

GameObject::GameObject(uint64 Id, Protocol::GameObjectType objectType, weak_ptr<class Room> room)
{
    _objectType = objectType;
    _objectInfo.set_allocated_posinfo(&_posInfo);
    _objectInfo.set_allocated_statinfo(&_statInfo);
    _objectInfo.set_objectid(Id);
    _Id = Id;
    _room = room;
}

GameObject::~GameObject()
{
    _objectInfo.release_posinfo();
    _objectInfo.release_statinfo();
}

void GameObject::SetPosition(Vector2Int pos)
{
    _posInfo.set_posx(pos.X);
    _posInfo.set_posy(pos.Y);
}

void GameObject::SetMoveDir(Protocol::MoveDir dir)
{
    _posInfo.set_movedir(dir);
}

void GameObject::SetState(Protocol::CreatureState state)
{
    _posInfo.set_state(state);
}

