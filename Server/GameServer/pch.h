#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

#include "CorePch.h"
#include "Enum.pb.h"
#include "GameTypes.h"
#include "Struct.pb.h"

struct Vector2Int
{
public:
	Vector2Int(int32 x, int32 y) { Y = y; X = x; }
	Vector2Int(Protocol::PositionInfo posInfo) { Y = posInfo.posy(); X = posInfo.posx(); }

	static Vector2Int up;
	static Vector2Int down;
	static Vector2Int left;
	static Vector2Int right;

public:
	friend Vector2Int operator+(const Vector2Int& a, const Vector2Int& b)
	{
		return Vector2Int(a.X + b.X, a.Y + b.Y);
	}

	friend Vector2Int operator-(const Vector2Int& a, const Vector2Int& b)
	{
		return Vector2Int(a.X - b.X, a.Y - b.Y);
	}

public:
	int32 Y;
	int32 X;
};