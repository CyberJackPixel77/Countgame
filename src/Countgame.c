#define _CRT_SECURE_NO_WARNINGS
#include "Countgame.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>

/*  Comments:
*  ENG / RUS
*  This code might be not perfect, cuz its my first ever C project. I'll try my best to improve my C-skills in coding)
*
*/
#define MAXLEN 10 //Length of custom_scanf line / Äëèíà ïîëÿ ââîäà â custom_scanf
#define ESC_BUTTON 27 //ASCII code of ESC button / Êîä êëàâèøè ESC
#define BACKSPACE_BUTTON 8 //ASCII code of BACKSPACE button / Êîä êëàâèøè óäàëåíèÿ ñèìâîëà
#define ENTER_BUTTON 13 //ASCII code of ENTER button / Êîä êëàâèøè ENTER
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define EPSILON 0.0001

#define MAX_ACTIVE_EXAMPLES 6
#define MAX_LINE_LENGTH 64
#define X_COORD_ANIMATE 49
#define Y_COORD_ANIMATE 16

struct Example {
    char text[MAX_LINE_LENGTH];
    int active;
};
struct Example examples[MAX_ACTIVE_EXAMPLES];



//Animation / Àíèìàöèÿ ---------------------------------------------
void gotoxy(int x, int y) {
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void animatelogo() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        printf("Error: Cannot get console handle\n");
        logger(1, "Cannot get CONSOLE HANDLE!");
        return;
    }
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
	int y = -0;
	while (y <= 10) {
		system("cls");
		int x = 26;
		gotoxy(x-3, y);
		printf("/========================================================================\\\n");
		gotoxy(x - 3, y+1);
		printf("|                                                                        |");
		gotoxy(x-3, y + 2);
		printf("|  /====+   /==+   /   |  |+   + =--+--=  /===+    /+     |+  /|  /===+  |\n");
		gotoxy(x-3, y + 3);
		printf("|  |       |    |  |   |  | +  |    |    |        /  +    | +/ | |____+  |\n");
		gotoxy(x-3, y + 4);
		printf("|  |       |    |  |   |  |  + |    |    |   -|  /====+   |    | |       |\n");
		gotoxy(x-3, y + 5);
		printf("|  +====/   +==/   +===+  +   +|    |     \\===/ /      +  |    |  \\===+  |\n");
		gotoxy(x - 3, y + 6);
		printf("|                                                                        |");
		gotoxy(x-3, y + 7);
		printf("\\========================================================================/\n");
		gotoxy(x - 3, y + 9);
		Sleep(100);
		y++;
	}
}
void showpressenter(int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        logger(1, "Cannot get console handle!");
        return;
    }
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int blinkState = 0; // 0 - Black back, 1 - White Back
    int iteration = 0;  // Itterations counter (1 sec)

    while (1) {
        gotoxy(56, y + 12);
        if (blinkState) {
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        }
        else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        printf("PRESS ENTER");
        fflush(stdout);

        Sleep(500);
        iteration++;
        if (iteration % 2 == 0) {
            blinkState = !blinkState;
        }

        if (_kbhit()) {
            int key = _getch();
            if (key == 13) {
                break;
            }
        }
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void handlepressenter(int y) {
    int a = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        printf("Error: Cannot get console handle\n");
        logger(1, "Cannot get console handle");
        return;
    }
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int blinkState = 0; //basically the same that was in older func)
    int iteration = 0;

    while (a < 13) {
        gotoxy(56, y + 12);
        if (blinkState) {
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        }
        else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        printf("PRESS ENTER");
        fflush(stdout);

        Sleep(50);
        iteration++;
        if (iteration % 2 == 0) {
            blinkState = !blinkState;
        }
        a++;
    }
}



//Main and submenu / Ãëàâíîå è ïîäìåíþ ------------------------------------
//MMU - Main Menu UPPER

//Global variables / Ãëîáàëüíûå ïåðåìåííûå 
int selected = 0;
int subselected = 0;
int special_code = 0; // 1 - Gamemode selected, 0 - Gamemode default
int answer;

//Pre-Game functions / Äî èãðîâûå ôóíêöèè
void checklang() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1) {
        DWORD threadId = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
        HKL keyboardLayout = GetKeyboardLayout(threadId);
        if (LOWORD(keyboardLayout) == 0x0409) {
            FlushConsoleInputBuffer(hConsole);
            system("cls");
            gotoxy(0, 0);
            break;
        }
        system("cls");
        gotoxy(20, 10);
        printf("/==================================================================================\\\n");
        gotoxy(20, 11);
        printf("|                                                                                  |\n");
        gotoxy(20, 12);
        printf("|                               <---- ATTENTION ---->                              |\n");
        gotoxy(20, 13);
        printf("|                  Countgame supports only ENGLISH keyboard layout.                |\n");
        gotoxy(20, 14);
        printf("|                     Please switch to ENG to continue playing.                    |\n");
        gotoxy(20, 15);
        printf("|                   If this message dont fade away, switch to ENG                  |\n");
        gotoxy(20, 16);
        printf("|                     and open any other window, that will help.                   |\n");
        gotoxy(20, 17);
        printf("|                                                                                  |\n");
        gotoxy(20, 18);
        printf("\\==================================================================================/");
        fflush(stdout);
        Sleep(200);
    }
}


//Drawing-Functions / Ôóíêöèè îòðèñîâêè
void printmainmenu() {
    printf("/======================================================================================================================\\\n");
    printf("|                                                                                                                      |\n");
    printf("|                                            -----Select gaming mode-----                                              |\n");
    printf("|                                                          |                                                           |\n");
    printf("|                     ++ ADDITION ++                       |                     -- SUBTRACTION --                     |\n");
    printf("|                                                          |                                                           |\n");
    printf("|                                                          |                                                           |\n");
    printf("|          +- Two digit plus One digit       (2 X 1)       |          +- Two digit minus One digit       (2 X 1)       |\n");
    printf("|          |                                               |          |                                                |\n");
    printf("|          +- Three digit plus Two digit     (3 X 2)       |          +- Three digit minus Two digit     (3 X 2)       |\n");
    printf("|          |                                               |          |                                                |\n");
    printf("|          +- Three digit plus Three digit   (3 X 3)       |          +- Three digit minus Three digit   (3 X 3)       |\n");
    printf("|          |                                               |          |                                                |\n");
    printf("|          +- Three digit plus One digit     (3 X 1)       |          +- Three digit minus One digit     (3 X 1)       |\n");
    printf("|                                                          |                                                           |\n");
    printf("|  ------------------------------------------------------  +  -------------------------------------------------------  |\n");
    printf("|                                                          |                                                           |\n");
    printf("|                  ** MULTIPLICATION **                    |                      // DIVISION //                       |\n");
    printf("|                                                          |                                                           |\n");
    printf("|          +- Two digit multiplied by One digit     (2 X 1)|          +- Two digit divided by One digit       (2 X 1)  |\n");
    printf("|          |                                               |          |                                                |\n");
    printf("|          +- Three digit multiplied by Two digit   (3 X 2)|          +- Three digit divided by Two digit     (3 X 2)  |\n");
    printf("|          |                                               |          |                                                |\n");
    printf("|          +- Three digit multiplied by Three digit (3 X 3)|          +- Three digit divided by Three digit   (3 X 3)  |\n");
    printf("|          |                                               |          |                                                |\n");
    printf("|          +- Three digit multiplied by One digit   (3 X 1)|          +- Three digit divided by One digit     (3 X 1)  |\n");
    printf("|                                                          |                                                           |\n");
    printf("|        TIP: Make sure that you resized your window size to 120 X 30 symbols to get proper screen resolution          |\n");
    printf("|                  Press 'H' to get help                                Press 'R' to read game rules                   |\n");
    printf("\\======================================================================================================================/");
}
void showhelp() {
    printf("/======================================================================================================================\\\n");
    printf("|                                                                                                                      |\n");
    printf("|                                                  WELCOME TO COUNTGAME!                                               |\n");
    printf("|          Use ARROWS in main menu to select needed gamemode. White coursor of current gamemode will be showed         |\n");
    printf("|          next to game menu like that ' _ ++ ADDITION ++ '.To confirm changes - press ENTER key,discard - ESC         |\n");
    printf("|          Remember, when you're in main menu , pressing ESC will lead to the game termination. Only when you're       |\n");
    printf("|          in sub-menu (or help menu), that will discard changes and return you to Main menu mode selection.           |\n");
    printf("|          Do not touch or corrupt any game saves, this will lead to game freeze. In this condition the only           |\n");
    printf("|          way to continue playing will be full game deletion. For that go to 'C:\\Games' and delete 'Countgame'        |\n");
    printf("|          folder, also make sure to delete 'bsaves.txt' file in Temp folder, or that will not work.                   |\n");
    printf("|                                                                                                                      |\n");
    printf("\\======================================================================================================================/");

}
void showrules() {
    printf("/======================================================================================================================\\\n");
    printf("|                                           <  COUNTGAME RULES  >                                                      |\n");
    printf("|     GAME BASICS, 'About menu':                                                                                       |\n");
    printf("|      Countgame contains various gamemodes, like ADDITION, SUBSTRACTION, MULTIPLICATION, DIVISION. Each gamemode      |\n");
    printf("|      contains 4 mode gamemodes. Gamemodes described in game's menu, and with 2 digits code near them (like '2 X 1')  |\n");
    printf("|      This short description means 'How many digits will be in first and second number'. Upper constant means         |\n");
    printf("|      'two digit number and one digit number', the exact operation of what to do with that numbers you can select in  |\n");
    printf("|      main menu (or 1st line of rules, or just read a little bit left from short desc in main menu).                  |\n");
    printf("|                                                                                                                      |\n");
    printf("|     GAME BASICS, 'Personal best'                                                                                     |\n");
    printf("|      Each Countgame gamemode has 4 'personal best' counters. All of them will be showed near upper edge of a screen  |\n");
    printf("|      when you start playing. First one, is 'Session best =' that number means 'How many times you answered correctly |\n");
    printf("|      in this gamemode in THIS SESSION'. After you exit to main menu, that record will be reset to 0 again. If you    |\n");
    printf("|      answer incorrect, game will tell you that, and freeze your record untill you finally beat it, after that it     |\n");
    printf("|      starts count again (from your last best). Second 'Subgamemode best =' means 'What was your best strike in that  |\n");
    printf("|      subgamemode from submenu?' (Like 'Multiplication 3 X 1'). That record will be saved in game saves and WONT BE   |\n");
    printf("|      RESET until you'll uninstall the game (read 'Help' to know how exactly do that). Third one is 'Gamemode best =' |\n");
    printf("|      that one means 'What was your best strike in ALL of subgamemodes at all'. This record is also saved in game     |\n");
    printf("|      files and will be unique for each gamemode (1st line. Will set to 0 if never played). The last record  -        |\n");
    printf("|      'Game's best =' means 'What was your best strike in ALL OF GAMEMODES?' This option will set to 0 if you NEVER   |\n");
    printf("|      PLAYED the game (or just reinstalled it), also stored in game's save files.                                     |\n");
    printf("|                                                                                                                      |\n");
    printf("|     GAME BASICS, 'How to play?'                                                                                      |\n");
    printf("|      Very easy. Game will give you math statements that you need to solve. Just write down the correct answer and    |\n");
    printf("|      beat your own records. To exit to main menu press 'ESC' and then select 'Yes', thats all. Enjoy.                |\n");
    printf("|     ADVANCED INFO, 'Anti-cheat system'                                                                               |\n");
    printf("|      Game is secured with anti-cheat system. If it will detect game files corruption, game WILL NEVER START untill   |\n");
    printf("|      you reinstall game, or return your last save file back. Game logs written in 'Countgame' folder, logger.txt     |\n");
    printf("|      file.                                                                                                           |\n");
    printf("\\======================================================================================================================/");
}
void showgameback(int SB, int* selected, int* subselected, struct gamesaves *p_saved_records) {
    int SGB = 0;
    int GB = 0;
    switch (*selected) {
    case ADDITION: {

        GB = p_saved_records->ADD_GAMEMODE_BEST;

        switch (*subselected) {
        case TWOxONE:
            SGB = p_saved_records->ADD_SGM_2X1;
            break;
        case THREExTWO:
            SGB = p_saved_records->ADD_SGM_3X2;
            break;
        case THREExTHREE:
            SGB = p_saved_records->ADD_SGM_3X3;
            break;
        case THREExONE:
            SGB = p_saved_records->ADD_SGM_3X1;
            break;
        }
        break;
    }
    case SUBSTRACTION: {

        GB = p_saved_records->SUBST_GAMEMODE_BEST;

        switch (*subselected) {
        case TWOxONE:
            SGB = p_saved_records->SUBSTR_SGM_2X1;
            break;
        case THREExTWO:
            SGB = p_saved_records->SUBSTR_SGM_3X2;
            break;
        case THREExTHREE:
            SGB = p_saved_records->SUBSTR_SGM_3X3;
            break;
        case THREExONE:
            SGB = p_saved_records->SUBSTR_SGM_3X1;
            break;
        }
        break;
    }
    case MULTIPLICATION: {

        GB = p_saved_records->MULT_GAMEMODE_BEST;

        switch (*subselected) {
        case TWOxONE:
            SGB = p_saved_records->MULT_SGM_2X1;
            break;
        case THREExTWO:
            SGB = p_saved_records->MULT_SGM_3X2;
            break;
        case THREExTHREE:
            SGB = p_saved_records->MULT_SGM_3X3;
            break;
        case THREExONE:
            SGB = p_saved_records->MULT_SGM_3X1;
            break;
        }
        break;
    }
    case DIVISION: {

        GB = p_saved_records->DEV_GAMEMODE_BEST;

        switch (*subselected) {
        case TWOxONE:
            SGB = p_saved_records->DEV_SGM_2X1;
            break;
        case THREExTWO:
            SGB = p_saved_records->DEV_SGM_3X2;
            break;
        case THREExTHREE:
            SGB = p_saved_records->DEV_SGM_3X3;
            break;
        case THREExONE:
            SGB = p_saved_records->DEV_SGM_3X1;
            break;
        }
        break;
       }
    }
    printf("/======================================================================================================================\\\n");
    printf("|   _______________________________________________________________________________________________________________    |\n");
    printf("|  /                                                                                                               \\   |\n");
    printf("|           +                                                                                              +           |\n");      
    printf("|           |                                                                                              |           |\n");
    printf("|           |    \\___________________________________________________________________________________/     |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |    \\____________________________________________________________________________________/    |           |\n");
    printf("|           |                                                                                              |           |\n");
    printf("|           |               /***\\  /===\\  |    \\  |\\   | (=\\=/=)  /===\\   /\\   /\\ /\\  /---]                |           |\n");
    printf("|           |               [      [   ]  |    |  | \\  |    |    |   _   /_|   | * |  |---|                |           |\n");
    printf("|           |               \\___/  \\___/  \\____/  |  \\-|    |     \\___/ /  |\\  \\   /  \\---]                |           |\n");
    printf("|                                                                                                                      |\n");
    printf("|  \\_______________________________________________________________________________________________________________/   |\n");
    printf("|      Session best =  %-6d      Subgamemode best = %-6d       Gamemode best = %-6d          Game's best = %-6d|\n", SB, SGB, GB, p_saved_records->GAMES_BEST);
    printf("|                                                                                                                      |\n");
    printf("\\======================================================================================================================/");
}
void printexitmenu() {
    int Ey = 9;
    int Ex = 15;
    gotoxy(Ex, Ey++);
    printf(" _________________________________________________________________________________________\n");
    gotoxy(Ex, Ey++);
    printf("/                                                                                         \\\n");
    gotoxy(Ex, Ey++);
    printf("|                                                                                         |\n");
    gotoxy(Ex, Ey++);
    printf("|                                                                                         |\n");
    gotoxy(Ex, Ey++);
    printf("|                        Do you really want to exit to main menu?                         |\n");
    gotoxy(Ex, Ey++);
    printf("|                                                                                         |\n");
    gotoxy(Ex, Ey++);
    printf("|                                                                                         |\n");
    gotoxy(Ex, Ey++);
    printf("|                          Yes                  No, I'll continue                         |\n");
    gotoxy(Ex, Ey++);
    printf("|                                                                                         |\n");
    gotoxy(Ex, Ey++);
    printf("|                                                                                         |\n");
    gotoxy(Ex, Ey++);
    printf("\\_________________________________________________________________________________________/\n");
}


//Main Menu Functions / Ôóíêöèè ðàáîòû ìåíþ
void highlightmenu(int selected) {
    if (selected == 0) {
        gotoxy(20, 4);
    }
    else if (selected == 1) {
        gotoxy(79, 4);
    }
    else if (selected == 2) {
        gotoxy(17, 17);
    }
    else if (selected == 3) {
        gotoxy(79, 17);
    }
}
void selectsubmenu(int selected, int subselected) {
    switch (selected) {
    case 0:
        gotoxy(9, 7);
        switch (subselected) {
        case 0:
            gotoxy(9, 7);
            break;
        case 1:
            gotoxy(9, 9);
            break;
        case 2:
            gotoxy(9, 11);
            break;
        case 3:
            gotoxy(9, 13);
            break;
        }
        break;
    case 1:
        gotoxy(68, 7);
        switch (subselected) {
        case 0:
            gotoxy(68, 7);
            break;
        case 1:
            gotoxy(68, 9);
            break;
        case 2:
            gotoxy(68, 11);
            break;
        case 3:
            gotoxy(68, 13);
            break;
        }
        break;
    case 2:
        gotoxy(9, 19);
        switch (subselected) {
        case 0:
            gotoxy(9, 19);
            break;
        case 1:
            gotoxy(9, 21);
            break;
        case 2:
            gotoxy(9, 23);
            break;
        case 3:
            gotoxy(9, 25);
            break;
        }
        break;
    case 3:
        gotoxy(68, 19);
        switch (subselected) {
        case 0:
            gotoxy(68, 19);
            break;
        case 1:
            gotoxy(68, 21);
            break;
        case 2:
            gotoxy(68, 23);
            break;
        case 3:
            gotoxy(68, 25);
            break;
        }
        break;
    }
}
int mmugetcoursor(int x, int y) {
    //Hide cursor / Ñêðûâàåì êóðñîð
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        printf("Error: Cannot get console handle\n");
        logger(1, "Cannot get console handle");
        return -1;
    }
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int insubmenu = 0;
    printmainmenu();
    if (insubmenu == 0) {
        highlightmenu(selected);
    }
    //Loop of flashing + enter / Öèêë ìèãàíèÿ + ñ÷èòûâàíèÿ
    while (1) {
        //Getting keys / Ñ÷èòûâàíèÿ êëàâèø è äåéñòâèÿ
        if (_kbhit()) {
            int key = _getch();
            if (key == 0 || key == 224) { //Ñïåöêëàâèøè
                key = _getch();
                switch (key) {
                case 72: // Ñòðåëêà ââåðx
                    if (insubmenu == 0) {
                        if (selected == 1) selected = 0;
                        else if (selected == 3) selected = 1;
                        else if (selected == 2) selected = 0;
                    }
                    else {
                        if (subselected > 0) {
                            subselected--;
                            system("cls");
                            printmainmenu();
                            selectsubmenu(selected, subselected);
                        }
                    }
                    break;
                case 80: // Ñòðåëêà âíèç
                    if (insubmenu == 0) {
                        if (selected == 0) selected = 2;
                        else if (selected == 1) selected = 3;
                    }
                    else {
                        //insubmenu == 1
                        if (subselected < 3) {
                            subselected++;
                            system("cls"); // Ïåðåðèñîâûâàåì
                            printmainmenu(); // Ôîí ìåíþ
                            selectsubmenu(selected, subselected);
                        }
                    }
                    break;
                case 75: // Ñòðåëêà âëåâî
                    if (selected == 1 && insubmenu == 0) selected = 0;
                    else if (selected == 3 && insubmenu == 0) selected = 2;
                    break;
                case 77: // Ñòðåëêà âïðàâî
                    if (selected == 0 && insubmenu == 0) selected = 1;
                    else if (selected == 2 && insubmenu == 0) selected = 3;
                    // Ëîãèêà äëÿ ïåðåõîäà âïðàâî
                    break;
                }
                if (insubmenu == 0) {
                    highlightmenu(selected);
                }
            }
            else { //Basic keys / Ñòàíäàðò êëàâèøè
                switch (key) {
                case ENTER_BUTTON:
                    if (insubmenu == 0) {
                        insubmenu = 1;
                        selectsubmenu(selected, subselected);
                    }
                    else if (insubmenu == 1) {
                        system("cls");
                        special_code = 1;
                        return 0;
                    }
                    break;
                case ESC_BUTTON:
                    if (insubmenu == 2) {
                        cursorInfo.bVisible = TRUE;
                        SetConsoleCursorInfo(hConsole, &cursorInfo);
                        system("cls");
                        printmainmenu();
                        highlightmenu(selected);
                        gotoxy(20, 4);
                        insubmenu = 0;
                        break;
                    }
                    else if (insubmenu == 1) {
                        insubmenu = 0;
                        system("cls");
                        printmainmenu();
                        highlightmenu(selected);
                        gotoxy(20, 4);
                        break;
                    }
                    else return -1;
                case 'h': // H (Ignoring register / èãíîðèðóåì ðåãèñòð)
                case 'H':
                    if (insubmenu == 0 || insubmenu == 1) {
                        cursorInfo.bVisible = FALSE;
                        SetConsoleCursorInfo(hConsole, &cursorInfo);
                        system("cls");
                        gotoxy(0, 8);
                        showhelp();
                        insubmenu = 2;
                    }
                    break;
                    // Show 'Help' menu / Ïîêàçàòü ïîìîùü
                case 'r':
                case 'R':

                    if (insubmenu == 0 || insubmenu == 1) {
                        cursorInfo.bVisible = FALSE;
                        SetConsoleCursorInfo(hConsole, &cursorInfo);
                        system("cls");
                        gotoxy(0, 0);
                        showrules();
                        insubmenu = 2;
                    }
                    break;
                    return 0;
                }
            }
        }
    }
}


//Animation Functions of 'maingame' / Ôóíêöèè Àíèìàöèè ãëàâíîé èãðû
void animatemaingame() {
    int base_y = Y_COORD_ANIMATE; 
    int base_x = X_COORD_ANIMATE;

    for (int i = 0; i < MAX_ACTIVE_EXAMPLES; i++) {
        if (examples[i].active) {
            int y = base_y - i * 2;

            gotoxy(base_x, y + 1);
            printf("                              ");
            gotoxy(base_x, y);
            printf("%-30s", examples[i].text);
        }
    }
}
void add_new_examples(const char* line) {
    // Move all exmpls up / Ñäâèãàåì âñå ïðèìåðû ââåðõ
    for (int i = MAX_ACTIVE_EXAMPLES - 1; i > 0; i--) {
        examples[i] = examples[i - 1];
    }

    // Write down new exmpl to lower line / Çàïèñûâàåì íîâûé ïðèìåð â ñàìóþ íèæíþþ ñòðîêó
    strncpy(examples[0].text, line, sizeof(examples[0].text) - 1);
    examples[0].text[sizeof(examples[0].text) - 1] = '\0';
    examples[0].active = 1;
}
void init_examples_struct() {
    for (int i = 0; i < MAX_ACTIVE_EXAMPLES; i++) {
        examples[i].active = 0;
        examples[i].text[0] = '\0';
    }
}
void keep_cursor() {
    int y_cursor = Y_COORD_ANIMATE;
    gotoxy(X_COORD_ANIMATE + strlen(examples[0].text), y_cursor);
}

//Maingame functions / Ôóíêöèè ñîçäàíèÿ èãðû
int custom_scanf(float* out) {
    /*RUS:
    Êàñòîìíàÿ ðåàëèçàöèÿ scanf äëÿ îäíîïîòîêà (scanf áëîêèðóåò ââîä, à ìíå íóæíî â ýòîò ìîìåíò ïðîâåðèòü íå íàæàò ëè ESC.
     Áîëåå òîãî, ýòà ôóíêöèÿ â ðàçû áîëåå áåçîïàñíà ÷åì scanf, äà è â êàêîé òî ñòåïåíè ïðîùå. Áûëî èíòåðåñíî å¸ íàïèñàòü)
     RETURN CODES: 
     ESC_BUTTON - Íàæàòèå ESC
     1 - Ñåðü¸çíàÿ îøèáêà
     0 - Áåçîøèáî÷íîå çàâåðøåíèå êîäà
     ENG:
     Custom realization of scanf for singlethread (scanf blocks the thread, until user dont enter a number. I need to make sure that user could use ESC-menu,
     furthermore, this function way more save then basic realization of 'scanf' func, and easier at all. It was exciting to write it)
     Return codes:
     ESC_BUTTON - ESC pressed
     1 - Critical ERR
     0 - 'All-OK' return
     */
    char custom_scanf_buffer[MAXLEN] = { 0 };
    int index = 0;
    int hasdot = 0;
    int FE = 0; //Force Exit - makes it impossible to press ENTER button when buffer is full (safety measure) / Forse Exit, íå äà¸ò íàæàòü ïðîáåë ïîñëå íåãî
    if (out == NULL) return 1;
    while (1) {
        if (_kbhit()) {
            char c = _getch();
            if (c == ESC_BUTTON) {
                //Logic for completing the enter phase, buffer flush and exit from func / Ëîãèêà çàâåðøåíèÿ ââîäà, î÷èñòêè áóôåðà è âûõîäà
                memset(custom_scanf_buffer, 0, MAXLEN);
                hasdot = 0;
                FE = 0;
                return ESC_BUTTON;
            }
            else if (c == BACKSPACE_BUTTON && index > 0) {
                //Logic for deleting a symbol / Ëîãèêà ðàáîòû ïðè óäàëåíèè ñèìâîëà
                if ((custom_scanf_buffer[index - 1] == '.') && hasdot > 0) hasdot--;
                index--;
                custom_scanf_buffer[index] = '\0';
                printf("\b \b");
            }
            else if (c >= '0' && c <= '9' || c == '.' || c == '-') {
                if (index == MAXLEN - 1) {
                    //Forse EXIT (Security)
                    custom_scanf_buffer[MAXLEN - 1] = '\0';
                    FE++;
                    *out = atof(custom_scanf_buffer);
                    memset(custom_scanf_buffer, 0, MAXLEN);
                    return 0;
                }
                else if (index < MAXLEN - 1) {
                    if (c == '-' && index == 0) {
                        if (index < MAXLEN - 1) putchar(c); custom_scanf_buffer[index] = c;
                        index++;
                    }
                    else if ((c == '.' && hasdot != 1) && index != 0 && custom_scanf_buffer[index-1] != '-') {
                         if (index < MAXLEN - 1) putchar(c); custom_scanf_buffer[index] = c;
                         hasdot++;
                         index++;
                    }
                    else if (! ( (custom_scanf_buffer[0] == '-' && c == '.' && index == 1) || (index == 0 && c == '.') || ((c == '.' || c == '-') && (custom_scanf_buffer[index - 1] == '-' || custom_scanf_buffer[index - 1] == '.')))) {
                        if (!(c == '.' && hasdot != 0)) {
                            custom_scanf_buffer[index] = c;
                            putchar(c);
                            index++;
                        }
                    }
                }
            }
            else if (c == ENTER_BUTTON && FE != 1 && index > 0) {
                custom_scanf_buffer[index] = '\0';
                *out = atof(custom_scanf_buffer);
                memset(custom_scanf_buffer, 0, MAXLEN);
                FE = 0;
                hasdot = 0;
                return 0;
                
            }
            
        }
    }
}
int handleanswers(float* Pcorrect) {

    //Needed varbls for func / Íåîáõîäèìûå ôóíêöèè ïåðåìåííûå
    float answer;
    float correct = *Pcorrect;
    int option = custom_scanf(&answer);


    if (option == ESC_BUTTON) {
        system("cls");
        return 2;
    }
    else if (option == 1) {
        return -1;
    }


    if (fabs(answer - correct) < EPSILON) {
        gotoxy(39, 4);
        printf("!!!!           CORRECT         !!!!");
        Sleep(500);
        return 0;
    }
    else {
        gotoxy(39, 4);
        printf("!!!!           INCORRECT           !!!!");
        Sleep(500);
        return 1;
    }

}
int writerecords(int* result, int* SB, int* softSB, int* last_err) {
    if (*result == 0) {
        if (*last_err == 0) {
            (*SB)++;       //Continue clear strike /  Ïðîäîëæàåì ÷èñòóþ ñåðèþ
        }
        else {
            (*softSB)++;   //Counting 'after-error' strike / Ñ÷èòàåì "ïîñëåîøèáî÷íóþ" ñåðèþ
            if (*softSB > *SB) {
                *SB = *softSB;
            }
        }
        *last_err = 0; // Flushing the err flag / Ñáðîñ ôëàãà îøèáêè
    }
    else if (*result == 1) {
        *softSB = 0;      // Îøèáêà  ñáðîñ ñåðèè
        *last_err = 1;
    }
}
int checknumber(const int* out_N1) {
    //Ôóíêöèÿ ïî ïðîâåðêå ÷èñëà
    //Ïðîâåðÿåì ïåðâîå ÷èñëî äëÿ ïîäáîðà âòîðîãî
    int N1 = *out_N1;
    int N2 = -100000; //ERR value / ERR çíà÷åíèå
    int is_simple = 1;
    for (int i = 2; i <= 10; i++) {
         if (N1 % i == 0) {
             is_simple = 0;
             break;
         } //If has devisors -> 0, if simple -> 0 / Åñëè ÷èñëî èìååò äåëèòåëè - 0, åñëè ïðîñòîå - 1.
    }
    if (is_simple == 1) {
        if (subselected == 0 || subselected == 3) {
            int random = rand() % 4;
            switch (random) {
            case 0: N2 = 1; break;
            case 1: N2 = 2; break;
            case 2: N2 = 4; break;
            case 3: N2 = 8; break;
            }
        }
        else if (subselected == 1) {
            N2 = 10;
            } 
        else if (subselected == 2) {
            int random = rand() % 2;
            switch (random) {
            case 0: N2 = 100; break;
            case 1: N2 = N1; break;
            }
        }
    }
    else {
        struct devisors {
            int even;
            int three;
            int four;
            int five;
            int six;
            int seven;
            int eight;
            int nine;
            int ten;
        };
        struct devisors NN = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        for (int i = 2; i <= 10; i++) {
            if (N1 % i == 0) {
                switch (i) {
                case 2: NN.even = 1; break;
                case 3: NN.three = 1; break;
                case 4: NN.four = 1; break;
                case 5: NN.five = 1; break;
                case 6: NN.six = 1; break;
                case 7: NN.seven = 1; break;
                case 8: NN.eight = 1; break;
                case 9: NN.nine = 1; break;
                case 10: NN.ten = 1; break;
                }
            }
            if (NN.even == 1) {
                //Devisors for even numbers / Äåëèòåëè äëÿ ÷¸òíûõ ÷èñåë
                //Idea for next version of Countgame: make devisors choices based on 'selected' and 'subselected' / Ñäåëàòü âûáîð â çàâèñèìîñòè îò ðåæèìà, 2-1/3-2/3-3/3-1
                if (subselected == 0 || subselected == 3) {
                    int prand = rand() % 5;
                    switch (prand) {
                    case 0: N2 = 1; break;
                    case 1: N2 = 2; break;
                    case 2: N2 = 4; break;
                    case 3: N2 = 5; break;
                    case 4: N2 = 8; break;
                    }
                }
                else if (subselected == 1) {
                    int prand = rand() % 5;
                    switch (prand) {
                    case 0: N2 = 10; break;
                    case 1: N2 = 20; break;
                    case 2: N2 = 25; break;
                    case 3: N2 = 40; break;
                    case 4: N2 = 50; break;
                    }
                }
                else {
                    int prand = rand() % 5;
                    switch (prand) {
                    case 0: N2 = 100; break;
                    case 1: N2 = 125; break;
                    case 2: N2 = 200; break;
                    case 3: N2 = 250; break;
                    case 4: N2 = 500; break;
                    }
                }
            }
            else if (NN.three == 1) {
                //Devisors for 3 / Äåëèòåëè äëÿ òðîéêè
                //2 - 1 / 3 - 2 / 3 - 3 / 3 - 1
                if (subselected == 0 || subselected == 3) {
                    int prand = rand() % 3;
                    switch (prand) {
                    case 0: N2 = 1; break;
                    case 1: N2 = 3; break;
                    case 2: N2 = 6; break;
                    }
                }
                else if (subselected == 1) {
                    int prand = rand() % 4;
                    switch (prand) {
                    case 0: N2 = 12; break;
                    case 1: N2 = 15; break;
                    case 2: N2 = 30; break;
                    case 3: N2 = 60; break;
                    }
                }
                else {
                    int prand = rand() % 2;
                    switch (prand) {
                    case 0: N2 = 150; break;
                    case 1: N2 = 300; break;
                    }
                }
            }
            else if (NN.four == 1) {
                //Devisors for 4 / Äåëèòåëè ÷åòâ¸ðêè
                //2 - 1 / 3 - 2 / 3 - 3 / 3 - 1
                if (subselected == 0 || subselected == 3) {
                    int prand = rand() % 5;
                    switch (prand) {
                    case 0: N2 = 1; break;
                    case 1: N2 = 2; break;
                    case 2: N2 = 4; break;
                    case 3: N2 = 5; break;
                    case 4: N2 = 8; break;
                    }
                }
                else if (subselected == 1) {
                    int prand = rand() % 4;
                    switch (prand) {
                    case 0: N2 = 10; break;
                    case 1: N2 = 20; break;
                    case 2: N2 = 25; break;
                    case 3: N2 = 40; break;
                    }
                }
                else {
                    int prand = rand() % 3;
                    switch (prand) {
                    case 0: N2 = 100; break;
                    case 1: N2 = 200; break;
                    case 2: N2 = 500; break;
                    }
                }
            }
            else if (NN.five == 1) {
                //Devisors for 5 /Äåëèòåëè ïÿò¸ðêè
                //2 - 1 / 3 - 2 / 3 - 3 / 3 - 1
                if (subselected == 0 || subselected == 3) {
                    int prand = rand() % 2;
                    switch (prand) {
                    case 0: N2 = 1; break;
                    case 1: N2 = 5; break;
                    }
                }
                else if (subselected == 1) {
                    int prand = rand() % 3;
                    switch (prand) {
                    case 0: N2 = 10; break;
                    case 1: N2 = 25; break;
                    case 2: N2 = 50; break;
                    }
                }
                else {
                    int prand = rand() % 4;
                    switch (prand) {
                    case 0: N2 = 100; break;
                    case 1: N2 = 125; break;
                    case 2: N2 = 250; break;
                    case 3: N2 = 500; break;
                    }
                }
            }
            else if (NN.six == 1) {
                //Devisors for 6 / Äåëèòåëè øåñò¸ðêè
                //2 - 1 / 3 - 2 / 3 - 3 / 3 - 1
                if (subselected == 0 || subselected == 3) {
                    int prand = rand() % 3;
                    switch (prand) {
                    case 0: N2 = 1; break;
                    case 1: N2 = 2; break;
                    case 2: N2 = 6; break;
                    }
                }
                else if (subselected == 1) {
                    N2 = 10;
                    if (NN.even) {
                        int prand = rand() % 2;
                        switch (prand) {
                        case 0: N2 = 20; break;
                        case 1: N2 = 25; break;
                        }
                    }
                }
                else {
                    int prand = rand() % 3;
                    switch (prand) {
                    case 0: N2 = 100; break;
                    case 1: N2 = 125; break;
                    case 2: N2 = 200; break;
                    }
                }
            }
            else if (NN.seven == 1) {
                //Devisors for 7 / äåëèòåëè ñåì¸ðêè
                //Simple number
                //2 - 1 / 3 - 2 / 3 - 3 / 3 - 1
                if (subselected == 0 || subselected == 3) {
                    int prand = rand() % 2;
                    switch (prand) {
                    case 0: N2 = 1; break;
                    case 1: N2 = 7; break;
                    }
                }
                else if (subselected == 1) {
                    int prand = rand() % 9;
                    switch (prand) {
                    case 0: N2 = 14; break;
                    case 1: N2 = 21; break;
                    case 2: N2 = 28; break;
                    case 3: N2 = 35; break;
                    case 4: N2 = 42; break;
                    case 5: N2 = 49; break;
                    case 6: N2 = 56; break;
                    case 7: N2 = 63; break;
                    case 8: N2 = 70; break;
                    }
                }
                else {
                    int prand = rand() % 2;
                    switch (prand) {
                    case 0: N2 = N1; break;
                    case 1: N2 = 100; break;
                    }
                }
            }
            else if (NN.eight == 1) {
                //Devisors for 8 / äåëèòåëè âîñüì¸ðêè
                //2 - 1 / 3 - 2 / 3 - 3 / 3 - 1
                if (subselected == 0 || subselected == 3) {
                    int prand = rand() % 5;
                    switch (prand) {
                    case 0: N2 = 1; break;
                    case 1: N2 = 2; break;
                    case 2: N2 = 4; break;
                    case 3: N2 = 5; break;
                    case 4: N2 = 8; break;
                    }
                }
                else if (subselected == 1) {
                    int prand = rand() % 4;
                    switch (prand) {
                    case 0: N2 = 10; break;
                    case 1: N2 = 20; break;
                    case 2: N2 = 25; break;
                    case 3: N2 = 40; break;
                    }
                }
                else {
                    int prand = rand() % 5;
                    switch (prand) {
                    case 0: N2 = 100; break;
                    case 1: N2 = 125; break;
                    case 2: N2 = 200; break;
                    case 3: N2 = 250; break;
                    case 4: N2 = 500; break;
                    }
                }
            }
            else if (NN.nine == 1) {
                //Devisors for 9 / äåëèòåëè äåâÿòêè
                //2 - 1 / 3 - 2 / 3 - 3 / 3 - 1
                if (subselected == 0 || subselected == 3) {
                    int prand = rand() % 4;
                    switch (prand) {
                    case 0: N2 = 1; break;
                    case 1: N2 = 5; break;
                    case 2: N2 = 3; break;
                    case 3: N2 = 9; break;
                    }
                }
                else if (subselected == 1) {
                    int prand = rand() % 3;
                    switch (prand) {
                    case 0: N2 = 10; break;
                    case 1: N2 = 20; break;
                    case 2: N2 = 25; break;
                    }
                }
                else {
                    int prand = rand() % 5;
                    switch (prand) {
                    case 0: N2 = 100; break;
                    case 1: N2 = 125; break;
                    case 2: N2 = 200; break;
                    case 3: N2 = 250; break;
                    case 4: N2 = 500; break;
                    }
                }
            }
            else if (NN.ten == 1) {
                //Devisors for 10 / äåëèòåëè äåñÿòêè
                //2 - 1 / 3 - 2 / 3 - 3 / 3 - 1
                if (subselected == 0 || subselected == 3) {
                    int prand = rand() % 3;
                    switch (prand) {
                    case 0: N2 = 1; break;
                    case 1: N2 = 2; break;
                    case 2: N2 = 5; break;
                    }
                }
                else if (subselected == 1) {
                    int prand = rand() % 3;
                    switch (prand) {
                    case 0: N2 = 20; break;
                    case 1: N2 = 25; break;
                    case 2: N2 = 50; break;
                    }
                }
                else {
                    int prand = rand() % 4;
                    switch (prand) {
                    case 0: N2 = 100; break;
                    case 1: N2 = 125; break;
                    case 2: N2 = 250; break;
                    case 3: N2 = 500; break;
                    }
                }
            }
        }
    }
    return N2;
}
void getnumber(int* out_N1, int* out_N2) {
    //Generates X number for each gamemode 
    int N1, N2;
    switch (subselected) {
    case 0: {
        //2 - 1
        int range1 = rand() % 2;
        if (range1 == 0) {
            N1 = (rand() % (90)) - 99; // From -99 to -10 / îò -99 äî -10
        }
        else {
            N1 = (rand() % (90)) + 10; // îò 10 äî 99
        }
        if (selected != 3) {
            N2 = 1 + rand() % (9 - 1 + 1);// îò -9 äî 9
            int rd = rand() % 2;
            if (rd == 0) {
                N2 = -N2;
            }
        }
        else {
            N2 = checknumber(&N1);
        }
        break;
    }
    case 1: {
        //3 - 2
        N1 = 100 + rand() % (999 - 100 + 1);
        int randop = rand() % 10;
        if (randop <= 4) {
            N1 = -N1;
        }
        if (selected != 3) {
            N2 = 10 + rand() % (99 - 10 + 1);
            int randop2 = rand() % 10;
            if (randop2 <= 4) {
                N2 = -N2;
            }
        }
        else {
            N2 = checknumber(&N1);
        }
        break;
    }
    case 2: {
        //3 - 3
        N1 = 100 + rand() % (999 - 100 + 1);
        int randop = rand() % 10;
        if (randop <= 4) N1 = -N1;
        if (selected != 3) {
            N2 = 100 + rand() % (999 - 100 + 1);
            int randop2 = rand() % 10;
            if (randop2 <= 4) N2 = -N2;
        }
        else {
            N2 = checknumber(&N1);
        }
        break;
    }
    case 3: {
        N1 = 100 + rand() % (999 - 100 + 1);
        int randop = rand() % 10;
        if (randop <= 4) N1 = -N1;
        if (selected != 3) {
            N2 = 1 + rand() % (9 - 1 + 1);
            int randop3 = rand() % 10;
            if (randop3 <= 4) N2 = -N2;
        }
        else {
            N2 = checknumber(&N1);
        }
        break;
        }
    }
    *out_N1 = N1;
    *out_N2 = N2; 
}
int maingame() {
        int stop = 0;
        int SB = 0;
        int softSB = 0; //Best after ERR / Òåêóùèé ðåêîðä ïîñëå îøèáêè
        int last_err = 0; //'Last-ERR' flag / Ôëàã óêàçûâàþùèé ÷òî ïîñëåäíèé ïðèìåð - îøèáêà.
        struct gamesaves SAVED_RECORDS;
        int load_status = load_progress(&SAVED_RECORDS);
        if (load_status == -1) {
            logger(1, "CANNOT LOAD GAMESAVES!!");
            return -1;
        }
        logger(0, "Game saves loaded successfully");
        char examplebuffer[MAX_LINE_LENGTH];
        init_examples_struct();


        while (stop != 1) {
            /*Special_code - become 0 if user didn't selected a gamemode in MMUgetcoursor / 
            * stop - indicates a condition for ESC menu
              Special_code - Ñòàíîâèòüñÿ 0 åñëè íå áûë âûáðàí ðåæèì èãðû â ãëàâíîì ìåíþ (MMUGetCoursor)
              stop - ôëàã ïîïàäàíèÿ â ìåíþ âûõîäà
            */
            if (special_code == 1) {
                int N1, N2;
                switch (selected) {
                case ADDITION: {
                    char new_example[MAX_LINE_LENGTH] = { 0 }; //Initializing buffer / Èíèöèàëèçàöèÿ áóôåðà

                    system("cls");
                    gotoxy(0, 0);
                    showgameback(SB, &selected, &subselected, &SAVED_RECORDS); //Making backscreen visible / Ïîêàçûâàåì çàäíèé ôîí
                    getnumber(&N1, &N2); //Getting numbers for math expression
                    if (N2 < 0) { snprintf(new_example, sizeof(new_example), "%d + (%d) = ", N1, N2); }
                    else snprintf(new_example, sizeof(new_example), "%d + %d = ", N1, N2);

                    add_new_examples(new_example); //Animation stuff / Ôóíêöèè àíèìàöèè
                    animatemaingame();
                    keep_cursor();

                    float correct = N1 + N2;
                    int result = handleanswers(&correct); //Checking user answer / Ïðîâåðêà îòâåòà ïîëüçîâàòåëÿ

                    char result_text[MAX_LINE_LENGTH]; //New buffer for user answer / Áóôåð äëÿ õðàíåíèÿ çíà÷åíèÿ ÷òî ââ¸ë ïîëüçîâàòåëü
                    snprintf(result_text, sizeof(result_text), "%s%d", examples[0].text, (int)correct);
                    strncpy(examples[0].text, result_text, sizeof(examples[0].text) - 1);
                    examples[0].text[sizeof(examples[0].text) - 1] = '\0';

                    writerecords(&result, &SB, &softSB, &last_err); //Updating personal bests on backscreen / Îáíîâëåíèå ðåêîðäîâ íà ôîíå
                    write_progress(&SAVED_RECORDS, &selected, &subselected, &SB); //Saving personal best to gamesaves file / Ñîõðàíÿåì ðåêîðäû ïîëüçîâàòåëÿ â ôàéë
                    if (result == 2) {
                        stop++;
                        continue;
                    }
                    else if (result == 0)  break;
                    else if (result == 1)  break;
                    else if (result == -1) { stop = 0; return -1; }
                    break;
                }
                case SUBSTRACTION: {
                    char new_example[MAX_LINE_LENGTH] = { 0 };
                    system("cls");
                    gotoxy(0, 0);
                    showgameback(SB, &selected, &subselected, &SAVED_RECORDS);
                    getnumber(&N1, &N2);
                    if (N2 < 0) { snprintf(new_example, sizeof(new_example), "%d - (%d) = ", N1, N2); }
                    else snprintf(new_example, sizeof(new_example), "%d - %d = ", N1, N2);

                    add_new_examples(new_example);
                    animatemaingame();
                    keep_cursor();

                    float correct = N1 - N2;
                    int result = handleanswers(&correct);

                    char result_text[MAX_LINE_LENGTH];
                    snprintf(result_text, sizeof(result_text), "%s%d", examples[0].text, (int)correct);
                    strncpy(examples[0].text, result_text, sizeof(examples[0].text) - 1);
                    examples[0].text[sizeof(examples[0].text) - 1] = '\0';

                    writerecords(&result, &SB, &softSB, &last_err);
                    write_progress(&SAVED_RECORDS, &selected, &subselected, &SB);
                    if (result == 2) {
                        stop++;
                        continue;
                    }
                    else if (result == 0) break;
                    else if (result == 1) break;
                    else if (result == -1) { stop = 0; return -1; }
                    break;
                }
                case MULTIPLICATION: {
                    char new_example[MAX_LINE_LENGTH] = { 0 };

                    system("cls");
                    gotoxy(0, 0);
                    showgameback(SB, &selected, &subselected, &SAVED_RECORDS);
                    animatemaingame();
                    getnumber(&N1, &N2);
                    if (N2 < 0) { snprintf(new_example, sizeof(new_example), "%d * (%d) = ", N1, N2); }
                    else snprintf(new_example, sizeof(new_example), "%d * %d = ", N1, N2);

                    add_new_examples(new_example);
                    animatemaingame();
                    keep_cursor();

                    float correct = N1 * N2;
                    int result = handleanswers(&correct);

                    char result_text[MAX_LINE_LENGTH];
                    snprintf(result_text, sizeof(result_text), "%s%d", examples[0].text, (int)correct);
                    strncpy(examples[0].text, result_text, sizeof(examples[0].text) - 1);
                    examples[0].text[sizeof(examples[0].text) - 1] = '\0';
                    writerecords(&result, &SB, &softSB, &last_err);
                    write_progress(&SAVED_RECORDS, &selected, &subselected, &SB);
                    if (result == 2) {
                        stop++;
                        continue;
                    }
                    else if (result == 0) break;
                    else if (result == 1) break;
                    else if (result == -1) { stop = 0; return -1; }
                    break;
                }
                case DIVISION: {
                    char new_example[MAX_LINE_LENGTH] = { 0 };

                    system("cls");
                    gotoxy(0, 0);
                    showgameback(SB, &selected, &subselected, &SAVED_RECORDS);
                    animatemaingame();
                    getnumber(&N1, &N2);
                    if (N2 < 0) { snprintf(new_example, sizeof(new_example), "%d / (%d) = ", N1, N2); }
                    else snprintf(new_example, sizeof(new_example), "%d / %d = ", N1, N2);

                    add_new_examples(new_example);
                    animatemaingame();
                    keep_cursor();

                    float correct = (float)N1 / (float)N2;
                    int result = handleanswers(&correct);

                    char result_text[MAX_LINE_LENGTH];
                    snprintf(result_text, sizeof(result_text), "%s%.4f", examples[0].text, correct);
                    strncpy(examples[0].text, result_text, sizeof(examples[0].text) - 1);
                    examples[0].text[sizeof(examples[0].text) - 1] = '\0';

                    writerecords(&result, &SB, &softSB, &last_err);
                    write_progress(&SAVED_RECORDS, &selected, &subselected, &SB);
                    if (result == 2) {
                        stop++;
                        continue;
                    }
                    else if (result == 0) break;
                    else if (result == 1) break;
                    else if (result == -1) { stop = 0; return -1; }
                    break;
                    }
                }
            }
    }
        if (stop == 1) {
            gotoxy(0, 0);
            printexitmenu();
            gotoxy(40, 16);
            int EMselected = 0;
            while (1) {
                if (_kbhit()) {
                    int key = _getch();
                    if (key == 0 || key == 224) { //Special keys / Ñïåöêëàâèøè
                        key = _getch();
                        switch (key) {
                        case ARROW_LEFT:
                            if (EMselected == 1) {
                                gotoxy(40, 16);
                                EMselected = 0;
                            }
                            break;
                        case ARROW_RIGHT:
                            if (EMselected == 0) {
                                gotoxy(61, 16);
                                EMselected = 1;
                            }
                            break;
                        }
                    }
                    else {
                        if (key == ENTER_BUTTON) {
                            if (EMselected == 0) {
                                //Âåðíóòüñÿ â ìåíþ
                                system("cls");
                                break;
                            }
                            else if (EMselected == 1) {
                                //Game continuation / Ïðîäîëæèòü èãðó
                                system("cls");
                                stop = 0;
                                return 2;
                            }
                        }
                    }
                }
            }

        }
    return 0;
}

int setup_countgame() {
    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD new_size = { 119, 30 };
    SetConsoleScreenBufferSize(hConsole, new_size);
    checklang();
    animatelogo();
    showpressenter(5);
    handlepressenter(5);
    system("cls");
    int exit = 0;
    int kir = 0; 
    /* KIR = Keep It Running - used for signalazing that there is no need to execure mmugetcoursor / 
       Keep It Running, íóæíà ÷òî áû ñèãíàëèçèðîâàòü ÷òî íå íóæíî âûïîëíÿòü mmugetcoursor
    */
    while (exit != 1) {
        if (kir == 0) {
            int result = mmugetcoursor(0, 0);
            if (result == -1) {
                exit = 1;
                break;
            }
        }
        int gameresult = maingame();
        if (gameresult == -1) {
            exit = 1;
            break;
        }
        if (gameresult == 2) {
            kir = 1;
        }
        if (gameresult == 0) {
            kir = 0;
        }
    }
    return 0;
}
