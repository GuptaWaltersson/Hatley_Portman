#include <raylib.h>

struct Position
{
	float x;
	float y;
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