# Countgame - Console math game for Windows
Countgame - Console application for Windows operating system. The game is designed to train both simple and advanced arithmetic skills.
The game is written in C for speed and ease. This allows it to work on almost any Windows device. The game uses CLI (Windows Command Line Interface) to draw all elements and does not use any graphics libraries, which makes it "light" and fast. The game has several game modes and submodes. The main idea of the game is to generate examples for the user depending on the selected game mode and check his answers for correctness.

The game has several main game modes that can be selected in the main menu, namely:
***
1. Addition (ADDITION)
2. Subtraction (SUBSTRACTION)
3. Multiplication (MULTIPLICATION)
4. Division (DIVISION)
***
Such division allows you to select examples for training the desired arithmetic operation with numbers.
Each game mode has several sub-modes to better tailor it to the user's needs, namely:
***
1. Two-Digit and One-Digit (2 X 1)
2. Three-Digit and Two-Digit (3 X 2)
3. Three-Digit and Three-Digit (3 X 3)
4. Three-Digit and One-Digit (3 X 1)
***
This brings us to the structure of the game:
1. ADDITION:     
   |- Two-Digit and One-Digit (2 X 1)     
   |- Three-Digit and Two-Digit (3 X 2)     
   |- Three-Digit and Three-Digit (3 X 3)      
   \\- Three-Digit and One-Digit (3 X 1)      
2. SUBSTRACTION:     
   |- Two-Digit and One-Digit (2 X 1)     
   |- Three-Digit and Two-Digit (3 X 2)     
   |- Three-Digit and Three-Digit (3 X 3)    
   \\- Three-Digit and One-Digit (3 X 1)     
3. MULTIPLICATION:    
   |- Two-Digit and One-Digit (2 X 1)    
   |- Three-Digit and Two-Digit (3 X 2)    
   |- Three-Digit and Three-Digit (3 X 3)    
   \\- Three-Digit and One-Digit (3 X 1)     
4. DIVISION      
   |- Two-Digit and One-Digit (2 X 1)      
   |- Three-Digit and Two-Digit (3 X 2)     
   |- Three-Digit and Three-Digit (3 X 3)     
   \\- Three-Digit and One-Digit (3 X 1)      
***
# Control and interaction     
The game is controlled using simple keys on the keyboard such as ENTER, Arrows or ESC.     
The H key can be used to open the help menu.     
The R key can be used to open the menu with the rules of the game.     
To exit a menu, press ESC. Pressing this key in the main menu will close the program.    
# File storage     
Countgame stores the main files in the path C:\\Games\Countgame and backups in the TEMP folder of the Windows OS.
The game has protection against counterfeiting and entering incorrect values through save files.    
# Known issues
1. The game stores backup files in the TEMP folder, which is why they can disappear periodically. This leads to the game not being able to start.
2. The game is only in English, in the future it may be possible to add support for the Russian language
3. Animations: The game may visually freeze during very fast interaction, however, this is not a problem with the C language, but with animations that do not have time to play to the end.

***
# Game versions before the release of the main repository
Ver 0.1:
- Implemented filecheck function
- Basic functionality <br>
- Menu + logo animations
- Added keyboard layout check
------------------
Ver 0.3:
- Added menu animations
- Added example generation
-------------------
Ver 0.4:
- Added exit to main menu function
- Added ability to read files
- Added Countgame.h header file
-------------------
Ver 0.5: <br>
- File rewriting now works <br>
- Fixed division bug <br>
- Fixed Games Best bug that was incorrectly calculated <br>
- removed else if in pecord counting that broke the game <br>
------------------
Ver 0.7:
- Added improved animation
------------------
Ver 0.7.7:
- Fixed division bug (integer display) + Fixed a bug with errors! <br>
- Fixed typos and visual bugs <br>
- Fixed a bug with entering incorrect values in saves <br>
- Added a game icon
------------------
Ver 0.8:
- Minor visual fixes <br>
- Added more concise comments to the code + comments in Russian / English <br>
- Changed Makefile <br>

***
# Further support and development of the game:
Although I expected that Countgame would be my preparatory project before larger and more complex projects, this may change, it all depends on your support. If I see more support from you, I will be happy to continue development.
# Afterword
I already have a couple of ideas for new versions of the game, but for now I will do more interesting things for me. I will inform you about new projects soon, believe me, it will be interesting. In fact, I am very glad that I finally finished this project. It took me about 4 months, considering that I wrote the code whenever possible no more than 4-5 hours and on weekends. I am glad that I see
