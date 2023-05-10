# winAPI-gui-key-logger
## Introduction
As a learner you probably watched some videos or tutorials where mentor taught you some code, and it was all fine and smooth... until the moment he/she pushed some button or a key-sequence and things flashed across the screen and you are stuck, cannot comprehend what you just wintessed. Meanwhile for the mentor it was a common thing, he/she continues as if nothing happened. So what were those keystrokes will keep being the mystery forever.
This program is one of those that can solve such a problem.
There are too few of teachers who do use keystroke visualizers, thus, this repository meant to act as a promotional material, as well. 
## About the program
It is a simple lightweight key-logger or keystroke visualizer, shows what keys are being pressed.
It displays its window above all other windows, 
records keystrokes independently of what window is currently in focus,
has fixed screen size, works as a simple indicator,
closes without problems when close button is pressed.
*Note*: doesn't show cyrillic keys or any other ones when you choose another language.

built with g++ 12.1.0, using winAPI on Windows 11 64-bit.
build command:
`C:\C++\mingw64\bin\g++.exe -g -std=c++20 D:\winAPI_projects\gui_keylogger2.0\*.cpp -o D:\winAPI_projects\gui_keylogger2.0\logger.exe -mwindows -lgdi32`

**Important**: This project is not intended for accomplishing any malicious goals, so authors do not take the responsibility for code misuse or modifications.

## Usage
See the `logger.exe` above, this is the program itself, run it as a simple .exe file and enjoy.

## Working program screenshots:
![image](https://github.com/Andriy-Bilenko/winAPI-gui-key-logger/blob/main/src/Working_program_screenshot_1.jpg)
![image](https://github.com/Andriy-Bilenko/winAPI-gui-key-logger/blob/main/src/Working_program_screenshot_2.png)
![image](https://github.com/Andriy-Bilenko/winAPI-gui-key-logger/blob/main/src/Working_program_screenshot_3.png)
## What's new
- Documented code with no warnings.
- Colored, fixed size window.
- Accepts relatively complex key-sequences.




If you ran into some issues by any chance or need to contact the developer, it would be great to recieve your valuable feedback on email: *bilenko.a.uni@gmail.com*.

<div align="right">
<table><td>
<a href="#start-of-content">↥ Scroll to top</a>
</td></table>
</div>