/*********************************************************************************************
* Module:   LibsWindow.cpp
* Author:   Group 6
* Purpose:  Hien thuc lenh dieu khien man hinh console
**********************************************************************************************/
#include "LibsWindow.h"

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       setWindows
// Purpose:    Thiet dat cua so chuong trinh
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void setWindows(void)
{
	SetConsoleTitle("LIBPRO");
	SMALL_RECT windowSize = { 0, 0, 79, 24 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { 120, 300 });
}
void setWindows(short x)
{
	SetConsoleTitle("LIBPRO");
	SMALL_RECT windowSize = { 0, 0, x - 1, 24 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { x, 300 });
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       setColor
// Purpose:    Thiet lap mau chu va mau nen
// Parameters:
// - background
// - text
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void setColor(color_t background, color_t text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), background * 16 + text);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       wherex
// Purpose:    Tra ve gia tri x toa do con tro man hinh console
// Parameters:
// Return:     short
///////////////////////////////////////////////////////////////////////////////////////////////
short wherex(void)
{
	CONSOLE_SCREEN_BUFFER_INFO currentPoint;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &currentPoint);
	return currentPoint.dwCursorPosition.X;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       wherey
// Purpose:    Tra ve gia tri y toa do con tro man hinh console
// Parameters:
// Return:     short
///////////////////////////////////////////////////////////////////////////////////////////////
short wherey(void)
{
	CONSOLE_SCREEN_BUFFER_INFO currentPoint;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &currentPoint);
	return currentPoint.dwCursorPosition.Y;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       gotoxy
// Purpose:    Dua con tro man hinh console den vi tri co toa do (x,y)
// Parameters:
// - x
// - y
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void gotoxy(short x, short y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       clreop (clear end of page)
// Purpose:    Xoa man hinh tu vi tri co toa do (x,y)
// Parameters:
// - x
// - y
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void clreop(short x, short y)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	COORD coord = { x, y };
	DWORD written;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	FillConsoleOutputCharacterW(GetStdHandle(STD_OUTPUT_HANDLE), ' ', info.dwSize.X * info.dwSize.Y, coord, &written);
	//Sau khi xoa xong dua con tro man hinh ve vi tri cu
	gotoxy(x, y);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       readKey
// Purpose:    Tra ve ma ASCII tuong ung phim duoc nhan
// Parameters:
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int readKey(void) {
	int key = _getch();
	if (key == Control) {
		key = _getch();
	}
	return key;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       wait
// Purpose:    Tam dung chuong trinh
// Parameters:
// - second
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void wait(int second) {
	Sleep(1000 * second);
	while (_kbhit()) {
		_getch();
	}
}
