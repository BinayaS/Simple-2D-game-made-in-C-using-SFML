#pragma once

#include "Solid.h"

#include <vector>
#include <SFML\Window\Keyboard.hpp>

class EntityHelper
{
public:
	bool PlaceMeeting(float x, float y, float width, float height, std::vector<Solid> solidArray);

	float sign(float x);
};