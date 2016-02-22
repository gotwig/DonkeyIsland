////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "tinyxml2.h"

// CUSTOM classes
#include "Inventory.h"
#include "Quests.h"

#include "gamescene.h"

#include "lake_grass.h"
#include "house.h"
#include "flower.h"


#include "AnimatedSprite.hpp"

using namespace sf;
using namespace tinyxml2;

int main()
{
	//Initalize Variables and Settings
	const sf::Vector2i screenDimensions(800, 600);

	FloatRect playerMoveSpace = sf::FloatRect(100, 100, screenDimensions.x - 100, screenDimensions.y - 320);

	RenderWindow window(VideoMode(screenDimensions.x, screenDimensions.y), "Donkey Island", Style::Titlebar | Style::Close);

	window.setFramerateLimit(60);

	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	Texture MenuBGTex;
	Sprite MenuBackground;

	Texture PlayerTex;
	AnimatedSprite PlayerImage;

	sf::Time actionTimer;

	int loadedLevelIndex = 0;

	GameScene* levels[] = { new LakeGrass(), new flower(), new House() };
	GameScene* loadedLevel = levels[loadedLevelIndex];

	tinyxml2::XMLElement* levelElement = NULL;

	static bool dragging = false;

	sf::Vector2f Target1;

	Inventory::item *draggeditem = NULL;

	bool clicked = false;

	if (MenuBGTex.loadFromFile("resources/menubackground.jpg")) {
		MenuBackground.setTexture(MenuBGTex);
		MenuBackground.setPosition(0.0f, 460.0f);
	}

	// load a new inventory. The inventory is kept across scenes.
	Inventory* playerInventory = new Inventory();

	// load a new quest journal. Each level, this variable is recreated with the right quests for that current level
	Quests* playerQuests = new Quests(loadedLevel);


	if (!PlayerTex.loadFromFile("resources/donkeyMovement.png")) {
		std::cout << "Failed to load player spritesheet!" << std::endl;
		return 1;
	}

	Animation walkingAnimationRight;
	walkingAnimationRight.setSpriteSheet(PlayerTex);
	walkingAnimationRight.addFrame(sf::IntRect(200, 0, 200, 200));
	walkingAnimationRight.addFrame(sf::IntRect(400, 0, 200, 200));
	walkingAnimationRight.addFrame(sf::IntRect(600, 0, 200, 200));
	walkingAnimationRight.addFrame(sf::IntRect(0, 0, 200, 200));

	Animation walkingAnimationLeft;
	walkingAnimationLeft.setSpriteSheet(PlayerTex);
	walkingAnimationLeft.addFrame(sf::IntRect(200, 200, 200, 200));
	walkingAnimationLeft.addFrame(sf::IntRect(400, 200, 200, 200));
	walkingAnimationLeft.addFrame(sf::IntRect(600, 200, 200, 200));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 200, 200, 200));

	Animation walkingAnimationIdle;
	walkingAnimationIdle.setSpriteSheet(PlayerTex);
	walkingAnimationIdle.addFrame(sf::IntRect(200, 400, 200, 200));
	walkingAnimationIdle.addFrame(sf::IntRect(400, 400, 200, 200));
	walkingAnimationIdle.addFrame(sf::IntRect(600, 400, 200, 200));
	walkingAnimationIdle.addFrame(sf::IntRect(0, 400, 200, 200));

	Animation* currentAnimation = &walkingAnimationLeft;

	PlayerImage = AnimatedSprite(sf::seconds(0.1), true, false);
	PlayerImage.setPosition(sf::Vector2f(screenDimensions / 3));

	sf::Clock frameClock;


	float speed = 160.f;
	bool noKeyWasPressed = true;
	// ------------------------
	// Initialization ends here 

	// Our GAMELOOP starts here
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::MouseButtonReleased) {
				playerInventory->refreshItems();
				dragging = false;
				clicked = false;
			}

		}

		sf::Time frameTime = frameClock.restart();

		// if a key was pressed set the correct animation and move correctly
		sf::Vector2f movement(0.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			movement.y -= speed;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			movement.y += speed;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			currentAnimation = &walkingAnimationLeft;
			movement.x -= speed;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			currentAnimation = &walkingAnimationRight;
			movement.x += speed;
			noKeyWasPressed = false;
		}
		PlayerImage.play(*currentAnimation);
		PlayerImage.move(movement * frameTime.asSeconds());

		// if no key was pressed stop the animation
		if (noKeyWasPressed)
		{
			//PlayerImage.stop();
			PlayerImage.setFrameTime(sf::seconds(0.4));

			currentAnimation = &walkingAnimationIdle;
		}
		if (!noKeyWasPressed) {
			PlayerImage.setFrameTime(sf::seconds(0.1));
		}
		noKeyWasPressed = true;

		// update AnimatedSprite
		PlayerImage.update(frameTime);
		
		// constatly check if the player completed the quest
		playerQuests->checkQuests(draggeditem, playerInventory, PlayerImage);

		window.clear();

		if (loadedLevel) {
			// draw the level background
			window.draw(loadedLevel->bgSprite);
		}

		// draw the menubackground (bottom part of screen)
		window.draw(MenuBackground);

		for (auto && entity : loadedLevel->currentEntities) {
			// draw all active entities in the level
			window.draw(entity.Sprite);
		}

		// Show text of talking NPCs
		if (playerQuests->triggerShowText) {

			if (playerQuests->clock.getElapsedTime().asSeconds() < 10)
				window.draw(playerQuests->talkText);

			if (playerQuests->clock.getElapsedTime().asSeconds() > 10)
				playerQuests->triggerShowText = false;
		}

		window.draw(PlayerImage);
		window.draw(playerQuests->currentQuestText);

		for (auto && item : playerInventory->currentItems) {
			// draw all items in the player invneotry
			window.draw(item.itemIconSprite);
		}

		// initiate the final draw call
		window.display();

		// Switch level, if 5 tasks have been accomplished in every map
		if (playerQuests->currentQuestId > 5 && loadedLevelIndex <= 3) {
			delete loadedLevel;
			delete playerQuests;

			loadedLevelIndex++;
			loadedLevel = levels[loadedLevelIndex];
			playerQuests = new Quests(loadedLevel);
			PlayerImage.setPosition(0.0f, 100.0f);
		}

		// Execute the Game Loop in each individual level constantly
		loadedLevel->Update(playerQuests->currentQuestId);

		//Check for left mouse clicks
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(localPosition);
			// Move player, if cursor is in game world
			if (localPosition.y < 380 && !dragging) {
					Target1.x = worldPos.x - 100;
					Target1.y = worldPos.y - 100;
			}
			// Use item and init dragging, if cursor is in menu (bottom screen part)
			if (localPosition.y > 380 && !dragging) {

				for (auto && item : playerInventory->currentItems) {
					if (localPosition.y < item.itemIconSprite.getPosition().y + item.itemIconSprite.getGlobalBounds().height && localPosition.y   > item.itemIconSprite.getPosition().y && localPosition.x  < item.itemIconSprite.getPosition().x + item.itemIconSprite.getGlobalBounds().width && localPosition.x  > item.itemIconSprite.getPosition().x) {
						item.itemIconSprite.setPosition(localPosition.x - 32, localPosition.y - 32);
						dragging = true;
						draggeditem = &item;

					}

				}

			}


			if (draggeditem) {
				if (dragging) {
					//Set the item position to the mouse cursor position if the user is dragging it
					draggeditem->itemIconSprite.setPosition(localPosition.x - 32, localPosition.y - 32);
				}



			}
			// MOVE TO POINT via CURSOR
			float k = 1;
			// Speed Constant
			float px = PlayerImage.getPosition().x;
			float py = PlayerImage.getPosition().y;
			float ex = Target1.x;
			float ey = Target1.y;

			// "clicked" is used to not allow the player to just drag his charachter across the screen,
			// but instead the player has to confirm each charachter movement by mouse click.

			if (!clicked) {
				PlayerImage.setPosition(Target1.x, Target1.y);
			}

			clicked = true;

		}

	}


	return 0;
}

