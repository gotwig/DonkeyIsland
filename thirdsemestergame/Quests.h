#pragma once
#include "tinyxml2.h"
#include <SFML/Graphics.hpp>
#include "Inventory.h"
#include <SFML/Audio.hpp>
#include <unordered_map>

#include "gamescene.h"

#include "AnimatedSprite.hpp"

class Quests
{
public:

	sf::Music actionSound;
	//sf::Clock actionClock;

	bool runOnce = true;
	tinyxml2::XMLElement* levelElement = NULL;
	GameScene* currentQuestLevel;
	int currentQuestId = 1;

	sf::Clock clock;

	tinyxml2::XMLDocument doc;

	float targetX, targetY;

	int itemId = 0;
	int entId = 0;

	bool triggerShowText = false;

	sf::Font font;


	sf::Text currentQuestText;
	sf::Text talkText;

	Quests(GameScene* currentLevel);
	~Quests();

	void checkQuests(Inventory::item* draggeditem, Inventory* playerInventory, AnimatedSprite playerImage);

};

