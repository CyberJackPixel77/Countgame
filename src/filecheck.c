#define _CRT_SECURE_NO_WARNINGS
#include "countgame.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <errno.h>
#include <io.h>
#include <direct.h>
#include <Windows.h>
#include <time.h>
//REVERSE CODES
// 0 - code copleted with success,
// 1 - logical error/exceprion.
static int skipchkcheat = 0;
const char* statustostring(logStatus status) {
	switch (status) {
	case INFO: return "INFO";
	case ERR: return "ERROR";
	case WARNING: return "WARNING";
	default: return "UNKNOWN";
	}
}
void logger(logStatus  status, const char* info) {
	time_t rawTime;
	struct tm* timeInfo;
	char timeStr[20];
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeInfo);
	FILE* log = fopen("C:\\Games\\Countgame\\logger.txt", "a");
	if (!log) {
		printf("LOGGER ERROR: Cannot open file. Message: [%s] %s\n", statustostring(status), info);
		return;
	}
	fprintf(log, "[%s] [%s] %s\n", timeStr, statustostring(status), info);
	fclose(log);
}
void getTempFilePath(char* output, size_t outputSize, const char* fileName) {
	char tempDir[300];
	GetTempPathA(sizeof(tempDir), tempDir);
	snprintf(output, outputSize, "%s%s", tempDir, fileName);
}
int chkfls() {
	//Checking the existance of gamefiles / Ïðîâåðêà ôàéëîâ íà íàëè÷èå (îïòèìèçàöèÿ)
	char full_file_path[300];
	getTempFilePath(full_file_path, sizeof(full_file_path), "bsaves.txt");

	FILE* saves = fopen("C:\\Games\\Countgame\\saves.txt", "r");
	FILE* bsaves = fopen(full_file_path, "r");

	if (saves == NULL || bsaves == NULL) {
		return 1;
	}
	if (saves != NULL) fclose(saves);
	if (bsaves != NULL) fclose(bsaves);
	logger(0, "Files verified");
	return 0;
}
int chkcheat() {
	char full_file_path[300];
	getTempFilePath(full_file_path, sizeof(full_file_path), "bsaves.txt");
	const char* savepath = "C:\\Games\\Countgame\\saves.txt";
	const char* backupsaves = full_file_path;

	//Checking files for coincidence / Ïðîâåðêà êîððåêòíîñòè çàïèñè ôàéëîâ, ïðîâåðêà íà èçìåíåíèÿ
	FILE* f1 = fopen(savepath, "rb");
	FILE* f2 = fopen(backupsaves, "rb");
	if (!f1 || !f2) {
		if (f1) fclose(f1);
		if (f2) fclose(f2);
		return -1;
	}
	int c1, c2;
	do {
		c1 = fgetc(f1);
		c2 = fgetc(f2);
		if (c1 != c2) {
			fclose(f1);
			fclose(f2);
			return -1;
		}
	} while (c1 != EOF && c2 != EOF);
	fclose(f1);
	fclose(f2);
	return (c1 == EOF && c2 == EOF) ? 0 : -1;
}
int chkdir() {
	const char pathtogames[50] = "C:\\Games";
	const char fullpath[100] = "C:\\Games\\Countgame";
	if (_access(pathtogames, 0) != 0) {
		logger(1, "C:\\Games directiry not found, CANNOT EXECUTE WITHOUT 'C:\\Games' DIRECTORY...");
		printf("FAILED: CANNOT EXECUTE WITHOUT 'C:\\Games' DIRECTORY...");
		return 1;
	}
	if (_access(fullpath, 0) != 0) {
		char full_file_path[300];
		getTempFilePath(full_file_path, sizeof(full_file_path), "bsaves.txt");
		/*
		* We have already checked existence if backup save and judging that we've got here, seems like we DO NOT have it. There is no need to check TEMP path.
		* If there if no 'Countgame' folder, that means that it's new game. 
		  / 
		  Ìû óæå ïðîâåðÿëè íàëè÷èå ôàéëà áýêàïà è ó÷èòûâàÿ ÷òî ìû ïîïàëè ñþäà, 
		  ìîæíî ñäåëàòü âûâîä ÷òî åãî íåò.Ïàïêó òåìï ïðîâåðÿòü íåò ñìûñëà íà íàëè÷èå, îíà åñòü. 
		  Çíà÷èò åñëè íåò ïàïêè Countgame, òî ýòî íîâàÿ èãðà. 
		  Ñîçäà¸ì âñå ïàïêè è âñå íåîáõîäèìûå ôàéëû.
		*/
		if (_mkdir(fullpath) != 0) {
			printf("FAILED: Failed to create folder 'C:\\Games\\Countgame...");
			return 1;
		}
		FILE* saves = fopen("C:\\Games\\Countgame\\saves.txt", "w");
		FILE* bsaves = fopen(full_file_path, "w");
		if (saves == NULL || bsaves == NULL) {
			logger(1, "Unable to load save files :(");
			return 1;
		}
		//For great readability
		fprintf(saves,
			"GAMES_BEST = 0\n\n"
			"ADD_GAMEMODE_BEST = 0\n"
			"SUBST_GAMEMODE_BEST = 0\n"
			"MULT_GAMEMODE_BEST = 0\n"
			"DEV_GAMEMODE_BEST = 0\n\n"
			"ADD_SGM_2X1 = 0\n"
			"ADD_SGM_3X2 = 0\n"
			"ADD_SGM_3X3 = 0\n"
			"ADD_SGM_3X1 = 0\n\n"
			"SUBSTR_SGM_2X1 = 0\n"
			"SUBSTR_SGM_3X2 = 0\n"
			"SUBSTR_SGM_3X3 = 0\n"
			"SUBSTR_SGM_3X1 = 0\n\n"
			"MULT_SGM_2X1 = 0\n"
			"MULT_SGM_3X2 = 0\n"
			"MULT_SGM_3X3 = 0\n"
			"MULT_SGM_3X1 = 0\n\n"
			"DEV_SGM_2X1 = 0\n"
			"DEV_SGM_3X2 = 0\n"
			"DEV_SGM_3X3 = 0\n"
			"DEV_SGM_3X1 = 0\n");
		fprintf(bsaves,
			"GAMES_BEST = 0\n\n"
			"ADD_GAMEMODE_BEST = 0\n"
			"SUBST_GAMEMODE_BEST = 0\n"
			"MULT_GAMEMODE_BEST = 0\n"
			"DEV_GAMEMODE_BEST = 0\n\n"
			"ADD_SGM_2X1 = 0\n"
			"ADD_SGM_3X2 = 0\n"
			"ADD_SGM_3X3 = 0\n"
			"ADD_SGM_3X1 = 0\n\n"
			"SUBSTR_SGM_2X1 = 0\n"
			"SUBSTR_SGM_3X2 = 0\n"
			"SUBSTR_SGM_3X3 = 0\n"
			"SUBSTR_SGM_3X1 = 0\n\n"
			"MULT_SGM_2X1 = 0\n"
			"MULT_SGM_3X2 = 0\n"
			"MULT_SGM_3X3 = 0\n"
			"MULT_SGM_3X1 = 0\n\n"
			"DEV_SGM_2X1 = 0\n"
			"DEV_SGM_3X2 = 0\n"
			"DEV_SGM_3X3 = 0\n"
			"DEV_SGM_3X1 = 0\n");
		fclose(saves);
		fclose(bsaves);
		skipchkcheat++;
		logger(0, "New game detected");
	}
	else {
		logger(1, "Files are missing in existed direcroty...");
		printf("FAILED: No saves files found...");
		return 1;
	}
	logger(0, "Directory check successfull");
	return 0;
	
}
int pre_game_check() {
	if (chkfls() != 0) {
		//No files / Ôàéëîâ íåò
		if (chkdir() != 0) {
			return NO_SUCH_FILE;
		}
	}
	if (skipchkcheat == 0) {
		//If NOT new game, then check coincidence / Åñëè íå íîâàÿ èãðà, òî ïðîâåðÿåì ñîâïàäåíèå
		if (chkcheat() != 0) {
			//If not the same - block / Åñëè ôàéëû íå ñîâïàäàþò, áëîê.
			logger(1, "Files are currupted, or cheat detected.");
			printf("CHKCHT: Game Files currupted. Touch some grass, cheater.\nGame will not start...");
			return FILES_CORRUPTED;
		}
	}
	logger(0, "Game ready to start.");
	return 0;
}
