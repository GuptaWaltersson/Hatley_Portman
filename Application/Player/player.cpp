#include "player.h"

float player::getSpeed()
{
	return this->m_movementSpeed;
}

void player::setSpeed(float speed) 
{
	this->m_movementSpeed = speed;
}

std::string player::getTextureName()
{
	return this->m_texture;
}

void player::setTextureName(std::string textureName)
{
	this->m_texture = textureName;
}
