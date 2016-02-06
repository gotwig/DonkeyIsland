#include "gamescene.h"


GameScene::GameScene()
{


}

void GameScene::Update(int currentQuestid)
{
}

void GameScene::setName(const std::string &Name) {
    GameScene::Name = Name;
}

void GameScene::setBgPath(const std::string &bgPath) {
	GameScene::bgPath = bgPath;

	if (bgTex.loadFromFile(bgPath)) {
		bgSprite.setTexture(bgTex);
	}

}

void GameScene::addEnt(int id, std::string texPath, float x, float y) {
		sf::Texture *newTexture = new sf::Texture;

		elementTemplate = {id, sf::Sprite(), sf::Texture(*newTexture), texPath, 200.0f, 200.0f};

		if (newTexture->loadFromFile(std::string("entTex/") + texPath)) {
			elementTemplate.Sprite.setTexture(*newTexture);
			elementTemplate.Sprite.setPosition(x, y);
		}

		currentEntities.push_back(elementTemplate);
		currentEntities.back().id = id;
		
	}

void GameScene::delEnt(int id) {
	currentEntities.erase(std::remove_if(currentEntities.begin(), currentEntities.end(), [=](auto& entity) { return entity.id == id; }), currentEntities.end());
}
