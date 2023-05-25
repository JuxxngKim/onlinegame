#pragma once
#include "JobQueue.h"
#include "Room.h"

class DBTransaction : public JobQueue
{
public:
    void CreateAccount(PacketSessionRef session, Protocol::C_CreateAccount pkt);
    void Login(PacketSessionRef session, Protocol::C_Login pkt);
};

extern DBTransaction GDBTransaction;
