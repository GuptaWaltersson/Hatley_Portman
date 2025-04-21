#pragma once
#include <string>
class player {
public:
	float m_movementSpeed = 0.0f;
	std::string m_texture;
	std::string m_name;

	float getSpeed() const;
};

