#include "WanderingGhost.h"

void WanderingGhost::changeDir() {
	int dir = getRandomInRange(1, 4);
	setDir(dir);
}

void WanderingGhost::setDir(int _dir) {
	switch (_dir) {
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

int WanderingGhost::getDir() {
	if (dirx == 0 && diry == 1) return 1;
	if (dirx == 0 && diry == -1) return 2;
	if (dirx == 1 && diry == 0) return 3;
	if (dirx == -1 && diry == 0) return 4;
}


void WanderingGhost::move() {
	Ghost::moveGhost(dirx, diry);
	stepsCounter++;

	if (stepsCounter == 3) {
		changeDir();
		stepsCounter = 1;
	}
}