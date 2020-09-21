#include "Solid.h"

/*----Constructor_and_Destructor----*/
Solid::Solid(float x, float y, float width, float height)
{
	body.setPosition(x, y);

	_InitVars();
	_InitBody(width, height);
}

Solid::~Solid()
{

}

sf::RectangleShape Solid::GetBody()
{
	return body;
}

/*----Private_Functions----*/
void Solid::_InitVars()
{

}

void Solid::_InitBody(float width, float height)
{
	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(width, height));
}

/*----Public_Functions----*/
void Solid::Update(sf::View view)
{
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();
	if (body.getPosition().x + body.getGlobalBounds().width < center.x - size.x / 2) {
		canDelete = true;
	}
}

void Solid::Render(sf::RenderTarget* rt)
{
	rt->draw(body);
}

bool Solid::GetCanDelete()
{
	return canDelete;
}

void Solid::SetPosition(float x, float y)
{
	body.setPosition(x, y);
}

void Solid::SetSize(float width, float height)
{
	body.setSize(sf::Vector2f(width, height));
}
