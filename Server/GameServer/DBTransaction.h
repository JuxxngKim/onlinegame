#pragma once
#include "JobQueue.h"
#include "Room.h"

class DBTransaction : public JobQueue
{
public:
    void CreateAccount(PacketSessionRef session, string id, string password);
    void Login(PacketSessionRef session, Protocol::C_Login pkt);
};

extern DBTransactionRef GDBTransaction;
