#pragma once

#include <SFML\Graphics.hpp>

class Solid
{
private:
	//Vars.
	sf::RectangleShape body;
	bool canDelete = false;

	void _InitVars();
	void _InitBody(float width, float height);

public:
	Solid(float x, float y, float width, float height);
	~Solid();

	//Getters
	sf::RectangleShape GetBody();
	bool GetCanDelete();

	//Setters
	void SetPosition(float x, float y);
	void SetSize(float width, float height);

	void Update(sf::View view);
	void Render(sf::RenderTarget* rt);
};

