#pragma once
#include "Session.h"
#include "GameTypes.h"
#include "Player.h"
#include "Protocol.pb.h"

class GameSession : public PacketSession
{
public:
	~GameSession()
	{
		cout << "~GameSession" << endl;
	}

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;

public:
	void HandleEnterGame();
	void HandleLogin(string name, int32 level, int32 gold);
	
public:
	PlayerDBData _playerDBData;
	PlayerRef _currentPlayer;
	weak_ptr<class Room> _room;
	bool _isLogin;
};
