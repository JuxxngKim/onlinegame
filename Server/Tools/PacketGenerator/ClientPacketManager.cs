using Google.Protobuf;
using Protocol;
using ServerCore;
using System;
using System.Collections.Generic;

class PacketManager
{
    public enum MsgId
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
    }

	#region Singleton
	static PacketManager _instance = new PacketManager();
    public static PacketManager Instance { get { return _instance; } }
#endregion

	Dictionary<ushort, Action<PacketSession, ArraySegment<byte>, ushort>> _onRecv = new Dictionary<ushort, Action<PacketSession, ArraySegment<byte>, ushort>>();
	Dictionary<ushort, Action<PacketSession, IMessage>> _handler = new Dictionary<ushort, Action<PacketSession, IMessage>>();

	public Action<PacketSession, IMessage, ushort> CustomHandler { get; set; }

	PacketManager()
	{
		Register();
	}

	public void Register()
	{
		_onRecv.Add((ushort)MsgId.PKT_C_Move, MakePacket<C_Move>);
		_handler.Add((ushort)MsgId.PKT_C_Move, PacketHandler.C_MoveHandler);
		_onRecv.Add((ushort)MsgId.PKT_C_Skill, MakePacket<C_Skill>);
		_handler.Add((ushort)MsgId.PKT_C_Skill, PacketHandler.C_SkillHandler);
		_onRecv.Add((ushort)MsgId.PKT_C_Login, MakePacket<C_Login>);
		_handler.Add((ushort)MsgId.PKT_C_Login, PacketHandler.C_LoginHandler);
		_onRecv.Add((ushort)MsgId.PKT_C_CreatePlayer, MakePacket<C_CreatePlayer>);
		_handler.Add((ushort)MsgId.PKT_C_CreatePlayer, PacketHandler.C_CreatePlayerHandler);
		_onRecv.Add((ushort)MsgId.PKT_C_EnterGame, MakePacket<C_EnterGame>);
		_handler.Add((ushort)MsgId.PKT_C_EnterGame, PacketHandler.C_EnterGameHandler);
		_onRecv.Add((ushort)MsgId.PKT_C_EquipItem, MakePacket<C_EquipItem>);
		_handler.Add((ushort)MsgId.PKT_C_EquipItem, PacketHandler.C_EquipItemHandler);
		_onRecv.Add((ushort)MsgId.PKT_C_Pong, MakePacket<C_Pong>);
		_handler.Add((ushort)MsgId.PKT_C_Pong, PacketHandler.C_PongHandler);
	}

	public void OnRecvPacket(PacketSession session, ArraySegment<byte> buffer)
	{
		ushort count = 0;

		ushort size = BitConverter.ToUInt16(buffer.Array, buffer.Offset);
		count += 2;
		ushort id = BitConverter.ToUInt16(buffer.Array, buffer.Offset + count);
		count += 2;

		Action<PacketSession, ArraySegment<byte>, ushort> action = null;
		if (_onRecv.TryGetValue(id, out action))
			action.Invoke(session, buffer, id);
	}

	void MakePacket<T>(PacketSession session, ArraySegment<byte> buffer, ushort id) where T : IMessage, new()
	{
		T pkt = new T();
		pkt.MergeFrom(buffer.Array, buffer.Offset + 4, buffer.Count - 4);

		if (CustomHandler != null)
		{
			CustomHandler.Invoke(session, pkt, id);
		}
		else
		{
			Action<PacketSession, IMessage> action = null;
			if (_handler.TryGetValue(id, out action))
				action.Invoke(session, pkt);
		}
	}

	public Action<PacketSession, IMessage> GetPacketHandler(ushort id)
	{
		Action<PacketSession, IMessage> action = null;
		if (_handler.TryGetValue(id, out action))
			return action;
		return null;
	}
}