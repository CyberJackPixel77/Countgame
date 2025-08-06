#ifndef COUNTGAME_H
#define COUNTGAME_H
#define ADDITION 0
#define SUBSTRACTION 1
#define MULTIPLICATION 2
#define DIVISION 3
#define TWOxONE 0
#define THREExTWO 1
#define THREExTHREE 2
#define THREExONE 3
#define NO_SUCH_FILE 9
#define FILES_CORRUPTED 8
#include <stddef.h>

//COUNTGAME_C
int setup_countgame();

//FILECHECK_C
typedef enum {
	INFO = 0,
	ERR = 1,
	WARNING = 2
} logStatus;
void getTempFilePath(char* output, size_t outputSize, const char* fileName);
void logger(logStatus  status, const char* info);
int pre_game_check();


//GAMESAVES_C
struct gamesaves {
	int GAMES_BEST;

	int ADD_GAMEMODE_BEST;
	int SUBST_GAMEMODE_BEST;
	int MULT_GAMEMODE_BEST;
	int DEV_GAMEMODE_BEST;

	int ADD_SGM_2X1;
	int ADD_SGM_3X2;
	int ADD_SGM_3X3;
	int ADD_SGM_3X1;

	int SUBSTR_SGM_2X1;
	int SUBSTR_SGM_3X2;
	int SUBSTR_SGM_3X3;
	int SUBSTR_SGM_3X1;

	int MULT_SGM_2X1;
	int MULT_SGM_3X2;
	int MULT_SGM_3X3;
	int MULT_SGM_3X1;

	int DEV_SGM_2X1;
	int DEV_SGM_3X2;
	int DEV_SGM_3X3;
	int DEV_SGM_3X1;
}; //Ñîçäàíèå áàçèñà
int load_progress(struct gamesaves* p_saved_records);
int write_progress(struct gamesaves* p_saved_records, int* selected, int* subselected, int* SB);

#endif
