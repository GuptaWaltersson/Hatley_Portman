#pragma once

#include <raylib.h>

struct Tag
{
	std::string name;
};

struct Position
{
	float x;
	float y;
};

struct BBox
{
	float width;
	float height;
};

struct Movement
{
	float dx;
	float dy;
	float ax;
	float ay;
	bool canJump;
};

struct Gravity
{
	float acceleration = 9.8;
};

struct Sprite
{
	Texture2D texture;
	std::string texturePath;
	int scale = 4;

	Sprite(const std::string& path)
		: texture(LoadTexture(path.c_str())), texturePath(path) {
	}
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

struct PlayerTag {
	bool isPlayer = true;
};

struct HatTag {
	// On Head = 0
	// Default = 1
	// Magic = 2
	//Legendary = 3
	int hatType;
};

struct LastMove {
	std::string lastKey;

};