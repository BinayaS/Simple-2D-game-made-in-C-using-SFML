#include "Player.h"

/*----Constructor_and_Destructor----*/
Player::Player(float x, float y, float width, float height)
{
	//Set start position
	body.setPosition(x, y);

	//Setup
	_InitVars();
	_InitBody(width, height);
}

Player::~Player()
{

}

/*----Private_Functions----*/
void Player::_InitVars()
{
	hspd = 0;
	vspd = 0;

	maxFallSpd = 14;
	maxJetSpeed = 6;

	frict = 0.4;
	accel = 0.8;
	grav = 0.5;
	weight = 0.5;

	jetPower = 1;
	jumpPower = 12;
	defaultMoveSpd = 10;
	moveSpd = defaultMoveSpd;

	vertState = verticalState::falling;
	isDead = false;
}

void Player::_InitBody(float width, float height)
{
	body.setFillColor(sf::Color::Green);
	body.setSize(sf::Vector2f(width, height));
}

void Player::_MovePlayer(std::vector<Solid> solidArray, float windownWidth, float windowHeight, sf::View view)
{
	//Set hspd
	horizontal = rightKey - leftKey;
	if (horizontal > 0) {
		if (hspd < moveSpd) {
			hspd += accel;
		} else {
			hspd = moveSpd;
		}
	}
	else if (horizontal < 0) {
		if (hspd > -moveSpd) {
			hspd -= accel;
		}
		else {
			hspd = -moveSpd;
		}
	}
	else {
		if (hspd > 0.1) {
			hspd -= frict;
		}
		else if(hspd < -0.1) {
			hspd += frict;
		}
		else {
			hspd = 0;
		}
	}

	//Set vspd
	switch (vertState)
	{
	case verticalState::grounded:
		if (!PlaceMeeting(
			body.getPosition().x, 
			body.getPosition().y + 1, 
			body.getGlobalBounds().width, 
			body.getGlobalBounds().height, 
			solidArray)) 
		{
			vertState = verticalState::falling;
		}

		if (jumpKey) {
			vspd -= jumpPower;
			vertState = verticalState::jumping;
		}
	break;

	case verticalState::jumping:
		if (vspd >= 0) {
			vertState = verticalState::falling;
		}
	break;
	
	case verticalState::jetpacking:
		if (vspd > -maxJetSpeed && !PlaceMeeting(
			body.getPosition().x, 
			body.getPosition().y + 1, 
			body.getGlobalBounds().width, 
			body.getGlobalBounds().height, 
			solidArray)) 
		{
			vspd -= jetPower + weight + std::max(0.0f, abs(vspd) / 20);
		}

		if (!jumpKey) {
			vertState = verticalState::falling;
		}
	break;
	
	case verticalState::falling:
		if (PlaceMeeting(
			body.getPosition().x, 
			body.getPosition().y + 1, 
			body.getGlobalBounds().width, 
			body.getGlobalBounds().height, 
			solidArray)) 
		{
			vertState = verticalState::grounded;
		}

		if (jumpKey) {
			vertState = verticalState::jetpacking;
		}
	break;
	}

	//Gravity
	if (vertState != verticalState::grounded) {
		if (vspd < maxFallSpd) {
			vspd += grav;
		}
	}

	//Collision
	//Horizontal
	if (PlaceMeeting(body.getPosition().x + hspd, body.getPosition().y, body.getGlobalBounds().width, body.getGlobalBounds().height, solidArray)) {
		while (!PlaceMeeting(body.getPosition().x + sign(hspd), body.getPosition().y, body.getGlobalBounds().width, body.getGlobalBounds().height, solidArray)) {
			body.move(sign(hspd), 0);
		}
		hspd = 0;
	}
	//Vertical
	if (PlaceMeeting(body.getPosition().x, body.getPosition().y + vspd, body.getGlobalBounds().width, body.getGlobalBounds().height, solidArray)) {
		while (!PlaceMeeting(body.getPosition().x, body.getPosition().y + sign(vspd), body.getGlobalBounds().width, body.getGlobalBounds().height, solidArray)) {
			body.move(0, sign(vspd));
		}
		vspd = 0;
	}

	//Move
	if (!isDead) {
		body.move(hspd, vspd);
	}

	//Dead check
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();

	if (body.getPosition().x + body.getGlobalBounds().width < center.x - size.x/2) {
		isDead = true;
	}
	if (body.getPosition().x > center.x + size.x/2) {
		isDead = true;
	}
	if (body.getPosition().y + body.getGlobalBounds().height < center.y - size.y/2) {
		isDead = true;
	}
	if (body.getPosition().y > center.y + size.y/2) {
		isDead = true;
	}
}

void Player::_GetKeyboardInputs()
{
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		leftKey = true;
	}
	else {
		leftKey = false;
	}

	//Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		rightKey = true;
	}
	else {
		rightKey = false;
	}

	//Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		jumpKey = true;
	}
	else {
		jumpKey = false;
	}
}

/*----Public_Functions----*/
void Player::Update(std::vector<Solid> solidArray, float windownWidth, float windowHeight, bool& menuScreen, sf::View view)
{
	_GetKeyboardInputs();

	//Start game
	if (!isDead && menuScreen && (leftKey || rightKey)) {
		menuScreen = false;
	}

	_MovePlayer(solidArray, windownWidth, windowHeight, view);
}

void Player::Render(sf::RenderTarget* rt)
{
	rt->draw(body);
}

void Player::SetMoveSpd(float newMoveSpd) {
	moveSpd = newMoveSpd;
}

void Player::SetPosition(float x, float y)
{
	body.setPosition(x, y);
}

void Player::SetIsDead(bool isDead)
{
	this->isDead = isDead;
}

bool Player::GetIsDead()
{
	return isDead;
}

float Player::GetMoveSpd()
{
	return moveSpd;
}

float Player::GetDefaultMoveSpd()
{
	return defaultMoveSpd;
}
