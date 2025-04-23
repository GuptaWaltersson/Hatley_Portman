#pragma once
#include <string>
#include "raylib.h"
#include <raymath.h>

class player {
public:
	float getSpeed() ;
	void setSpeed(float speed);
	std::string getTextureName();
	void setTextureName(std::string textureName);

	Vector2 getPositon() { return this->position; };

	void updatePlayer(float deltaTime);
private:

	float m_movementSpeed = 1000.0f;
	std::string m_texture = "../Textures/Portman_v1.png"; // Filepath
	std::string m_name;
	Vector2 position = { 850,400 };
	
};

