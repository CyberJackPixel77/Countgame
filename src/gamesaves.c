#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "Countgame.h"
#include <string.h>
#define MAX_LINE_LENGTH 128
#define MAX_FLAG_LENGTH 64


int load_progress(struct gamesaves *p_saved_records) {

	char line[MAX_LINE_LENGTH];
	char flag[MAX_FLAG_LENGTH];
	int VAL;

	FILE* saves = fopen("C:\\Games\\Countgame\\saves.txt", "r");
	if (saves == NULL) return -1;

    while (fgets(line, sizeof(line), saves) != NULL) {
        if (line[0] == '\n') continue;
        if (sscanf(line, "%s = %d", flag, &VAL) == 2) {

            if (strcmp(flag, "GAMES_BEST") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->GAMES_BEST = 0;
                else p_saved_records->GAMES_BEST = VAL;
            }

            else if (strcmp(flag, "ADD_GAMEMODE_BEST") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->ADD_GAMEMODE_BEST = 0;
                else p_saved_records->ADD_GAMEMODE_BEST = VAL;
            }
            else if (strcmp(flag, "SUBST_GAMEMODE_BEST") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->SUBST_GAMEMODE_BEST = 0;
                else p_saved_records->SUBST_GAMEMODE_BEST = VAL;
            }
            else if (strcmp(flag, "MULT_GAMEMODE_BEST") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->MULT_GAMEMODE_BEST = 0;
                else p_saved_records->MULT_GAMEMODE_BEST = VAL;
            }
            else if (strcmp(flag, "DEV_GAMEMODE_BEST") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->DEV_GAMEMODE_BEST = 0;
                else p_saved_records->DEV_GAMEMODE_BEST = VAL;
            }


            else if (strcmp(flag, "ADD_SGM_2X1") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->ADD_SGM_2X1 = 0;
                else p_saved_records->ADD_SGM_2X1 = VAL;
            }
            else if (strcmp(flag, "ADD_SGM_3X2") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->ADD_SGM_3X2 = 0;
                else p_saved_records->ADD_SGM_3X2 = VAL;
            }
            else if (strcmp(flag, "ADD_SGM_3X3") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->ADD_SGM_3X3 = 0;
                else p_saved_records->ADD_SGM_3X3 = VAL;
            }
            else if (strcmp(flag, "ADD_SGM_3X1") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->ADD_SGM_3X1 = 0;
                else p_saved_records->ADD_SGM_3X1 = VAL;
            }


            else if (strcmp(flag, "SUBSTR_SGM_2X1") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->SUBSTR_SGM_2X1 = 0;
                else p_saved_records->SUBSTR_SGM_2X1 = VAL;
            }
            else if (strcmp(flag, "SUBSTR_SGM_3X2") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->SUBSTR_SGM_3X2 = 0;
                else p_saved_records->SUBSTR_SGM_3X2 = VAL;
            }
            else if (strcmp(flag, "SUBSTR_SGM_3X3") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->SUBSTR_SGM_3X3 = 0;
                else p_saved_records->SUBSTR_SGM_3X3 = VAL;
            }
            else if (strcmp(flag, "SUBSTR_SGM_3X1") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->SUBSTR_SGM_3X1 = 0;
                else p_saved_records->SUBSTR_SGM_3X1 = VAL;
            }


            else if (strcmp(flag, "MULT_SGM_2X1") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->MULT_SGM_2X1 = 0;
                else p_saved_records->MULT_SGM_2X1 = VAL;
            }
            else if (strcmp(flag, "MULT_SGM_3X2") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->MULT_SGM_3X2 = 0;
                else p_saved_records->MULT_SGM_3X2 = VAL;
            }
            else if (strcmp(flag, "MULT_SGM_3X3") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->MULT_SGM_3X3 = 0;
                else p_saved_records->MULT_SGM_3X3 = VAL;
            }
            else if (strcmp(flag, "MULT_SGM_3X1") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->MULT_SGM_3X1 = 0;
                else p_saved_records->MULT_SGM_3X1 = VAL;
            }


            else if (strcmp(flag, "DEV_SGM_2X1") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->DEV_SGM_2X1 = 0;
                else p_saved_records->DEV_SGM_2X1 = VAL;
            }
            else if (strcmp(flag, "DEV_SGM_3X2") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->DEV_SGM_3X2 = 0;
                else p_saved_records->DEV_SGM_3X2 = VAL;
            }
            else if (strcmp(flag, "DEV_SGM_3X3") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->DEV_SGM_3X3 = 0;
                else p_saved_records->DEV_SGM_3X3 = VAL;
            }
            else if (strcmp(flag, "DEV_SGM_3X1") == 0) {
                if (VAL < 0 || VAL > 99999999) p_saved_records->DEV_SGM_3X1 = 0;
                else p_saved_records->DEV_SGM_3X1 = VAL;
            }
        }
    }
    fclose(saves);
    return 0;
} 
int write_progress(struct gamesaves *p_saved_records,  int* selected, int* subselected, int* SB) {
    //Defining the records / Îïðåäåëåíèå ðåêîðäîâ
    switch (*selected) {
    case ADDITION:
        switch (*subselected) {
        case TWOxONE:
            if (*SB > p_saved_records->ADD_SGM_2X1) {
                p_saved_records->ADD_SGM_2X1 = *SB;
            }
            break;
        case THREExTWO:
            if (*SB > p_saved_records->ADD_SGM_3X2) {
                p_saved_records->ADD_SGM_3X2 = *SB;
            }
            break;
        case THREExTHREE:
            if (*SB > p_saved_records->ADD_SGM_3X3) {
                p_saved_records->ADD_SGM_3X3 = *SB;
            }
            break;
        case THREExONE:
            if (*SB > p_saved_records->ADD_SGM_3X1) {
                p_saved_records->ADD_SGM_3X1 = *SB;
            }
        }
        int ADD_GBest = 0;
        if (p_saved_records->ADD_SGM_2X1 > ADD_GBest) ADD_GBest = p_saved_records->ADD_SGM_2X1;
        if (p_saved_records->ADD_SGM_3X2 > ADD_GBest) ADD_GBest = p_saved_records->ADD_SGM_3X2;
        if (p_saved_records->ADD_SGM_3X3 > ADD_GBest) ADD_GBest = p_saved_records->ADD_SGM_3X3;
        if (p_saved_records->ADD_SGM_3X1 > ADD_GBest) ADD_GBest = p_saved_records->ADD_SGM_3X1;
        p_saved_records->ADD_GAMEMODE_BEST = ADD_GBest;
        break;
    case SUBSTRACTION:
        switch (*subselected) {
        case TWOxONE:
            if (*SB > p_saved_records->SUBSTR_SGM_2X1) {
                p_saved_records->SUBSTR_SGM_2X1 = *SB;
            }
            break;
        case THREExTWO:
            if (*SB > p_saved_records->SUBSTR_SGM_3X2) {
                p_saved_records->SUBSTR_SGM_3X2 = *SB;
            }
            break;
        case THREExTHREE:
            if (*SB > p_saved_records->SUBSTR_SGM_3X3) {
                p_saved_records->SUBSTR_SGM_3X3 = *SB;
            }
            break;
        case THREExONE:
            if (*SB > p_saved_records->SUBSTR_SGM_3X1) {
                p_saved_records->SUBSTR_SGM_3X1 = *SB;
            }
        }
        int SGMB_Counter = 0;
        if (p_saved_records->SUBSTR_SGM_2X1 > SGMB_Counter) SGMB_Counter = p_saved_records->SUBSTR_SGM_2X1;
        if (p_saved_records->SUBSTR_SGM_3X2 > SGMB_Counter) SGMB_Counter = p_saved_records->SUBSTR_SGM_3X2;
        if (p_saved_records->SUBSTR_SGM_3X3 > SGMB_Counter) SGMB_Counter = p_saved_records->SUBSTR_SGM_3X3;
        if (p_saved_records->SUBSTR_SGM_3X1 > SGMB_Counter) SGMB_Counter = p_saved_records->SUBSTR_SGM_3X1;
        p_saved_records->SUBST_GAMEMODE_BEST = SGMB_Counter;
        break;
    case MULTIPLICATION:
        switch (*subselected) {
        case TWOxONE:
            if (*SB > p_saved_records->MULT_SGM_2X1) {
                p_saved_records->MULT_SGM_2X1 = *SB;
            }
            break;
        case THREExTWO:
            if (*SB > p_saved_records->MULT_SGM_3X2) {
                p_saved_records->MULT_SGM_3X2 = *SB;
            }
            break;
        case THREExTHREE:
            if (*SB > p_saved_records->MULT_SGM_3X3) {
                p_saved_records->MULT_SGM_3X3 = *SB;
            }
            break;
        case THREExONE:
            if (*SB > p_saved_records->MULT_SGM_3X1) {
                p_saved_records->MULT_SGM_3X1 = *SB;
            }
        }
        int MGMB_Counter = 0;
        if (p_saved_records->MULT_SGM_2X1 > MGMB_Counter) MGMB_Counter = p_saved_records->MULT_SGM_2X1;
        if (p_saved_records->MULT_SGM_3X2 > MGMB_Counter) MGMB_Counter = p_saved_records->MULT_SGM_3X2;
        if (p_saved_records->MULT_SGM_3X3 > MGMB_Counter) MGMB_Counter = p_saved_records->MULT_SGM_3X3;
        if (p_saved_records->MULT_SGM_3X1 > MGMB_Counter) MGMB_Counter = p_saved_records->MULT_SGM_3X1;
        p_saved_records->MULT_GAMEMODE_BEST = MGMB_Counter;
        break;
    case DIVISION:
        switch (*subselected) {
        case TWOxONE:
            if (*SB > p_saved_records->DEV_SGM_2X1) {
                p_saved_records->DEV_SGM_2X1 = *SB;
            }
            break;
        case THREExTWO:
            if (*SB > p_saved_records->DEV_SGM_3X2) {
                p_saved_records->DEV_SGM_3X2 = *SB;
            }
            break;
        case THREExTHREE:
            if (*SB > p_saved_records->DEV_SGM_3X3) {
                p_saved_records->DEV_SGM_3X3 = *SB;
            }
            break;
        case THREExONE:
            if (*SB > p_saved_records->DEV_SGM_3X1) {
                p_saved_records->DEV_SGM_3X1 = *SB;
            }
        }
        int DGMB_Counter = 0;
        if (p_saved_records->DEV_SGM_2X1 > DGMB_Counter) DGMB_Counter = p_saved_records->DEV_SGM_2X1;
        if (p_saved_records->DEV_SGM_3X2 > DGMB_Counter) DGMB_Counter = p_saved_records->DEV_SGM_3X2;
        if (p_saved_records->DEV_SGM_3X3 > DGMB_Counter) DGMB_Counter = p_saved_records->DEV_SGM_3X3;
        if (p_saved_records->DEV_SGM_3X1 > DGMB_Counter) DGMB_Counter = p_saved_records->DEV_SGM_3X1;
        p_saved_records->DEV_GAMEMODE_BEST = DGMB_Counter;
        break;
    }
    int GB = 0;
    
    if (p_saved_records->ADD_GAMEMODE_BEST > GB) GB = p_saved_records->ADD_GAMEMODE_BEST;
    if (p_saved_records->SUBST_GAMEMODE_BEST > GB) GB = p_saved_records->SUBST_GAMEMODE_BEST;
    if (p_saved_records->MULT_GAMEMODE_BEST > GB) GB = p_saved_records->MULT_GAMEMODE_BEST;
    if (p_saved_records->DEV_GAMEMODE_BEST > GB) GB = p_saved_records->DEV_GAMEMODE_BEST;
    p_saved_records->GAMES_BEST = GB;

    //Rewriting the file / Çàïèñü â ôàéë
    char full_file_path[300];
    getTempFilePath(full_file_path, sizeof(full_file_path), "bsaves.txt");

    FILE* bsaves = fopen(full_file_path, "w");
    FILE* saves = fopen("C:\\Games\\Countgame\\saves.txt", "w");
    if (saves == NULL || bsaves == NULL) return -1;
    fprintf(saves,
        "GAMES_BEST = %d\n\n"
        "ADD_GAMEMODE_BEST = %d\n"
        "SUBST_GAMEMODE_BEST = %d\n"
        "MULT_GAMEMODE_BEST = %d\n"
        "DEV_GAMEMODE_BEST = %d\n\n"
        "ADD_SGM_2X1 = %d\n"
        "ADD_SGM_3X2 = %d\n"
        "ADD_SGM_3X3 = %d\n"
        "ADD_SGM_3X1 = %d\n\n"
        "SUBSTR_SGM_2X1 = %d\n"
        "SUBSTR_SGM_3X2 = %d\n"
        "SUBSTR_SGM_3X3 = %d\n"
        "SUBSTR_SGM_3X1 = %d\n\n"
        "MULT_SGM_2X1 = %d\n"
        "MULT_SGM_3X2 = %d\n"
        "MULT_SGM_3X3 = %d\n"
        "MULT_SGM_3X1 = %d\n\n"
        "DEV_SGM_2X1 = %d\n"
        "DEV_SGM_3X2 = %d\n"
        "DEV_SGM_3X3 = %d\n"
        "DEV_SGM_3X1 = %d\n",
        p_saved_records->GAMES_BEST,

        p_saved_records->ADD_GAMEMODE_BEST,
        p_saved_records->SUBST_GAMEMODE_BEST,
        p_saved_records->MULT_GAMEMODE_BEST,
        p_saved_records->DEV_GAMEMODE_BEST,

        p_saved_records->ADD_SGM_2X1,
        p_saved_records->ADD_SGM_3X2,
        p_saved_records->ADD_SGM_3X3,
        p_saved_records->ADD_SGM_3X1,

        p_saved_records->SUBSTR_SGM_2X1,
        p_saved_records->SUBSTR_SGM_3X2,
        p_saved_records->SUBSTR_SGM_3X3,
        p_saved_records->SUBSTR_SGM_3X1,

        p_saved_records->MULT_SGM_2X1,
        p_saved_records->MULT_SGM_3X2,
        p_saved_records->MULT_SGM_3X3,
        p_saved_records->MULT_SGM_3X1,

        p_saved_records->DEV_SGM_2X1,
        p_saved_records->DEV_SGM_3X2,
        p_saved_records->DEV_SGM_3X3,
        p_saved_records->DEV_SGM_3X1
    );
    fprintf(bsaves,
        "GAMES_BEST = %d\n\n"
        "ADD_GAMEMODE_BEST = %d\n"
        "SUBST_GAMEMODE_BEST = %d\n"
        "MULT_GAMEMODE_BEST = %d\n"
        "DEV_GAMEMODE_BEST = %d\n\n"
        "ADD_SGM_2X1 = %d\n"
        "ADD_SGM_3X2 = %d\n"
        "ADD_SGM_3X3 = %d\n"
        "ADD_SGM_3X1 = %d\n\n"
        "SUBSTR_SGM_2X1 = %d\n"
        "SUBSTR_SGM_3X2 = %d\n"
        "SUBSTR_SGM_3X3 = %d\n"
        "SUBSTR_SGM_3X1 = %d\n\n"
        "MULT_SGM_2X1 = %d\n"
        "MULT_SGM_3X2 = %d\n"
        "MULT_SGM_3X3 = %d\n"
        "MULT_SGM_3X1 = %d\n\n"
        "DEV_SGM_2X1 = %d\n"
        "DEV_SGM_3X2 = %d\n"
        "DEV_SGM_3X3 = %d\n"
        "DEV_SGM_3X1 = %d\n",
        p_saved_records->GAMES_BEST,

        p_saved_records->ADD_GAMEMODE_BEST,
        p_saved_records->SUBST_GAMEMODE_BEST,
        p_saved_records->MULT_GAMEMODE_BEST,
        p_saved_records->DEV_GAMEMODE_BEST,

        p_saved_records->ADD_SGM_2X1,
        p_saved_records->ADD_SGM_3X2,
        p_saved_records->ADD_SGM_3X3,
        p_saved_records->ADD_SGM_3X1,

        p_saved_records->SUBSTR_SGM_2X1,
        p_saved_records->SUBSTR_SGM_3X2,
        p_saved_records->SUBSTR_SGM_3X3,
        p_saved_records->SUBSTR_SGM_3X1,

        p_saved_records->MULT_SGM_2X1,
        p_saved_records->MULT_SGM_3X2,
        p_saved_records->MULT_SGM_3X3,
        p_saved_records->MULT_SGM_3X1,

        p_saved_records->DEV_SGM_2X1,
        p_saved_records->DEV_SGM_3X2,
        p_saved_records->DEV_SGM_3X3,
        p_saved_records->DEV_SGM_3X1
    );
    fclose(saves);
    fclose(bsaves);
    return 0;
}
