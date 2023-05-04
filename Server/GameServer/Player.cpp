#include "pch.h"
#include "Player.h"

Player::Player(uint64 Id, Protocol::GameObjectType objectType, weak_ptr<class Room> room)
    : GameObject(Id, objectType, room)
{
    _objectInfo.set_objecttype(Protocol::GameObjectType::PLAYER);

    _statInfo.set_level(1);
    _statInfo.set_attack(1);
    _statInfo.set_hp(30);
    _statInfo.set_maxhp(30);
    _statInfo.set_speed(3);
    _statInfo.set_totalexp(0);
}
