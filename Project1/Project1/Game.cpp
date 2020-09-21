#include "Game.h"

/*----Constructor_and_Destructor----*/
Game::Game()
{
    //Setup
    _InitVars();
	_InitWindow();

    //Create player
    player = new Player(videoMode.width / 2.f, videoMode.height / 2.f, 16, 16);

    //Create start area
    _CreateStartArea();

    
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        // error...
        printf("FAIL!");
    }
    
    _SetMenuText();
}

Game::~Game()
{
	delete window;
}

/*----Private_Functions----*/
void Game::_InitVars()
{
	window = nullptr;
    restart = false;
    gameOver = false;
    menuScreen = true;

    levelSpd = 0;
    maxSolids = 15;
    solidsLimit = 40;
    timer = 0;
    timerNextBoost = 10*60;
    boostTimer = timerNextBoost;
    levelSpdIncrease = 2;
    maxSolidsNumIncrease = 5;

    infoString = "<-- A key \n--> D key \n^ Space key \n\n*Hold Space to float* \n\n\n                                       Move to Start";

    c_Green = sf::Color(0, 255, 0);
    c_Gray = sf::Color(170, 170, 170);
    c_Red = sf::Color(255, 50, 50);
    c_Blue = sf::Color(0, 0, 255);
    c_Yellow = sf::Color(255, 255, 0);
    c_Lime = sf::Color(0, 255, 0);
    c_Orchid = sf::Color(218, 112, 214);
    c_Silver = sf::Color(192, 192, 192);
    c_DeepSkyBlue = sf::Color(0, 191, 255);
    c_AquaMarine = sf::Color(127, 255, 212);
}

void Game::_InitWindow()
{
	videoMode.height = 1080;
	videoMode.width = 1920;
    videoMode.getDesktopMode();

    view.setSize(videoMode.width, videoMode.height);
    view.setCenter(videoMode.width / 2, videoMode.height / 2);

	window = new sf::RenderWindow(videoMode, "Simple Platformer", sf::Style::None);
	window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setView(view);
}

void Game::_Restart() {
    solidArray.clear();
    _SetMenuText();

    view.reset(sf::FloatRect(0, 0, videoMode.width, videoMode.height));
    view.setCenter(videoMode.width / 2, videoMode.height / 2);

    _CreateStartArea();

    player->SetPosition(videoMode.width / 2, videoMode.height / 2);
    player->SetIsDead(false);
    player->SetMoveSpd(player->GetDefaultMoveSpd());

    timer = 0;
    restart = false;
    gameOver = false;
    menuScreen = true;
    levelSpd = 0;
    boostTimer = timerNextBoost;
}

void Game::_CreateStartArea()
{
    Solid bottomStart(0, videoMode.height - 32, videoMode.width, 32);
    Solid leftStart(0, 0, 32, videoMode.height);
    Solid topStart(0, 0, videoMode.width, 32);
    solidArray.push_back(bottomStart);
    solidArray.push_back(leftStart);
    solidArray.push_back(topStart);
}

void Game::_SetMenuText()
{
    currentScore.setFont(font);
    currentScore.setCharacterSize(100);
    currentScore.setFillColor(c_Green);
    currentScore.setPosition(200.0f, 160.0f);
    currentScore.setString("Run Cube RUN!!");

    info.setFont(font);
    info.setCharacterSize(30);
    info.setFillColor(c_Green);
    info.setPosition(200.0f, 280.0f);
    info.setString(infoString);
}

/*----Public_Functions----*/
void Game::Update()
{
    if (restart) {
        _Restart();
    }

    float rightEdge = view.getCenter().x + view.getSize().x/2;
    
    //If running
    if (!menuScreen) {
        timer++;
        boostTimer++;
        //Random Solid Generation
        if (solidArray.size() < maxSolids) {
            Solid newSolid(rand() % 1000 + rightEdge, rand() % videoMode.height-200 + 100, rand() % 128 + 32, rand() % 128 + 32);
            solidArray.push_back(newSolid);
        }
        if (boostTimer > timerNextBoost) {
            if (levelSpd == 0) {
                levelSpd = 1;
            }
            levelSpd += levelSpdIncrease;
            boostTimer = 0;
            maxSolids += maxSolidsNumIncrease;
            if (maxSolids > solidsLimit) {
                maxSolids = solidsLimit;
            }
            player->SetMoveSpd(player->GetMoveSpd() + levelSpd);
        }

        //Set score text
        currentScore.setCharacterSize(50);
        currentScore.setPosition(view.getCenter().x - 10, 100);
        currentScore.setFillColor(c_AquaMarine);
        currentScore.setString("Score: " + std::to_string(timer / 60));
    }
    
    //If player not dead
    if (!player->GetIsDead()) {

        //Move view
        view.move(levelSpd, 0.0f);
        window->setView(view);
        
    }

    if(player->GetIsDead() && !menuScreen) {
        menuScreen = true;
        info.setPosition(view.getCenter().x - 10, 500);
        info.setString("Game Over!");
    }

    //Update solids
    for (int i = 0; i < solidArray.size(); i++) {
        solidArray[i].Update(view);
        if (solidArray[i].GetCanDelete()) {
            solidArray.erase(solidArray.begin() + i);
        }
    }

    //Update Player
    player->Update(solidArray, videoMode.width, videoMode.height, menuScreen, view);

    //Check for window close
    PollEvent();
}

void Game::Render()
{
    //Clear
    window->clear(sf::Color(0, 0, 0));

    /*----Draw_The_Game----*/
    {
        //Draw Solids
        for (int i = 0; i < solidArray.size(); i++) {
            solidArray[i].Render(window);
        }

        //Draw Player
        player->Render(window);

        //Draw Score and other text
        window->draw(currentScore);
        if (menuScreen) {
            window->draw(info);
        }
    }
    /*----Draw_The_Game----*/

    //Display
    window->display();
}

void Game::PollEvent()
{
    while (window->pollEvent(event))
    {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                window->close();
            }
            if (event.key.code == sf::Keyboard::R) {
                restart = true;
            }
            break;
        }
    }
}

bool Game::GetWindowIsOpen()
{
	return window->isOpen();
}

bool Game::GetMenuScreen()
{
    return menuScreen;
}

void Game::SetMenuScreen(bool newValue)
{
    menuScreen = newValue;
}
