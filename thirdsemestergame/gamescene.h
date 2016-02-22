// This class is the base for other level classes, to create game scenes

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Audio.hpp>

class GameScene {
public:
	sf::Sprite bgSprite;
	sf::Texture bgTex;
	std::string bgPath;

	struct entity {
		int id;
		sf::Sprite Sprite;
		sf::Texture Tex;
		std::string texPath;
		float x;
		float y;
	};

	entity elementTemplate;

	std::vector< entity > currentEntities;

	std::string Name;
	sf::Music AmbientSound;

	int previousQuestid;

public:
	GameScene();

	//Gameloop for each level
	virtual void Update(int currentQuestid);

	//Set levelname, for the correct entry finding in quests.xml
	void setName(const std::string &Name);

	//set the level background
	void setBgPath(const std::string &bgPath);

	//set the level background sound
	void setLvlSound(const std::string &audioPath);

	//add entities to the level scene
	void addEnt(int id, std::string texPath, float x, float y);

	//remove entities from the level scene
	void delEnt(int id);
};

