#include "WanderingGhost.h"

void WanderingGhost::changeDir() {
	int dir = getRandomInRange(1, 4);
	switch (dir) {
	case 1:
		dirx = 0;
		diry = 1;
		break;
	case 2:
		dirx = 0;
		diry = -1;
		break;
	case 3:
		dirx = 1;
		diry = 0;
		break;
	case 4:
		dirx = -1;
		diry = 0;
		break;
	}
}

void WanderingGhost::move() {
	Ghost::moveGhost(dirx, diry);
	stepsCounter++;

	if (stepsCounter == 3) {
		changeDir();
		stepsCounter = 1;
	}
}