using Google.Protobuf;
using Protocol;
using ServerCore;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

class PacketHandler
{
{%-for pkt in parser.recv_pkt%}

	public static void {{pkt.name}}Handler(PacketSession session, IMessage message)
	{
		{{pkt.name}} packet = message as {{pkt.name}};
		if (packet == null)
			return;
	}

{%-endfor%}
}