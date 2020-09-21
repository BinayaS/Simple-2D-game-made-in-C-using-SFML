#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "Player.h"
#include "Solid.h"

/*
	The Main Object that holds game information
*/

class Game
{
private:
	//Vars.
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::View view;
	bool restart;
	Player* player;
	std::vector<Solid> solidArray;
	sf::Font font;
	sf::Text currentScore;
	sf::Text info;
	int maxSolids;
	int solidsLimit;
	int timer;
	int boostTimer;
	int timerNextBoost;
	int levelSpdIncrease;
	int maxSolidsNumIncrease;

	std::string infoString;

	sf::Color c_Green;
	sf::Color c_Gray;
	sf::Color c_Red;
	sf::Color c_Blue;
	sf::Color c_Yellow;
	sf::Color c_Lime;
	sf::Color c_Orchid;
	sf::Color c_Silver;
	sf::Color c_DeepSkyBlue;
	sf::Color c_AquaMarine;
	
	bool menuScreen;
	bool gameOver;

	float levelSpd;

	//Functions
	void _InitVars();
	void _InitWindow();
	void _Restart();
	void _CreateStartArea();
	void _SetMenuText();

public:
	//Constructor and Destructor
	Game();
	~Game();

	//Getters
	bool GetWindowIsOpen();
	bool GetMenuScreen();

	//Setters
	void SetMenuScreen(bool newValue);

	//Functions
	void Update();
	void Render();
	void PollEvent();

};

