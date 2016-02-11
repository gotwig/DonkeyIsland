#include "Inventory.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

struct Inventory::item itemList[7] = { { "" },
{ "hay.png" },
{ "ladder.png" },
{ "watercan_inv.png" },
};

void Inventory::refreshItems() {
	float x = 500.0f, y = 500.0f;
	int i = 0;

	for (auto && item : currentItems) {
		if (item.itemIconTex.loadFromFile(std::string("inventoryIcons/") + item.iconPath)) {
			item.itemIconSprite.setTexture(item.itemIconTex);
			item.itemIconSprite.setPosition(x, y);
			x += 100.0f;

			i++;
			if (i > 2) {
				y = 550;

			}

			if (i == 3)
				x = 500.0f;
		}
	}

};

	void Inventory::addItem(int id) {
		if (itemList[id].iconPath) {
			currentItems.push_back(itemList[id]);
			currentItems.back().id = id;
		}

		refreshItems();

	};

	void Inventory::removeItem(int id) {
		currentItems.erase(std::remove_if(currentItems.begin(), currentItems.end(), [=](auto& item) { return item.id == id; }), currentItems.end());
		refreshItems();
		}



