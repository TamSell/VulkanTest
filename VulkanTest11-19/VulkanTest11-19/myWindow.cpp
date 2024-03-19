#include "myWindow.h"
#include <iostream>

LRESULT WindowProc(HWND hWND, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWND);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWND, uMsg, wParam, lParam);
}


myWindow::myWindow(int width, int height) : w_hInstance(GetModuleHandle(nullptr))
{
	const wchar_t* CLASS_NAME = L"My Window Class";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = w_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	w_hWidth = width;
	w_hHeight = height;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + w_hWidth;
	rect.bottom = rect.top + w_hHeight;

	AdjustWindowRect(&rect, style, false);

	w_Hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Tellor Vulkan",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		w_hInstance,
		NULL

	);
		std::cout << "Created window handle" << std::endl;

	ShowWindow(w_Hwnd, SW_SHOW);
}

myWindow::~myWindow()
{
	const wchar_t* CLASS_NAME = L"My Window Class";

	UnregisterClass(CLASS_NAME, w_hInstance);
}

bool myWindow::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

HWND myWindow::getMyHandle()
{
	return w_Hwnd;
}

int myWindow::getHeigth()
{
	return w_hHeight;
}

int myWindow::getWidth()
{
	return w_hWidth;
}