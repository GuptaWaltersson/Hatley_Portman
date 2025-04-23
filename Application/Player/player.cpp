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


void player::updatePlayer(float deltaTime)
{
	if (IsKeyPressed(KEY_LEFT)) this->position.x -= this->m_movementSpeed ;
	if (IsKeyPressed(KEY_RIGHT)) this->position.x += this->m_movementSpeed ;

}
