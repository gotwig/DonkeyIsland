#include "Quests.h"
#include <iostream>
#include <string>


Quests::Quests(GameScene* currentLevel)
{
	doc.LoadFile("resources/quests.xml");
	currentQuestLevel = currentLevel;

	font.loadFromFile("resources/Lobster-Regular.ttf");

}


Quests::~Quests()
{
}

void Quests::checkQuests(Inventory::item* draggeditem, Inventory* playerInventory, AnimatedSprite playerImage) {

	for (tinyxml2::XMLElement* child = doc.FirstChildElement("levels")->FirstChildElement("level"); child != NULL; child = child->NextSiblingElement())
	{

		const char* id = child->Attribute("id");

		currentQuestText.setString(id);

		if (currentQuestLevel){
		if (strcmp(id, currentQuestLevel->Name.c_str()) == 0){
			levelElement = child;
		}
		}

	}


	const char* title = levelElement->FirstChildElement("quest")->FirstChildElement("description")->GetText();

	for (tinyxml2::XMLElement* child = levelElement->FirstChildElement("quest"); child != NULL; child = child->NextSiblingElement())
	{
		int id;
		child->QueryIntAttribute("id", &id);

		if (id == currentQuestId){
			
			currentQuestText.setString(child->FirstChildElement("description")->GetText());

						sf::Vector2f playerPos = playerImage.getPosition();

						if (child->Attribute("target")) {
							std::string test = child->Attribute("target");

							//std::string test = "100x200";

							targetX = playerPos.x;
							targetY = playerPos.y;

							if (test != "player"){
								std::size_t pos = test.find("x");
								targetX = std::stof(test.substr(0, pos));
								targetY = std::stof(test.substr(pos + 1));
							}



						}

			if (child->Attribute("action") == std::string("pickupItem")) {

				itemId = 0;
				entId = 0;

				child->QueryIntAttribute("itemvalue", &itemId);

				child->QueryIntAttribute("entvalue", &entId);

				if (playerPos.y < targetY + 70 && playerPos.y   > targetY && playerPos.x  < targetX + 70 && playerPos.x  > targetX) {

					currentQuestLevel->delEnt(entId);
					playerInventory->addItem(itemId);
					currentQuestId++;
					if (child->Attribute("sound")) {
						actionSound.openFromFile(std::string("./sounds/") + child->Attribute("sound"));

						// Play the music
						actionSound.play();
					}
				}

			}

						if (child->Attribute("action") == std::string("useItem")) {

							itemId = 0;

							child->QueryIntAttribute("itemvalue", &itemId);


							if (draggeditem) {
								if (draggeditem->id == itemId) {

									if (draggeditem->itemIconSprite.getPosition().y < targetY + 200 && draggeditem->itemIconSprite.getPosition().y > targetY && draggeditem->itemIconSprite.getPosition().x  < targetX + 200 && draggeditem->itemIconSprite.getPosition().x  > targetX) {
										

										currentQuestId++;

										if (!child->Attribute("dontWaste")) {
											if (draggeditem) {
												playerInventory->removeItem(draggeditem->id);
											}
										}

										draggeditem = NULL;




										if (child->Attribute("sound")) {
											actionSound.openFromFile(std::string("./sounds/") + child->Attribute("sound"));

											// Play the music
											actionSound.play();
										}
									}


									
								}
							}

						}

						if (child->Attribute("action") == std::string("move")) {


							if (playerPos.y < targetY + 200 && playerPos.y   > targetY && playerPos.x  < targetX + 200 && playerPos.x  > targetX) {
								currentQuestId++;
								if (child->Attribute("sound")) {
									actionSound.openFromFile(std::string("./sounds/") + child->Attribute("sound"));

								// Play the music
									actionSound.play();
								}
							}
						}

            if (child->Attribute("action") == std::string("talk")) {


                if (playerPos.y < targetY + 200 && playerPos.y   > targetY && playerPos.x  < targetX + 200 && playerPos.x  > targetX) {


                    talkText.setFont(font);
                    sf::FloatRect textRect = currentQuestText.getLocalBounds();
                    talkText.setOrigin(textRect.left + textRect.width/2.0f,
                                               0.0f);

                    talkText.setPosition(250.0f, 55.0f);
                    talkText.setString(child->Attribute("value"));
                    talkText.setCharacterSize(40);
                    talkText.setColor(sf::Color::White);

                    triggerShowText = true;
                    clock.restart();
                    currentQuestId++;
                    if (child->Attribute("sound")) {
                        actionSound.openFromFile(std::string("./sounds/") + child->Attribute("sound"));

                        // Play the music
                        actionSound.play();
                    }
                }

            }



		}

	}

	currentQuestText.setFont(font);
	sf::FloatRect textRect = currentQuestText.getLocalBounds();
	currentQuestText.setOrigin(textRect.left + textRect.width/2.0f,
				   0.0f);

	currentQuestText.setPosition(350.0f, 425.0f);
	//currentQuestText.setString(title);
	currentQuestText.setCharacterSize(30);
	currentQuestText.setColor(sf::Color::Yellow);

}
