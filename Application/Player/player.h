#pragma once
#include <string>
#include <raymath.h>
class player {
public:
	float getSpeed() ;
	void setSpeed(float speed);
	std::string getTextureName();
	void setTextureName(std::string textureName);
private:

	float m_movementSpeed = 0.0f;
	std::string m_texture; // Filepath
	std::string m_name; //behövs nog inte men jag vne
	Vector2 position;
	
};

