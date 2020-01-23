#pragma once

#include "defInds.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);  // message proc

//define window data

HWND WindowInit(HINSTANCE hInst,int nCmdShow);
int directXInit(HWND hWnd, HINSTANCE hInst);
ID2D1Bitmap* LoadImageTo(std::wstring path);

// Define elements of class
#define WND_CLASSNAME L"Demo"
#define WND_TITLE L"Clarles"
#define WND_ICON NULL
#define WND_ICONSM NULL
#define WND_CALLBACKROC WndProc
#define WND_COLSTYLE CS_CLASSDC
#define WND_CURSOR NULL
#define WND_BKGROUND NULL
#define WND_MENUNAME NULL

//define elements of window



#define WND_WNDSTYLE WS_OVERLAPPEDWINDOW
#define WND_SHOWAREA RECT{0,0,1280,720}


#define SAFE_RELEASE(p) if(p){p->Release();p=NULL;} 



#define GAMEEVENT_NEXT WM_USER+100
#define GAMEEVENT_TEST WM_USER+101
#define GAMEEVENT_1 WM_USER+102
#define GAMEEVENT_2 WM_USER+103


#define VIEW_EVENT_TEST (WM_USER)+100
#define VIEW_EVENT_START WM_USER+101
#define VIEW_EVENT_EXIT WM_USER+102
#define VIEW_EVENT_NEXT WM_USER+103
