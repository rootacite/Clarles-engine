#pragma once

#include "elements.h"


BOOL PointInRect(POINT p, RECT rect);
using namespace std;



#define MEVENT_CLICK 0
#define MEVENT_MOVEIN 1
#define MEVENT_MOVEOUT 2



// 定义变量
DWORD WINAPI renderThread(LPVOID pValue);
class ViewObject
{
public:
	ViewObject(HWND hWnd, DWORD thread);
	~ViewObject();

	//friend LRESULT CALLBACK MouseEventProc(int nCode, WPARAM wParam, LPARAM lParam);
	BOOL setBkground(ID2D1Bitmap* path);//设置背景图片
	BOOL setBkmusic(wstring path);
	wstring m_Bkmusic = L"";
	int addElement(ID2D1Bitmap* elementIni, POINT area, UINT msg, double Tranl);
	BOOL complete();

	void clear();
	void clearWithoutEvent();

	HHOOK hMouse = NULL;
	RECT ShowArea = {0};
	HWND m_hWnd = NULL;

	RECT eventArea[100];
	BOOL isInArea[100];
	int eventCount = 0;
	string TextPath = "";
	UINT msgList[100];
	LPWSTR musicPath = NULL;
	DWORD ccThreadId = NULL;
	ID2D1Bitmap* LoadImageTo(wstring path);
};
