#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>
#include <memory>
#include "cDummy.h"
#include "cDebris.h"
#include "cMissile.h"
#include "cActor.h"
#include "cTeam.h"

#define MAX_NUMBER_OF_ITEMS 3

using namespace sf;

//This is the main gem class
class Game {
public:
	
	Game(int mapType, int nUnitsInTeam);

	void run();

	//MENU

	void Menu_run();
	void Menu_draw();


	void MoveUp();
	void MoveDown();

	void Options_draw();
	void OptionsRun(RectangleShape& OptionsBackground);
	void OptionsMoveUp();
	void OptionsMoveDown();

	void MenuPause_draw();
	void MenuPauseRun();
	void MenuPauseMoveUp();
	void MenuPauseMoveDown();

	void GameOverMenuRun();
	void GameOverMenuDraw();


	int GetPressedItem() {
		return selectedItemIndex;
	}

	int GetPressedItemMenuPause() {
		return selectedItemPasueIndex;
	}
	bool isPaused;

private:

	Texture aimTexture;
	Sprite aimSprite;



	RenderWindow window;
	View view;  //camera
	Clock clock;

	float deltaTime;

	// min and max zoom are for 4500 map width & 2300 map height and 1920x1080 resolution
	const float minZoom = 1.0f;
	const float maxZoom = 2.1f;
	static int viewWidth;
	static int viewHeight;
	static int nMapWidth;
	static int nMapHeight;
	VertexArray vertexArray;  //Special SFML array І use for map
	RectangleShape backgroundRect;
	Texture backgroundSzymonTexture;
	Sprite backgroundSzymonSprite;
	VertexArray groundSzymon;

	int mapType; 
	int nUnitsInTeam;

	SoundBuffer bufferExplosion;
	Sound soundExplosion;

	std::vector<cTeam> teamsList;

	std::list<std::unique_ptr<cPhysicsObject>> objectList; //list with all objects on a map
	cPhysicsObject* pPlayerControlled = nullptr;
	cPhysicsObject* pCameraTrac = nullptr;

	bool bEnergising = false;
	float fEnergLevel = 0.0f;
	float fEnergTime = 0.0f;
	float maxEnergisingTime = 1.0f;
	bool bWeaponFire = false;

	const float gravity = 1000.0f;

	bool isMousePressed = false;

	bool isPlayerHaveControl = false;
	bool isPlayerActionComplete = false;

	int nCurrentTeam = 0;

	Font font;
	unsigned int initialFontSize = 32;
	const float fBaseRounfTimeConst = 40;
	float fBaseRoundTime = fBaseRounfTimeConst;
	float fRoundTime;
	Text roundTimeText;
	bool bShowCountdown = false;

	enum GAME_STATE {
		GS_RESET = 0,
		GS_MAP_MAKE = 1,
		GS_MAP_MAKING,
		GS_ALLOCATE_UNITS,
		GS_ALLOCATING_UNITS,
		GS_START_PLAY,
		GS_CAMERA_MODE,
		GS_GAME_OVER1
	} nGameState, nNextState;

	bool checkGameStability();
	void explosion(int xPosition, int yPosition, float radius);
	void fillMap(); 
	void fillMapSzymon();
	void handleInput(); //handle users input
	void logic(); //some stuff that don`t really fit to other two functions
	void draw(); 

	//MENU

	int selectedItemIndex;
	int selectedItemPasueIndex;
	bool returnclicked;

	int numberofplayers_clicked;
	int map_clicked;

	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Text options_buttons_menu[4];
	sf::Text pauseMenu_buttons_menu[2];
	sf::Text gameover_menu[2];
	sf::Text map_buttons_menu[2];
	sf::Text number_of_players[2];
};