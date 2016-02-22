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
	
	// dynamic array for the currentItems in the player inventory
	std::vector< struct item > currentItems;

	// keep the inventory state up-to-date
	void refreshItems();
	
	//add new items by id
	void addItem(int id);
	
	//remove new items by id
	void removeItem(int id);

};
