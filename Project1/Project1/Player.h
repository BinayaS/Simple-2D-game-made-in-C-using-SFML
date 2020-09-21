#pragma once

#include "Solid.h"
#include "EntityHelper.h"

#include <SFML\Graphics.hpp>
#include <algorithm>

class Player: public EntityHelper
{
private:
	//Keys
	bool leftKey;
	bool rightKey;
	bool jumpKey;

	//Vars.
	bool onGround;
	float horizontal;
	float hspd;
	float vspd;
	float moveSpd;
	float defaultMoveSpd;
	float grav;
	float jumpPower;
	sf::RectangleShape body;

	float maxFallSpd;
	float maxJetSpeed;

	float frict;
	float accel;
	float weight;
	float jetPower;

	enum class verticalState {
		grounded,
		jumping,
		jetpacking,
		falling
	};

	verticalState vertState;
	bool isDead;

	//Functions
	void _InitVars();
	void _InitBody(float width, float height);
	void _MovePlayer(std::vector<Solid> solidArray, float windownWidth, float windowHeight, sf::View view);
	void _GetKeyboardInputs();

public:
	Player(float x, float y, float width, float height);
	~Player();

	//Getters
	bool GetIsDead();
	float GetMoveSpd();
	float GetDefaultMoveSpd();

	//Setters
	void SetMoveSpd(float newMoveSpd);
	void SetPosition(float x, float y);
	void SetIsDead(bool isDead);

	void Update(std::vector<Solid> solidArray, float windownWidth, float windowHeight, bool& menuStart, sf::View view);
	void Render(sf::RenderTarget* rt);
};

