#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(uint64 Id, Protocol::GameObjectType objectType, weak_ptr<class Room> room)
{
    _objectType = objectType;
    _objectInfo.set_allocated_posinfo(&_posInfo);
    _Id = Id;
    _room = room;
}

void GameObject::SetPosition()
{
    
}
