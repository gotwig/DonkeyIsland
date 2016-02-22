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

	//temporary actionSound for each task, which gets played once completed
	sf::Music actionSound;

	// make sure to run each check only once
	bool runOnce = true;
	// XML structure of the quests.xml file
	tinyxml2::XMLElement* levelElement = NULL;
	tinyxml2::XMLDocument doc;
	
	GameScene* currentQuestLevel;
	int currentQuestId = 1;

	// position of entity target
	float targetX, targetY;

	// ids for Entities and items
	int itemId = 0;
	int entId = 0;

	// trigger to show talk text if set to true
	bool triggerShowText = false;

	sf::Font font;

	sf::Text currentQuestText;
	sf::Text talkText;

	Quests(GameScene* currentLevel);
	~Quests();

	//check if quest is completed (runs constantly, by main.cpp)
	void checkQuests(Inventory::item* draggeditem, Inventory* playerInventory, AnimatedSprite playerImage);

};

