#pragma once
#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
	PKT_S_ENTERGAME = 1000,
	PKT_S_LEAVEGAME = 1001,
	PKT_S_SPAWN = 1002,
	PKT_S_DESPAWN = 1003,
	PKT_C_MOVE = 1004,
	PKT_S_MOVE = 1005,
	PKT_C_SKILL = 1006,
	PKT_S_SKILL = 1007,
	PKT_S_CHANGEHP = 1008,
	PKT_S_DIE = 1009,
	PKT_S_CONNECTED = 1010,
	PKT_C_LOGIN = 1011,
	PKT_S_LOGIN = 1012,
	PKT_C_CREATEPLAYER = 1013,
	PKT_S_CREATEPLAYER = 1014,
	PKT_C_ENTERGAME = 1015,
	PKT_S_ITEMLIST = 1016,
	PKT_S_ADDITEM = 1017,
	PKT_C_EQUIPITEM = 1018,
	PKT_S_EQUIPITEM = 1019,
	PKT_S_CHANGESTAT = 1020,
	PKT_S_PING = 1021,
	PKT_C_PONG = 1022,
};

// Custom Handlers
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_S_ENTERGAME(PacketSessionRef& session, Protocol::S_ENTERGAME& pkt);
bool Handle_S_LEAVEGAME(PacketSessionRef& session, Protocol::S_LEAVEGAME& pkt);
bool Handle_S_SPAWN(PacketSessionRef& session, Protocol::S_SPAWN& pkt);
bool Handle_S_DESPAWN(PacketSessionRef& session, Protocol::S_DESPAWN& pkt);
bool Handle_S_MOVE(PacketSessionRef& session, Protocol::S_MOVE& pkt);
bool Handle_S_SKILL(PacketSessionRef& session, Protocol::S_SKILL& pkt);
bool Handle_S_CHANGEHP(PacketSessionRef& session, Protocol::S_CHANGEHP& pkt);
bool Handle_S_DIE(PacketSessionRef& session, Protocol::S_DIE& pkt);
bool Handle_S_CONNECTED(PacketSessionRef& session, Protocol::S_CONNECTED& pkt);
bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt);
bool Handle_S_CREATEPLAYER(PacketSessionRef& session, Protocol::S_CREATEPLAYER& pkt);
bool Handle_S_ITEMLIST(PacketSessionRef& session, Protocol::S_ITEMLIST& pkt);
bool Handle_S_ADDITEM(PacketSessionRef& session, Protocol::S_ADDITEM& pkt);
bool Handle_S_EQUIPITEM(PacketSessionRef& session, Protocol::S_EQUIPITEM& pkt);
bool Handle_S_CHANGESTAT(PacketSessionRef& session, Protocol::S_CHANGESTAT& pkt);
bool Handle_S_PING(PacketSessionRef& session, Protocol::S_PING& pkt);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
		GPacketHandler[PKT_S_ENTERGAME] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_ENTERGAME>(Handle_S_ENTERGAME, session, buffer, len); };
		GPacketHandler[PKT_S_LEAVEGAME] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_LEAVEGAME>(Handle_S_LEAVEGAME, session, buffer, len); };
		GPacketHandler[PKT_S_SPAWN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_SPAWN>(Handle_S_SPAWN, session, buffer, len); };
		GPacketHandler[PKT_S_DESPAWN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_DESPAWN>(Handle_S_DESPAWN, session, buffer, len); };
		GPacketHandler[PKT_S_MOVE] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_MOVE>(Handle_S_MOVE, session, buffer, len); };
		GPacketHandler[PKT_S_SKILL] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_SKILL>(Handle_S_SKILL, session, buffer, len); };
		GPacketHandler[PKT_S_CHANGEHP] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_CHANGEHP>(Handle_S_CHANGEHP, session, buffer, len); };
		GPacketHandler[PKT_S_DIE] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_DIE>(Handle_S_DIE, session, buffer, len); };
		GPacketHandler[PKT_S_CONNECTED] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_CONNECTED>(Handle_S_CONNECTED, session, buffer, len); };
		GPacketHandler[PKT_S_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_LOGIN>(Handle_S_LOGIN, session, buffer, len); };
		GPacketHandler[PKT_S_CREATEPLAYER] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_CREATEPLAYER>(Handle_S_CREATEPLAYER, session, buffer, len); };
		GPacketHandler[PKT_S_ITEMLIST] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_ITEMLIST>(Handle_S_ITEMLIST, session, buffer, len); };
		GPacketHandler[PKT_S_ADDITEM] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_ADDITEM>(Handle_S_ADDITEM, session, buffer, len); };
		GPacketHandler[PKT_S_EQUIPITEM] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_EQUIPITEM>(Handle_S_EQUIPITEM, session, buffer, len); };
		GPacketHandler[PKT_S_CHANGESTAT] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_CHANGESTAT>(Handle_S_CHANGESTAT, session, buffer, len); };
		GPacketHandler[PKT_S_PING] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::S_PING>(Handle_S_PING, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::C_MOVE& pkt) { return MakeSendBuffer(pkt, PKT_C_MOVE); }
	static SendBufferRef MakeSendBuffer(Protocol::C_SKILL& pkt) { return MakeSendBuffer(pkt, PKT_C_SKILL); }
	static SendBufferRef MakeSendBuffer(Protocol::C_LOGIN& pkt) { return MakeSendBuffer(pkt, PKT_C_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::C_CREATEPLAYER& pkt) { return MakeSendBuffer(pkt, PKT_C_CREATEPLAYER); }
	static SendBufferRef MakeSendBuffer(Protocol::C_ENTERGAME& pkt) { return MakeSendBuffer(pkt, PKT_C_ENTERGAME); }
	static SendBufferRef MakeSendBuffer(Protocol::C_EQUIPITEM& pkt) { return MakeSendBuffer(pkt, PKT_C_EQUIPITEM); }
	static SendBufferRef MakeSendBuffer(Protocol::C_PONG& pkt) { return MakeSendBuffer(pkt, PKT_C_PONG); }

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