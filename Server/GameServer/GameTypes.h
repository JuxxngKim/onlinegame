#pragma once

#define USING_SHARED_PTR(name)	using name##Ref = std::shared_ptr<class name>;

USING_SHARED_PTR(GameSession);
USING_SHARED_PTR(Player); 
USING_SHARED_PTR(GameObject);
USING_SHARED_PTR(Room);
USING_SHARED_PTR(GameMap);