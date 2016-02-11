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

	virtual void Update(int currentQuestid);

	void setName(const std::string &Name);

	void setBgPath(const std::string &bgPath);

	void setLvlSound(const std::string &audioPath);

	void addEnt(int id, std::string texPath, float x, float y);

	void delEnt(int id);
};

