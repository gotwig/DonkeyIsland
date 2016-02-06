#pragma once
#include <SFML/Graphics.hpp>

class Inventory {
public:

	struct item {
		char* iconPath;
		int id;
		sf::Sprite itemIconSprite;
		sf::Texture itemIconTex;
	};
	
	std::vector< struct item > currentItems;

	void refreshItems();
	void addItem(int id);
	void removeItem(int id);

};