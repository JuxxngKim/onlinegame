using Google.Protobuf;
using Protocol;
using ServerCore;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

class PacketHandler
{

	public static void S_EnterGameHandler(PacketSession session, IMessage message)
	{
		S_EnterGame packet = message as S_EnterGame;
		if (packet == null)
			return;
	}

	public static void S_LeaveGameHandler(PacketSession session, IMessage message)
	{
		S_LeaveGame packet = message as S_LeaveGame;
		if (packet == null)
			return;
	}

	public static void S_SpawnHandler(PacketSession session, IMessage message)
	{
		S_Spawn packet = message as S_Spawn;
		if (packet == null)
			return;
	}

	public static void S_DespawnHandler(PacketSession session, IMessage message)
	{
		S_Despawn packet = message as S_Despawn;
		if (packet == null)
			return;
	}

	public static void S_MoveHandler(PacketSession session, IMessage message)
	{
		S_Move packet = message as S_Move;
		if (packet == null)
			return;
	}

	public static void S_SkillHandler(PacketSession session, IMessage message)
	{
		S_Skill packet = message as S_Skill;
		if (packet == null)
			return;
	}

	public static void S_ChangeHpHandler(PacketSession session, IMessage message)
	{
		S_ChangeHp packet = message as S_ChangeHp;
		if (packet == null)
			return;
	}

	public static void S_DieHandler(PacketSession session, IMessage message)
	{
		S_Die packet = message as S_Die;
		if (packet == null)
			return;
	}

	public static void S_ConnectedHandler(PacketSession session, IMessage message)
	{
		S_Connected packet = message as S_Connected;
		if (packet == null)
			return;
	}

	public static void S_LoginHandler(PacketSession session, IMessage message)
	{
		S_Login packet = message as S_Login;
		if (packet == null)
			return;
	}

	public static void S_CreatePlayerHandler(PacketSession session, IMessage message)
	{
		S_CreatePlayer packet = message as S_CreatePlayer;
		if (packet == null)
			return;
	}

	public static void S_ItemListHandler(PacketSession session, IMessage message)
	{
		S_ItemList packet = message as S_ItemList;
		if (packet == null)
			return;
	}

	public static void S_AddItemHandler(PacketSession session, IMessage message)
	{
		S_AddItem packet = message as S_AddItem;
		if (packet == null)
			return;
	}

	public static void S_EquipItemHandler(PacketSession session, IMessage message)
	{
		S_EquipItem packet = message as S_EquipItem;
		if (packet == null)
			return;
	}

	public static void S_ChangeStatHandler(PacketSession session, IMessage message)
	{
		S_ChangeStat packet = message as S_ChangeStat;
		if (packet == null)
			return;
	}

	public static void S_PingHandler(PacketSession session, IMessage message)
	{
		S_Ping packet = message as S_Ping;
		if (packet == null)
			return;
	}
}