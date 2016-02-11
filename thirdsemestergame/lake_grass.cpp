//
//
//

#include "lake_grass.h"

LakeGrass::LakeGrass() {
    setName("lake_grass");
    setBgPath("bg.png");
	setLvlSound("lakegrass.ogg");
    addEnt(1, "hay.png", 140, 150);
    addEnt(2, "sign_bird.png", 500, -20);

}

void LakeGrass::Update(int currentQuestid)
{
}