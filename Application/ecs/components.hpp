#pragma once

#include <raylib.h>

struct Position
{
	float x;
	float y;
};

struct HitBox
{
	float length_x;
	float length_y;
	Position Origin;
};

struct velocity
{
	float dx;
	float dy;
};

struct Gravity
{
	float acceleration = 9.8;
};

struct Sprite
{
	Texture2D texture;
};

struct Health
{
	float value;
};

struct Poison
{
	float tickDamage;
};

struct Behaviour
{
	char ScriptPath[64];
	int LuaTableRef;

	Behaviour(const char* path, int luaRef) : LuaTableRef(luaRef)
	{
		memset(ScriptPath, '\0', sizeof(ScriptPath));
		strcpy_s(ScriptPath, path);
	}
};

struct PLayerTag {};