#include "pch.h"
#include "Player.h"

Player::Player(uint64 Id, Protocol::GameObjectType objectType, weak_ptr<class Room> room)
    : GameObject(Id, objectType, room)
{
    _objectInfo.set_objecttype(Protocol::GameObjectType::PLAYER);
}
