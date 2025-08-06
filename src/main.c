#include <stdio.h>
#include "Countgame.h"

int main() {
	int filecheck = pre_game_check();
	if (filecheck == NO_SUCH_FILE) return 1;
	else if (filecheck == FILES_CORRUPTED) return 1;
	int countgame = setup_countgame();
	if (countgame == -1) {
		return -1;
	}
	return 0;
}
