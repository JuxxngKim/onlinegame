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
		if (packet?.Player == null)
			return;

		Managers.Object.Add(packet.Player, myPlayer: true);
	}

	public static void S_LeaveGameHandler(PacketSession session, IMessage message)
	{
		S_LeaveGame packet = message as S_LeaveGame;
		if (packet == null)
			return;
	}

	public static void S_SpawnHandler(PacketSession session, IMessage message)
	{
		S_Spawn spawn = message as S_Spawn;
		if (spawn?.Objects == null || spawn.Objects.Count <= 0)
			return;
		
		foreach (ObjectInfo obj in spawn.Objects)
		{
			Managers.Object.Add(obj, myPlayer: false);
		}
	}

	public static void S_DespawnHandler(PacketSession session, IMessage message)
	{
		S_Despawn despawnPacket = message as S_Despawn;
		foreach (int id in despawnPacket.ObjectIds)
			Managers.Object.Remove(id);
	}

	public static void S_MoveHandler(PacketSession session, IMessage message)
	{
		S_Move packet = message as S_Move;
		if (packet == null)
			return;

		GameObject go = Managers.Object.FindById(packet.ObjectId);
		if (go == null)
			return;

		if (Managers.Object.MyPlayer.Id == packet.ObjectId)
			return;

		BaseController bc = go.GetComponent<BaseController>();
		if (bc == null)
			return;

		bc.PosInfo = packet.PosInfo;
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

		if (packet.LoginOk != 1)
		{
			Debug.LogError($"LoginError : {packet.LoginOk}");
			return;
		}
		
		Managers.Scene.LoadScene(Define.Scene.Game);
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
	
	public static void S_ChatHandler(PacketSession session, IMessage message)
	{
		S_Chat packet = message as S_Chat;
		if (packet == null)
			return;
	}
	
	public static void S_CreateAccountHandler(PacketSession session, IMessage message)
	{
		S_CreateAccount packet = message as S_CreateAccount;
		if (packet == null)
			return;
		
		
	}
}