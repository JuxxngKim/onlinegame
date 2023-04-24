#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(uint64 Id, Protocol::GameObjectType objectType)
{
    _objectType = objectType;
    _objectInfo.set_allocated_posinfo(&_posInfo);
    _Id = Id;
}

void GameObject::SetPosition()
{
    
}
