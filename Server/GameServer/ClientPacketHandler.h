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
	PKT_C_CreatePlayer = 1013,
	PKT_S_CreatePlayer = 1014,
	PKT_C_EnterGame = 1015,
	PKT_S_ItemList = 1016,
	PKT_S_AddItem = 1017,
	PKT_C_EquipItem = 1018,
	PKT_S_EquipItem = 1019,
	PKT_S_ChangeStat = 1020,
	PKT_S_Ping = 1021,
	PKT_C_Pong = 1022,
};

// Custom Handlers
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_Move(PacketSessionRef& session, Protocol::C_Move& pkt);
bool Handle_C_Skill(PacketSessionRef& session, Protocol::C_Skill& pkt);
bool Handle_C_Login(PacketSessionRef& session, Protocol::C_Login& pkt);
bool Handle_C_CreatePlayer(PacketSessionRef& session, Protocol::C_CreatePlayer& pkt);
bool Handle_C_EnterGame(PacketSessionRef& session, Protocol::C_EnterGame& pkt);
bool Handle_C_EquipItem(PacketSessionRef& session, Protocol::C_EquipItem& pkt);
bool Handle_C_Pong(PacketSessionRef& session, Protocol::C_Pong& pkt);

class ClientPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
		GPacketHandler[PKT_C_Move] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_Move>(Handle_C_Move, session, buffer, len); };
		GPacketHandler[PKT_C_Skill] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_Skill>(Handle_C_Skill, session, buffer, len); };
		GPacketHandler[PKT_C_Login] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_Login>(Handle_C_Login, session, buffer, len); };
		GPacketHandler[PKT_C_CreatePlayer] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_CreatePlayer>(Handle_C_CreatePlayer, session, buffer, len); };
		GPacketHandler[PKT_C_EnterGame] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_EnterGame>(Handle_C_EnterGame, session, buffer, len); };
		GPacketHandler[PKT_C_EquipItem] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_EquipItem>(Handle_C_EquipItem, session, buffer, len); };
		GPacketHandler[PKT_C_Pong] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_Pong>(Handle_C_Pong, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::S_EnterGame& pkt) { return MakeSendBuffer(pkt, PKT_S_EnterGame); }
	static SendBufferRef MakeSendBuffer(Protocol::S_LeaveGame& pkt) { return MakeSendBuffer(pkt, PKT_S_LeaveGame); }
	static SendBufferRef MakeSendBuffer(Protocol::S_Spawn& pkt) { return MakeSendBuffer(pkt, PKT_S_Spawn); }
	static SendBufferRef MakeSendBuffer(Protocol::S_Despawn& pkt) { return MakeSendBuffer(pkt, PKT_S_Despawn); }
	static SendBufferRef MakeSendBuffer(Protocol::S_Move& pkt) { return MakeSendBuffer(pkt, PKT_S_Move); }
	static SendBufferRef MakeSendBuffer(Protocol::S_Skill& pkt) { return MakeSendBuffer(pkt, PKT_S_Skill); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ChangeHp& pkt) { return MakeSendBuffer(pkt, PKT_S_ChangeHp); }
	static SendBufferRef MakeSendBuffer(Protocol::S_Die& pkt) { return MakeSendBuffer(pkt, PKT_S_Die); }
	static SendBufferRef MakeSendBuffer(Protocol::S_Connected& pkt) { return MakeSendBuffer(pkt, PKT_S_Connected); }
	static SendBufferRef MakeSendBuffer(Protocol::S_Login& pkt) { return MakeSendBuffer(pkt, PKT_S_Login); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CreatePlayer& pkt) { return MakeSendBuffer(pkt, PKT_S_CreatePlayer); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ItemList& pkt) { return MakeSendBuffer(pkt, PKT_S_ItemList); }
	static SendBufferRef MakeSendBuffer(Protocol::S_AddItem& pkt) { return MakeSendBuffer(pkt, PKT_S_AddItem); }
	static SendBufferRef MakeSendBuffer(Protocol::S_EquipItem& pkt) { return MakeSendBuffer(pkt, PKT_S_EquipItem); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ChangeStat& pkt) { return MakeSendBuffer(pkt, PKT_S_ChangeStat); }
	static SendBufferRef MakeSendBuffer(Protocol::S_Ping& pkt) { return MakeSendBuffer(pkt, PKT_S_Ping); }

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