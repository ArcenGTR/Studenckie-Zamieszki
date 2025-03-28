#include <memory>
#include "Game.h"
#include "Functions.h"

int Game::viewWidth = 1920;
int Game::viewHeight = 1080;
int Game::nMapWidth = 4500;
int Game::nMapHeight = 2300;

sf::Event event;

//, Style::Fullscreen
// pre initialization of some variables
Game::Game(int mapType, int nUnitsInTeam) : window(VideoMode(viewWidth, viewHeight), "Worms", Style::Fullscreen),
view(FloatRect(0, 0, viewWidth, viewHeight)),
vertexArray(Points, nMapWidth* nMapHeight),
groundSzymon(Points, nMapWidth* nMapHeight),
backgroundRect(Vector2f(nMapWidth, nMapHeight)) {

	this->mapType = mapType;
	this->nUnitsInTeam = nUnitsInTeam;
	window.setFramerateLimit(144); //fps_max 144
	view.setCenter(nMapWidth / 2, nMapHeight / 2);

	if (!backgroundSzymonTexture.loadFromFile("materials\\background.jpg")) {
		std::cout << "Failed to load background!" << std::endl;
	}
	backgroundSzymonSprite.setTexture(backgroundSzymonTexture);
	backgroundSzymonSprite.setPosition(0, 0);




	if (!font.loadFromFile("ARIAL.TTF")) {
		std::cout << "Failed to load font!" << std::endl;
	}
	roundTimeText.setFont(font);
	roundTimeText.setCharacterSize(initialFontSize);
	roundTimeText.setFillColor(sf::Color::Black);
	roundTimeText.setPosition(10.0f, 10.0f);

	//Aim texture

	if (!aimTexture.loadFromFile("materials\\aimText.png")) {
		std::cout << "Failed to load aim!" << std::endl;
	}
	aimSprite.setTexture(aimTexture);


	if (!bufferExplosion.loadFromFile("sounds\\explosion.wav")) { std::cout << "Sound load error" << std::endl; }
	soundExplosion.setBuffer(bufferExplosion);

	backgroundRect.setFillColor(Color::Blue);

	nGameState = GS_RESET;
	nNextState = GS_RESET;

	srand(time(NULL));

	//Menu

	if (!font.loadFromFile("ARIAL.TTF")) {
		//error
	}

	sf::CircleShape circle;
	circle.setRadius(14);
	circle.setOrigin({ 14, 14 });
	circle.setFillColor(Color::White);
	circle.setOutlineColor(Color::Yellow);
	circle.setOutlineThickness(1.0f);

	//main menu buttoms
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Magenta);
	menu[0].setOutlineColor(sf::Color::White);
	menu[0].setOutlineThickness(3);
	menu[0].setString("PLAY");
	menu[0].setCharacterSize(50);
	menu[0].setPosition(sf::Vector2f(viewWidth / 5, viewHeight / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setOutlineColor(sf::Color::White);
	menu[1].setOutlineThickness(3);
	menu[1].setString("OPTIONS");
	menu[1].setCharacterSize(50);
	menu[1].setPosition(sf::Vector2f(viewWidth / 5, viewHeight / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setOutlineColor(sf::Color::White);
	menu[2].setOutlineThickness(3);
	menu[2].setString("QUIT");
	menu[2].setCharacterSize(50);
	menu[2].setPosition(sf::Vector2f(viewWidth / 5, viewHeight / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	//options buttons


	options_buttons_menu[0].setFont(font);
	options_buttons_menu[0].setFillColor(sf::Color::White);
	options_buttons_menu[0].setOutlineColor(sf::Color::White);
	options_buttons_menu[0].setOutlineThickness(3);
	options_buttons_menu[0].setString("NUMBER OF PLAYERS: ");
	options_buttons_menu[0].setCharacterSize(50);
	options_buttons_menu[0].setPosition(sf::Vector2f(viewWidth / 5 - 200, viewHeight / (3 + 1) * 1));

	options_buttons_menu[1].setFont(font);
	options_buttons_menu[1].setFillColor(sf::Color::White);
	options_buttons_menu[1].setOutlineColor(sf::Color::White);
	options_buttons_menu[1].setOutlineThickness(3);
	options_buttons_menu[1].setString("MAP: ");
	options_buttons_menu[1].setCharacterSize(50);
	options_buttons_menu[1].setPosition(sf::Vector2f(viewWidth / 5 - 150, viewHeight / (3 + 1) * 2));


	options_buttons_menu[2].setFont(font);
	options_buttons_menu[2].setFillColor(sf::Color::Magenta);
	options_buttons_menu[2].setOutlineColor(sf::Color::White);
	options_buttons_menu[2].setOutlineThickness(3);
	options_buttons_menu[2].setString("RETURN");
	options_buttons_menu[2].setCharacterSize(50);
	options_buttons_menu[2].setPosition(sf::Vector2f(viewWidth / 5 - 200, viewHeight / (3 + 1) * 3));


	//map button 

	map_buttons_menu[0].setFont(font);
	map_buttons_menu[0].setFillColor(sf::Color::White);
	map_buttons_menu[0].setOutlineColor(sf::Color::White);
	map_buttons_menu[0].setOutlineThickness(3);
	map_buttons_menu[0].setString("AGH");
	map_buttons_menu[0].setCharacterSize(50);
	map_buttons_menu[0].setPosition(sf::Vector2f(viewWidth / 3 - 250, viewHeight / (3 + 1) * 2));

	map_buttons_menu[1].setFont(font);
	map_buttons_menu[1].setFillColor(sf::Color::White);
	map_buttons_menu[1].setOutlineColor(sf::Color::White);
	map_buttons_menu[1].setOutlineThickness(3);
	map_buttons_menu[1].setString("Random");
	map_buttons_menu[1].setCharacterSize(50);
	map_buttons_menu[1].setPosition(sf::Vector2f(viewWidth / 3 - 250, viewHeight / (3 + 1) * 2));

	//number of players button

	number_of_players[0].setFont(font);
	number_of_players[0].setFillColor(sf::Color::White);
	number_of_players[0].setOutlineColor(sf::Color::White);
	number_of_players[0].setOutlineThickness(3);
	number_of_players[0].setString("3");
	number_of_players[0].setCharacterSize(50);
	number_of_players[0].setPosition(sf::Vector2f(viewWidth / 2 - 150, viewHeight / (3 + 1) * 1));

	number_of_players[1].setFont(font);
	number_of_players[1].setFillColor(sf::Color::White);
	number_of_players[1].setOutlineColor(sf::Color::White);
	number_of_players[1].setOutlineThickness(3);
	number_of_players[1].setString("4");
	number_of_players[1].setCharacterSize(50);
	number_of_players[1].setPosition(sf::Vector2f(viewWidth / 2 - 150, viewHeight / (3 + 1) * 1));


	//pause manu
	pauseMenu_buttons_menu[0].setFont(font);
	pauseMenu_buttons_menu[0].setFillColor(sf::Color::Magenta);
	pauseMenu_buttons_menu[0].setOutlineColor(sf::Color::White);
	pauseMenu_buttons_menu[0].setOutlineThickness(3);
	pauseMenu_buttons_menu[0].setString("RESUME");
	pauseMenu_buttons_menu[0].setCharacterSize(50);
	pauseMenu_buttons_menu[0].setPosition(sf::Vector2f(viewWidth / 5 - 200, viewHeight / 3));

	pauseMenu_buttons_menu[1].setFont(font);
	pauseMenu_buttons_menu[1].setFillColor(sf::Color::White);
	pauseMenu_buttons_menu[1].setOutlineColor(sf::Color::White);
	pauseMenu_buttons_menu[1].setOutlineThickness(3);
	pauseMenu_buttons_menu[1].setString("BACK TO MAIN MENU");
	pauseMenu_buttons_menu[1].setCharacterSize(50);
	pauseMenu_buttons_menu[1].setPosition(sf::Vector2f(viewWidth / 5 - 200, viewHeight / 1.5));


	//gameover menu
	gameover_menu[0].setFont(font);
	gameover_menu[0].setFillColor(sf::Color::Magenta);
	gameover_menu[0].setOutlineColor(sf::Color::White);
	gameover_menu[0].setOutlineThickness(3);
	gameover_menu[0].setString("BACK TO MAIN MENU");
	gameover_menu[0].setCharacterSize(50);
	gameover_menu[0].setPosition(sf::Vector2f(viewWidth / 5 + 190, viewHeight - 200));




	selectedItemIndex = 0;

	map_clicked = 0;

	numberofplayers_clicked = 0;

	returnclicked = false;

	selectedItemPasueIndex = 0;

	isPaused = false;
}

void Game::run() {
	while (window.isOpen()) {
		if (isPaused) {

			MenuPauseRun();
			//nGameState = GS_CAMERA_MODE;
			deltaTime = clock.restart().asSeconds();

		}
		else
		{
			for (int i = 0; i < 5; i++) { logic(); }
			deltaTime = clock.restart().asSeconds();
			handleInput();
			draw();
			nGameState = nNextState;


		}
	}
}

void Game::fillMap() {
	float* fSurface = new float[nMapWidth];
	float* fNoiseSeed = new float[nMapWidth];

	for (int i = 0; i < nMapWidth; ++i) {
		fNoiseSeed[i] = (float)rand() / (float)RAND_MAX;
	}

	fNoiseSeed[0] = 0.5f;
	perlinNoise1D(nMapWidth, fNoiseSeed, 6, 2.2f, fSurface);

	for (int x = 0; x < nMapWidth; ++x) {
		for (int y = 0; y < nMapHeight; ++y) {
			int index = y * nMapWidth + x;

			vertexArray[index].position = Vector2f(x, y);
			if (y >= fSurface[x] * nMapHeight) vertexArray[index].color = Color::Green;
			else vertexArray[index].color = Color::Transparent;
		}
	}

	delete[] fSurface;
	delete[] fNoiseSeed;
}

void Game::fillMapSzymon() {
	Image image;
	if (!image.loadFromFile("materials\\destructive_overlay.png")) {
		std::cout << "Failed to load image!" << std::endl;
	}
	for (unsigned int y = 0; y < image.getSize().y; ++y) {
		for (unsigned int x = 0; x < image.getSize().x; ++x) {
			sf::Color pixelColor = image.getPixel(x, y);
			if (pixelColor.a == 0) {
				pixelColor = sf::Color::Transparent;
			}
			vertexArray[(y * image.getSize().x) + x].position = sf::Vector2f(x, y);
			vertexArray[(y * image.getSize().x) + x].color = pixelColor;
		}
	}
}

bool Game::checkGameStability() {
	for (auto& p : objectList) {
		if (!(p->bStable)) {
			return false;
		}
	}

	return true;
}

void Game::explosion(int xPosition, int yPosition, float radius) {

	auto CircleBresenham = [&](int xc, int yc, int r)
		{
			// Taken from wikipedia
			int x = 0;
			int y = r;
			int p = 3 - 2 * r;
			if (!r) return;

			auto drawline = [&](int sx, int ex, int ny)
				{
					for (int i = sx; i < ex; i++)
						if (ny >= 0 && ny < nMapHeight && i >= 0 && i < nMapWidth)
							vertexArray[ny * nMapWidth + i].color = Color::Transparent;
				};

			while (y >= x)
			{
				// Modified to draw scan-lines instead of edges
				drawline(xc - x, xc + x, yc - y);
				drawline(xc - y, xc + y, yc - x);
				drawline(xc - x, xc + x, yc + y);
				drawline(xc - y, xc + y, yc + x);
				if (p < 0) p += 4 * x++ + 6;
				else p += 4 * (x++ - y--) + 10;
			}
		};

	soundExplosion.play();

	// making a hole
	CircleBresenham(xPosition, yPosition, radius);

	// shockwave other objects
	for (auto& p : objectList) {
		Vector2f distance = { p->position.x - xPosition, p->position.y - yPosition };
		float fDistance = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
		if (fDistance < 0.0001f) fDistance = 0.0001f; // check for zero division		

		if (fDistance < radius) {
			p->velocity = { distance.x / fDistance * radius, distance.y / fDistance * radius };
			p->bStable = false;
		}
	}

	//counting hp of units
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < nUnitsInTeam; j++) {
			cActor* p = teamsList[i].members[j];

			Vector2f distance = { p->position.x - xPosition, p->position.y - yPosition };
			float fDistance = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
			if (fDistance < 0.0001f) fDistance = 0.0001f; // check for zero division	

			if (fDistance < radius) {
				p->fHealth -= sqrt(pow(distance.x / fDistance * radius, 2) + pow(distance.y / fDistance * radius, 2)) / 2.0f;
				if (p->fHealth <= 0) p->bIsPlayable = false;
			}
		}
	}

	// spawning debris
	for (int i = 0; i < radius / 10; i++) {
		cDebris* p = new cDebris(xPosition, yPosition, Color(240, 144, 41));
		objectList.push_back(std::unique_ptr<cDebris>(p));
	}
}

void Game::handleInput() {

	Vector2i mousePosition = Mouse::getPosition(window);


	//Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (isPlayerHaveControl) {
			// This part handle mouse scroll and uses it for zoom(done with chatgpt)
			if (event.type == Event::MouseWheelMoved) {
				float zoomFactor = 1.1f;
				if (event.mouseWheel.delta > 0 && view.getSize().x * (1.0f / zoomFactor) >= viewWidth * minZoom) {
					view.zoom(1.0f / zoomFactor);
				}
				else if (event.mouseWheel.delta < 0 && view.getSize().x * zoomFactor <= viewWidth * maxZoom) {
					view.zoom(zoomFactor);
				}
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) pCameraTrac = pPlayerControlled;

	//drops a missile
	//if (Mouse::isButtonPressed(Mouse::Right) && !isMousePressed) {
	//	isMousePressed = true;
	//
	//	Vector2f worldMousePos = window.mapPixelToCoords(mousePosition, view);
	//
	//	cMissile* p = new cMissile(worldMousePos.x, worldMousePos.y, 25);
	//	objectList.push_back(std::unique_ptr<cMissile>(p));
	//}

	if (isPlayerHaveControl) {
		// map scroll with mouse
		if (mousePosition.x <= 15) view.move(-25, 0);
		if (mousePosition.x >= window.getSize().x - 15) view.move(25, 0);
		if (mousePosition.y <= 15) view.move(0, -25);
		if (mousePosition.y >= window.getSize().y - 5) view.move(0, 25);

		// mouse scroll with keyboard
		if (Keyboard::isKeyPressed(Keyboard::Left)) view.move(-15, 0);
		if (Keyboard::isKeyPressed(Keyboard::Right)) view.move(15, 0);
		if (Keyboard::isKeyPressed(Keyboard::Up)) view.move(0, -15);
		if (Keyboard::isKeyPressed(Keyboard::Down)) view.move(0, 15);
	}

	// camera tracking
	if (pCameraTrac != nullptr) {
		Vector2f camTarget = pCameraTrac->position;
		Vector2f camActual = view.getCenter();
		view.setCenter(camActual + ((camTarget - camActual) * 5.0f * deltaTime));
	}

	// bounds of camera
	if (view.getCenter().x - view.getSize().x / 2 < 0) view.setCenter(view.getSize().x / 2, view.getCenter().y);
	if (view.getCenter().x + view.getSize().x / 2 > nMapWidth) view.setCenter(nMapWidth - view.getSize().x / 2, view.getCenter().y);
	if (view.getCenter().y - view.getSize().y / 2 < 0) view.setCenter(view.getCenter().x, view.getSize().y / 2);
	if (view.getCenter().y + view.getSize().y / 2 > nMapHeight) view.setCenter(view.getCenter().x, nMapHeight - view.getSize().y / 2);

	std::cout << "= " << nGameState << std::endl;
	// Control Supervisor
	switch (nGameState) {
	case GS_RESET: // Set game variables to know state
	{
		isPlayerHaveControl = false;
		nNextState = GS_MAP_MAKE;
	}
	break;

	case GS_MAP_MAKE: // Create a new terrain
	{
		isPlayerHaveControl = false;

		if (map_clicked % 2 == 1) {
			fillMap();
		}
		else if (map_clicked % 2 == 0) {
			fillMapSzymon();
		}

		nNextState = GS_MAP_MAKING;
	}
	break;

	case GS_MAP_MAKING:
	{
		isPlayerHaveControl = false;
		nNextState = GS_ALLOCATE_UNITS;
	}
	break;

	case GS_ALLOCATE_UNITS: // Add a unit to the top of the screen
	{
		isPlayerHaveControl = false;

		if (!teamsList.empty()) {
			// Iterate through teamsList and check if members vector is not empty before clearing
			for (auto& team : teamsList) {
				// Check if the members vector is not empty
				if (!team.members.empty()) {
					// Clear the members vector for the team
					team.members.clear();
				}
			}

			// Clear the teamsList vector
			teamsList.clear();
		}
		if (!objectList.empty()) {
			objectList.clear();
		}

		if (numberofplayers_clicked % 2 == 0) {
			nUnitsInTeam = 3;
		}
		else if (numberofplayers_clicked % 2 == 1) {
			nUnitsInTeam = 4;
		}

		for (int i = 0; i < 2; i++) {
			teamsList.push_back(cTeam());

			for (int j = 0; j < nUnitsInTeam; j++) {
				int xActor = j * 450 + 350;
				int yActor = 200;
				if (i) {
					xActor = nMapWidth - xActor;
				}

				cActor* p = new cActor(xActor, yActor);
				p->nTeam = i;
				p->setTexture();
				objectList.push_back(std::unique_ptr<cActor>(p));

				teamsList[i].members.push_back(p);
				teamsList[i].nTeamSize = nUnitsInTeam;
			}

			pPlayerControlled = teamsList[0].members[teamsList[0].nCurrentMember];
			pCameraTrac = pPlayerControlled;

		}


		nNextState = GS_ALLOCATING_UNITS;
	}
	break;

	case GS_ALLOCATING_UNITS: // Stay in this state whilst units are deploying
	{
		isPlayerActionComplete = false;
		isPlayerHaveControl = false;

		if (checkGameStability()) {
			nNextState = GS_START_PLAY;
		}
		else {
			nNextState = GS_ALLOCATING_UNITS;
		}
	}
	break;

	case GS_START_PLAY: // Player is in control of unit
	{
		fRoundTime += deltaTime;
		isPlayerHaveControl = true;
		bShowCountdown = true;

		if (!teamsList[(nCurrentTeam + 1) % 2].IsTeamAlive()) {
			nNextState = GS_GAME_OVER1;
		}

		if (isPlayerActionComplete || fBaseRoundTime - fRoundTime < 0) {
			fRoundTime = 0;
			fBaseRoundTime = fBaseRounfTimeConst;
			nNextState = GS_CAMERA_MODE;
		}
	}
	break;

	case GS_CAMERA_MODE: // Camera is tracking on-screen action
	{
		isPlayerHaveControl = false;
		isPlayerActionComplete = false;
		bShowCountdown = false;

		if (checkGameStability()) {
			int nOldTeam = nCurrentTeam;
			do {
				nCurrentTeam++;
				nCurrentTeam %= 2;
			} while (!teamsList[nCurrentTeam].IsTeamAlive());

			pPlayerControlled = teamsList[nCurrentTeam].GetNextMember();
			pCameraTrac = pPlayerControlled;
			nNextState = GS_START_PLAY;

		}
	}
	break;

	case GS_GAME_OVER1:
	{
		sf::FloatRect ekran1;
		ekran1.height = 1080;
		ekran1.width = 1920;
		view.reset(ekran1);
		window.setView(view);

		GameOverMenuRun();

	}
	break;
	}

	// controls of actor
	if (pPlayerControlled != nullptr && isPlayerHaveControl) {
		if (pPlayerControlled->bStable) {

			// jumping
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				float angle = ((cActor*)pPlayerControlled)->shootAngle;
				pPlayerControlled->velocity.x = 35.0f * cosf(angle);
				pPlayerControlled->velocity.y = gravity / 8.0f * sinf(angle);
				pPlayerControlled->bStable = false;
			}
			// angle control
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				cActor* player = (cActor*)pPlayerControlled;
				player->shootAngle += 2.0f * deltaTime;

				if (player->shootAngle > 0.75f) {
					player->shootAngle = 0.75f;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				cActor* player = (cActor*)pPlayerControlled;
				player->shootAngle -= 2.0f * deltaTime;

				if (player->shootAngle < -4.0f) {
					player->shootAngle = -4.0f;
				}
			}
			// choosing power to shoot
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				if (!bEnergising) {

					bEnergising = true;
					fEnergLevel = 0.0f;
					fEnergTime = 0.0f;
				}

				fEnergTime += deltaTime;
				fEnergLevel = fEnergTime / maxEnergisingTime;

				if (fEnergLevel >= 1.0f) {
					fEnergLevel = 1.0f;
				}
			}
			else {
				if (bEnergising) {
					bWeaponFire = true;
				}
				bEnergising = false;
				fEnergTime = 0.0f;
			}
			// shooting
			if (bWeaponFire) {
				cActor* player = (cActor*)pPlayerControlled;

				Vector2f missileOrigin = player->position;
				Vector2f weaponShootDirection = { cosf(player->shootAngle), sinf(player->shootAngle) };

				cMissile* m = new cMissile(missileOrigin.x, missileOrigin.y);
				m->velocity = { weaponShootDirection.x * 500.0f * fEnergLevel, weaponShootDirection.y * 700.0f * fEnergLevel };
				objectList.push_back(std::unique_ptr<cMissile>(m));
				pCameraTrac = m;

				bWeaponFire = false;
				fEnergLevel = 0.0f;
				bEnergising = false;

				isPlayerActionComplete = true;
			}

		}
	}

	// jest a check that if mouse button pressed 
	if (!Mouse::isButtonPressed(sf::Mouse::Left) && !(Mouse::isButtonPressed(Mouse::Middle)) && !(Mouse::isButtonPressed(Mouse::Right))) { isMousePressed = false; }

	// just stuff for debug
	std::cout << view.getCenter().x << " " << view.getCenter().y << "    " << mousePosition.x << " " << mousePosition.y << std::endl;
	for (auto& p : objectList) {
		std::cout << p->position.x << " " << p->position.y << std::endl;
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {

		sf::FloatRect ekran;
		ekran.height = 1080;
		ekran.width = 1920;
		view.reset(ekran);
		window.setView(view);
		isPaused = true;

	}
}

void Game::logic() {
	// gravity and collision with map for objects
	for (auto& p : objectList) {
		// applying gravity

		p->acceleration.y += gravity * deltaTime;
		p->velocity += p->acceleration * deltaTime;

		// creating vector with object position in next frame
		Vector2f potentialPos = p->position + (p->velocity * deltaTime);

		// reseting acceleration
		p->acceleration = Vector2f(0.0f, 0.0f);
		p->bStable = false;

		Vector2f response; //direction of bouncing
		bool bCollision = false;
		p->directionAngle = atan2(p->velocity.y, p->velocity.x);

		if (dynamic_cast<cActor*>(p.get()) != nullptr) {
			if (potentialPos.x < 0) {
				potentialPos.x = 0;
				p->velocity.x = 0;
			}
			else if (potentialPos.x > nMapWidth) {
				potentialPos.x = nMapWidth;
				p->velocity.x = 0;
			}

			if (potentialPos.y < 0) {
				potentialPos.y = 0;
				p->velocity.y = 0;
				p->bStable = true;
			}
			else if (potentialPos.y > nMapHeight) {
				potentialPos.y = nMapHeight;
				p->velocity.y = 0;
			}
		}

		// loop that checks collision of semicircle of object`s direction
		for (float r = p->directionAngle - 3.1415f / 2.0f; r < p->directionAngle + 3.1415f / 2.0f; r += 3.1415f / 8.0f) {

			// tested point of semicircle
			Vector2f testPos = { p->radius * cos(r) + potentialPos.x, p->radius * sin(r) + potentialPos.y };

			// making code safe from out of bounds
			if (testPos.x >= nMapWidth) testPos.x = nMapWidth - 1;
			if (testPos.y >= nMapHeight) testPos.y = nMapHeight - 1;
			if (testPos.x < 0) testPos.x = 0;
			if (testPos.y < 0) testPos.y = 0;

			// checks collision with everything beside sky and counting response vector
			if (vertexArray[(int)testPos.y * nMapWidth + (int)testPos.x].color != Color::Transparent) {
				response += potentialPos - testPos;
				bCollision = true;
			}
		}
		// counting magnitudes of bouncing and speed
		float fMagVelocity = sqrt(pow(p->velocity.x, 2) + pow(p->velocity.y, 2));
		float fMagResponse = sqrt(pow(response.x, 2) + pow(response.y, 2));

		// if collision occures then counting reflection by formula (found on internet)
		// and doing times nrgLoss for object to slow down
		if (bCollision) {
			p->bStable = true;

			float dot = p->velocity.x * (response.x / fMagResponse) + p->velocity.y * (response.y / fMagResponse);
			p->velocity = { p->nrgLoss * (-2.0f * dot * (response.x / fMagResponse) + p->velocity.x), p->nrgLoss * (-2.0f * dot * (response.y / fMagResponse) + p->velocity.y) };

			if (p->nBounceBeforeDeath >= 0) {
				p->nBounceBeforeDeath--;
				p->bDead = p->nBounceBeforeDeath <= 0;

				if (p->bDead) {
					int nResponce = p->bounceDeathAction();
					if (nResponce > 0) explosion(p->position.x, p->position.y, nResponce);
					pCameraTrac = nullptr;
				}
			}
		}
		else {
			p->position = potentialPos;
		}

		// for objects with small speed
		if (fMagVelocity < 0.1f) p->bStable = true;

	}

	// removes dead objects from the list, unique pointers 
	// automaticly deletes object when out of scope
	objectList.remove_if([](std::unique_ptr<cPhysicsObject>& o) {return o->bDead; });
}

void Game::draw() {

	window.clear();
	window.setView(view); //setting camera

	if (mapType == 1) { window.draw(backgroundRect); }
	else if (mapType == 2) { window.draw(backgroundSzymonSprite); }

	window.draw(vertexArray); //drawing map

	for (auto& p : objectList) { //drawing objects
		p->draw(window);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < nUnitsInTeam; j++) {
				cActor* player = teamsList[i].members[j];

				if (player->bIsPlayable) {
					RectangleShape healthIndicator(Vector2f(player->fHealth, 10));
					healthIndicator.setOutlineColor(Color(69, 7, 7));
					healthIndicator.setOutlineThickness(2);
					healthIndicator.setPosition(player->position.x - 0.5f * player->fHealth, player->position.y - player->radius + 70);
					healthIndicator.setFillColor(Color::Red);
					window.draw(healthIndicator);
				}
				else {
					player->setGrave();
				}
			}
		}

		cActor* player = (cActor*)pPlayerControlled;

		if (p.get() == player) {
			Vector2f aimPos = { player->position.x + 60.0f * cosf(player->shootAngle) - 10, player->position.y + 60.0f * sinf(player->shootAngle) - 10 };

			aimSprite.setPosition(aimPos);
			window.draw(aimSprite);

			float indicatorHeight = 50.0f;
			RectangleShape energyIndicator(Vector2f(10.0f, fEnergLevel * indicatorHeight));
			energyIndicator.setPosition(player->position.x - 45.0f, player->position.y - 50.0f);
			energyIndicator.setFillColor(Color(255, 136, 18));
			window.draw(energyIndicator);
		}


	}

	if (bShowCountdown) {
		roundTimeText.setString("Round Time: " + std::to_string((int)(fBaseRoundTime - fRoundTime)));

		sf::Vector2f cameraPosition = view.getCenter() - view.getSize() / 2.0f;

		roundTimeText.setPosition(cameraPosition.x + 10.0f, cameraPosition.y + 10.0f);
		roundTimeText.setCharacterSize(initialFontSize / (window.getSize().y / view.getSize().y));

		window.draw(roundTimeText);
	}

	window.display();

}


void Game::Menu_run() {


	//setting background

	RectangleShape background;
	background.setSize(Vector2f(viewWidth, viewHeight));
	Texture MainTexture;
	MainTexture.loadFromFile("materials/mainpicture.jpg");
	background.setTexture(&MainTexture);

	//photo to options

	RectangleShape OptionsBackground;
	OptionsBackground.setSize(Vector2f(viewWidth, viewHeight));
	Texture options_back_texture;
	options_back_texture.loadFromFile("materials/mainpicture.jpg");
	OptionsBackground.setTexture(&options_back_texture);



	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Up:
					MoveUp();
					break;
				case sf::Keyboard::Down:
					MoveDown();
					break;
				case sf::Keyboard::Enter:
					switch (GetPressedItem()) {
					case 0:
						nGameState = GS_RESET;
						fBaseRoundTime = fBaseRounfTimeConst;
						bShowCountdown = false;
						//teamsList.clear();
						teamsList.resize(2);
						run();
						break;
					case 1:
						OptionsRun(OptionsBackground);
						break;

					case 2:
						window.close();
						break;
					}
					break;
				}
			}
		}

		window.clear();

		window.draw(background);

		Menu_draw();

		window.display();
	}
}

void Game::Menu_draw() {
	//drawing buttoms
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(menu[i]);
	}
}

void Game::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Magenta);
	}
}

void Game::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Magenta);
	}
}

void Game::Options_draw() {
	//drawing options buttoms
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(options_buttons_menu[i]);
	}
	window.draw(map_buttons_menu[map_clicked % 2]);
	window.draw(number_of_players[numberofplayers_clicked % 2]);
}

void Game::OptionsMoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		options_buttons_menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		options_buttons_menu[selectedItemIndex].setFillColor(sf::Color::Magenta);
	}
}

void Game::OptionsMoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		options_buttons_menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		options_buttons_menu[selectedItemIndex].setFillColor(sf::Color::Magenta);
	}
}

void Game::OptionsRun(RectangleShape& OptionsBackground) {
	//runing options

	view.setCenter(1920 / 2, 1080 / 2);

	selectedItemIndex = 2;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Up:
					OptionsMoveUp();
					break;
				case sf::Keyboard::Down:
					OptionsMoveDown();
					break;
				case sf::Keyboard::Enter:
					switch (GetPressedItem()) {
					case 0:
						std::cout << "Number of players: ";
						numberofplayers_clicked++;
						break;
					case 1:
						std::cout << "Map: ";
						map_clicked++;
						break;
					case 2:
						returnclicked = true;
						break;
					}
				}
			}
		}
		std::cout << selectedItemIndex;

		if (returnclicked)
			break;

		window.clear();

		window.draw(OptionsBackground);

		Options_draw();

		window.display();
	}
	returnclicked = false;
	selectedItemIndex = 1;

}

//Pasue Menu

void Game::MenuPauseRun() {

	view.setCenter(-1920 / 2, 1080 / 2);

	RectangleShape Pause_background;
	Pause_background.setSize(Vector2f(viewWidth, viewHeight));
	Texture Pause_MainTexture;
	Pause_MainTexture.loadFromFile("materials/mainpicture.jpg");
	Pause_background.setTexture(&Pause_MainTexture);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Up:
					std::cout << "GORA";
					MenuPauseMoveUp();
					break;
				case sf::Keyboard::Down:
					std::cout << "DOL";
					MenuPauseMoveDown();
					break;
				case sf::Keyboard::Enter:
					std::cout << "ENTER";
					switch (GetPressedItemMenuPause()) {
					case 0:
						isPaused = false;
						break;
					case 1:
						isPaused = false;
						Menu_run();
						break;

					}
				}
			}
		}
		if (!isPaused) {
			break;
		}

		window.clear();

		window.draw(Pause_background);

		MenuPause_draw();

		window.display();

	}
	isPaused = false;
}

void Game::MenuPause_draw() {



	for (int i = 0; i < 2; i++) {
		window.draw(pauseMenu_buttons_menu[i]);
		std::cout << pauseMenu_buttons_menu[i].getPosition().y << " " << pauseMenu_buttons_menu[i].getPosition().y << std::endl;
	}
}

void Game::MenuPauseMoveUp() {
	if (selectedItemPasueIndex - 1 >= 0) {
		pauseMenu_buttons_menu[selectedItemPasueIndex].setFillColor(sf::Color::White);
		selectedItemPasueIndex--;
		pauseMenu_buttons_menu[selectedItemPasueIndex].setFillColor(sf::Color::Magenta);
	}
}

void Game::MenuPauseMoveDown() {
	if (selectedItemPasueIndex + 1 < 2) {
		pauseMenu_buttons_menu[selectedItemPasueIndex].setFillColor(sf::Color::White);
		selectedItemPasueIndex++;
		pauseMenu_buttons_menu[selectedItemPasueIndex].setFillColor(sf::Color::Magenta);
	}
}


//game over menu

void Game::GameOverMenuRun() {

	Sprite GameOver_background;
	//GameOver_background.setSize(Vector2f(viewWidth, viewHeight));
	Texture Over_MainTexture;
	
	Over_MainTexture.loadFromFile("materials\\student_win.png");
	GameOver_background.setTexture(Over_MainTexture);

	

	//runing Game Over menu

	Sprite GameOverJaguar_background;
	//GameOver_background.setSize(Vector2f(viewWidth, viewHeight));
	Texture OverJaguar_MainTexture;
	OverJaguar_MainTexture.loadFromFile("materials\\jaguar_win.png");
	GameOverJaguar_background.setTexture(OverJaguar_MainTexture);


	while (window.isOpen()) {
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Enter) {
					Menu_run();
				}
			}
		}
		window.clear();

		if ((nCurrentTeam + 1) % 2 == 1) {
			window.draw(GameOver_background);
		}
		else if ((nCurrentTeam + 1) % 2 == 0) {
			window.draw(GameOverJaguar_background);
		}

		GameOverMenuDraw();

		window.display();

	}

}

void Game::GameOverMenuDraw() {

	for (int i = 0; i < 1; i++) {
		window.draw(gameover_menu[i]);
	}

}