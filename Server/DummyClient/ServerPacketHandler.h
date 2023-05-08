#pragma once
#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
	PKT_S_EnterGame = 1000,
	PKT_S_LeaveGame = 1001,
	PKT_S_Spawn = 1002,
	PKT_S_Despawn = 1003,
	PKT_C_Move = 1004,
	PKT_S_Move = 1005,
	PKT_C_Skill = 1006,
	PKT_S_Skill = 1007,
	PKT_S_ChangeHp = 1008,
	PKT_S_Die = 1009,
	PKT_S_Connected = 1010,
	PKT_C_Login = 1011,
	PKT_S_Login = 1012,
	PKT_C_EnterGame = 1013,
	PKT_S_ChangeStat = 1014,
	PKT_C_Chat = 1015,
	PKT_S_Chat = 1016,
	PKT_C_CreateAccount = 1017,
	PKT_S_CreateAccount = 1018,
	PKT_S_Ping = 1019,
	PKT_C_Pong = 1020,
};

// Custom Handlers
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_S_EnterGame(PacketSessionRef& session, Protocol::S_EnterGame& pkt);
bool Handle_S_LeaveGame(PacketSessionRef& session, Protocol::S_LeaveGame& pkt);
bool Handle_S_Spawn(PacketSessionRef& session, Protocol::S_Spawn& pkt);
bool Handle_S_Despawn(PacketSessionRef& session, Protocol::S_Despawn& pkt);
bool Handle_S_Move(PacketSessionRef& session, Protocol::S_Move& pkt);
bool Handle_S_Skill(PacketSessionRef& session, Protocol::S_Skill& pkt);
bool Handle_S_ChangeHp(PacketSessionRef& session, Protocol::S_ChangeHp& pkt);
bool Handle_S_Die(PacketSessionRef& session, Protocol::S_Die& pkt);
bool Handle_S_Connected(PacketSessionRef& session, Protocol::S_Connected& pkt);
bool Handle_S_Login(PacketSessionRef& session, Protocol::S_Login& pkt);
bool Handle_S_ChangeStat(PacketSessionRef& session, Protocol::S_ChangeStat& pkt);
bool Handle_S_Chat(PacketSessionRef& session, Protocol::S_Chat& pkt);
bool Handle_S_CreateAccount(PacketSessionRef& session, Protocol::S_CreateAccount& pkt);
bool Handle_S_Ping(PacketSessionRef& session, Protocol::S_Ping& pkt);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
		GPacketHandler[PKT_S_EnterGame] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_EnterGame>(Handle_S_EnterGame, session, buffer, len); };
		GPacketHandler[PKT_S_LeaveGame] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_LeaveGame>(Handle_S_LeaveGame, session, buffer, len); };
		GPacketHandler[PKT_S_Spawn] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_Spawn>(Handle_S_Spawn, session, buffer, len); };
		GPacketHandler[PKT_S_Despawn] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_Despawn>(Handle_S_Despawn, session, buffer, len); };
		GPacketHandler[PKT_S_Move] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_Move>(Handle_S_Move, session, buffer, len); };
		GPacketHandler[PKT_S_Skill] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_Skill>(Handle_S_Skill, session, buffer, len); };
		GPacketHandler[PKT_S_ChangeHp] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_ChangeHp>(Handle_S_ChangeHp, session, buffer, len); };
		GPacketHandler[PKT_S_Die] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_Die>(Handle_S_Die, session, buffer, len); };
		GPacketHandler[PKT_S_Connected] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_Connected>(Handle_S_Connected, session, buffer, len); };
		GPacketHandler[PKT_S_Login] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_Login>(Handle_S_Login, session, buffer, len); };
		GPacketHandler[PKT_S_ChangeStat] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_ChangeStat>(Handle_S_ChangeStat, session, buffer, len); };
		GPacketHandler[PKT_S_Chat] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_Chat>(Handle_S_Chat, session, buffer, len); };
		GPacketHandler[PKT_S_CreateAccount] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_CreateAccount>(Handle_S_CreateAccount, session, buffer, len); };
		GPacketHandler[PKT_S_Ping] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_Ping>(Handle_S_Ping, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::C_Move& pkt) { return MakeSendBuffer(pkt, PKT_C_Move); }
	static SendBufferRef MakeSendBuffer(Protocol::C_Skill& pkt) { return MakeSendBuffer(pkt, PKT_C_Skill); }
	static SendBufferRef MakeSendBuffer(Protocol::C_Login& pkt) { return MakeSendBuffer(pkt, PKT_C_Login); }
	static SendBufferRef MakeSendBuffer(Protocol::C_EnterGame& pkt) { return MakeSendBuffer(pkt, PKT_C_EnterGame); }
	static SendBufferRef MakeSendBuffer(Protocol::C_Chat& pkt) { return MakeSendBuffer(pkt, PKT_C_Chat); }
	static SendBufferRef MakeSendBuffer(Protocol::C_CreateAccount& pkt) { return MakeSendBuffer(pkt, PKT_C_CreateAccount); }
	static SendBufferRef MakeSendBuffer(Protocol::C_Pong& pkt) { return MakeSendBuffer(pkt, PKT_C_Pong); }

private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, pkt);
	}

	template<typename T>
	static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};