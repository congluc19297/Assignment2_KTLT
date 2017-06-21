#pragma once
#ifndef LIBSWINDOW_H
#define LIBSWINDOW_H
#include <Windows.h>
#include <conio.h>

enum color_t {
	Black, Blue, Green, Aqua, Red, Purple, Yellow, White, Gray, Light_Blue,
	Light_Green, Light_Aqua, Light_Red, Light_Purple, Light_Yellow, Bright_White
};

enum arrow { Control = 224, Up = 72, Down = 80, Enter = 13 };

void   setWindows(void);
void   setWindows(short);
void   setColor(color_t, color_t);
short  wherex(void);
short  wherey(void);
void   gotoxy(short, short);
void   clreop(short, short);
void   wait(int);
int    readKey(void);

#endif