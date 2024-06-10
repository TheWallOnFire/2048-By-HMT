// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include <utility>
#include <cstdlib>
#include <ctime>

// Enum for key
enum KeyCodeAscii
{
    // Direction input
    KEY_LEFT = 75, // Press Left Arrow
    KEY_A = 97, // Press 'a' for left direction
    KEY_RIGHT = 77, // Press Right Arrow
    KEY_D = 100, // Press 'd' for right direction
    KEY_UP = 72, // Press Up Arrow
    KEY_W = 119, // Press 'w' for up direction
    KEY_DOWN = 80, // Press Down Arrow
    KEY_S = 115, // Press 's' for down direction

    // Command input
    KEY_ESCAPE = 27, // Press ESC
    KEY_ENTER = 13, // Press ENTER
    KEY_SPACE = 32, // Press SPACEBAR
    KEY_TAB = 9, // Press TAB
    KEY_BACKSPACE = 8, // Press BACKSPACE

    // Key input
    KEY_Q = 113, // Press 'q' -> QUIT
    KEY_E = 101, // Press 'e'
    KEY_R = 104 , // Press 'r' 
    KEY_F = 102, // Press 'f'
    KEY_I = 105, // Press 'i'
    KEY_P = 112, // Press 'p' -> PAUSE
    KEY_Z = 122, // Press 'z' -> UNDO
    KEY_X = 120, // Press 'x' -> REDO
    KEY_M = 109, // Press 'm' -> SAVE
    KEY_N = 110, // Press 'n' -> LOAD
    KEY_H = 104, // Press 'h' -> HELP

    KEY_ZERO = 48,
    KEY_ONE = 49,
    KEY_TWO = 50,
    KEY_THREE = 51,
    KEY_FOUR = 52,
    KEY_FIVE = 53,
    KEY_SIX = 54,
    KEY_SEVEN = 55,
    KEY_EIGHT = 56,
    KEY_NINE = 57,
};

// Enum for color
enum ColorCode
{ // //std::cout << "\033[31;1;4mHello\033[0m\n";

    // 7 basic color
    C_BLACK = 30,
    C_RED = 31,
    C_GREEN = 32,
    C_YELLOW = 33,
    C_BLUE = 34,
    C_MAGNETA = 35,
    C_CYAN = 36,
    C_WHITE = 37,

    C_RESET = 0
};


#endif //PCH_H