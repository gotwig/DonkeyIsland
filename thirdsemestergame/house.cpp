//
//
//

#include "house.h"

House::House() {
    setName("house");
    setBgPath("bg_house.png");
    addEnt(1, "cat_sad.png", 550, 100);
    //addEnt(2, "cat_happy.png", 10, 340);
	addEnt(3, "girl_sad.png", 220, 210);
	//addEnt(4, "girl_happy.png", 550, 100);

	addEnt(5, "ladder_mountain.png", 30, 220);
	
}

void House::Update(int currentQuestid)
{
	if (currentQuestid != previousQuestid) {

		if (currentQuestid == 4) {
			addEnt(6, "ladder_vertical.png", 600, 240);
		}

		if (currentQuestid == 5) {
			delEnt(1);
			delEnt(3);
			addEnt(2, "cat_happy.png", 10, 340);
			addEnt(4, "girl_happy.png", 150, 250);
		}

	}

	previousQuestid = currentQuestid;

}
