#include "flower.h"

flower::flower() {
	setName("flower");
	setBgPath("bg_flower.png");

	setLvlSound("flower.ogg");

	addEnt(1, "vaultboy_start.png", 215, 235);
	addEnt(2, "watercan.png", 500, 300);
	addEnt(3, "flower_start.png", 30, 220);

}

void flower::Update(int currentQuestid)
{
	if (currentQuestid != previousQuestid) {

		if (currentQuestid == 5) {
			delEnt(1);
			delEnt(3);
			addEnt(4, "vaultboy_finish.png", 212, 142);
			addEnt(5, "flower_growed.png", 20, 150);
		}

	}

	previousQuestid = currentQuestid;

}
