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
bool Handle_C_MOVE(PacketSessionRef& session, Protocol::C_MOVE& pkt);
bool Handle_C_SKILL(PacketSessionRef& session, Protocol::C_SKILL& pkt);
bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt);
bool Handle_C_CREATEPLAYER(PacketSessionRef& session, Protocol::C_CREATEPLAYER& pkt);
bool Handle_C_ENTERGAME(PacketSessionRef& session, Protocol::C_ENTERGAME& pkt);
bool Handle_C_EQUIPITEM(PacketSessionRef& session, Protocol::C_EQUIPITEM& pkt);
bool Handle_C_PONG(PacketSessionRef& session, Protocol::C_PONG& pkt);

class ClientPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
		GPacketHandler[PKT_C_MOVE] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_MOVE>(Handle_C_MOVE, session, buffer, len); };
		GPacketHandler[PKT_C_SKILL] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_SKILL>(Handle_C_SKILL, session, buffer, len); };
		GPacketHandler[PKT_C_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_LOGIN>(Handle_C_LOGIN, session, buffer, len); };
		GPacketHandler[PKT_C_CREATEPLAYER] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_CREATEPLAYER>(Handle_C_CREATEPLAYER, session, buffer, len); };
		GPacketHandler[PKT_C_ENTERGAME] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ENTERGAME>(Handle_C_ENTERGAME, session, buffer, len); };
		GPacketHandler[PKT_C_EQUIPITEM] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_EQUIPITEM>(Handle_C_EQUIPITEM, session, buffer, len); };
		GPacketHandler[PKT_C_PONG] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_PONG>(Handle_C_PONG, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::S_ENTERGAME& pkt) { return MakeSendBuffer(pkt, PKT_S_ENTERGAME); }
	static SendBufferRef MakeSendBuffer(Protocol::S_LEAVEGAME& pkt) { return MakeSendBuffer(pkt, PKT_S_LEAVEGAME); }
	static SendBufferRef MakeSendBuffer(Protocol::S_SPAWN& pkt) { return MakeSendBuffer(pkt, PKT_S_SPAWN); }
	static SendBufferRef MakeSendBuffer(Protocol::S_DESPAWN& pkt) { return MakeSendBuffer(pkt, PKT_S_DESPAWN); }
	static SendBufferRef MakeSendBuffer(Protocol::S_MOVE& pkt) { return MakeSendBuffer(pkt, PKT_S_MOVE); }
	static SendBufferRef MakeSendBuffer(Protocol::S_SKILL& pkt) { return MakeSendBuffer(pkt, PKT_S_SKILL); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CHANGEHP& pkt) { return MakeSendBuffer(pkt, PKT_S_CHANGEHP); }
	static SendBufferRef MakeSendBuffer(Protocol::S_DIE& pkt) { return MakeSendBuffer(pkt, PKT_S_DIE); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CONNECTED& pkt) { return MakeSendBuffer(pkt, PKT_S_CONNECTED); }
	static SendBufferRef MakeSendBuffer(Protocol::S_LOGIN& pkt) { return MakeSendBuffer(pkt, PKT_S_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CREATEPLAYER& pkt) { return MakeSendBuffer(pkt, PKT_S_CREATEPLAYER); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ITEMLIST& pkt) { return MakeSendBuffer(pkt, PKT_S_ITEMLIST); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ADDITEM& pkt) { return MakeSendBuffer(pkt, PKT_S_ADDITEM); }
	static SendBufferRef MakeSendBuffer(Protocol::S_EQUIPITEM& pkt) { return MakeSendBuffer(pkt, PKT_S_EQUIPITEM); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CHANGESTAT& pkt) { return MakeSendBuffer(pkt, PKT_S_CHANGESTAT); }
	static SendBufferRef MakeSendBuffer(Protocol::S_PING& pkt) { return MakeSendBuffer(pkt, PKT_S_PING); }

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