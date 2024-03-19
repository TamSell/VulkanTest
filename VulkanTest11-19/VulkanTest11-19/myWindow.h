#pragma once

#define WM_LBUTTONDOWN    0x0201

#include<Windows.h>

LRESULT CALLBACK WindowProc(HWND hWND, UINT uMsg, WPARAM wParam, LPARAM lParam);

class myWindow
{
public:
	myWindow(int width, int height);
	myWindow(const myWindow&) = delete;
	myWindow& operator = (const myWindow&) = delete;
	HWND getMyHandle();
	int getHeigth();
	int getWidth();
	~myWindow();

	bool ProcessMessages();

private:
	HINSTANCE w_hInstance;
	HWND w_Hwnd;
	int w_hHeight;
	int w_hWidth;
	
};