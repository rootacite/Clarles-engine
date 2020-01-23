#pragma once
#include "ViewSystem.h"

struct ElementItem {
	POINT position;
	//wchar_t path[255];
	wstring path;
	int ChangeTime = 1;
};

struct ButtonItem {
	UINT msg;
	POINT position;
	wstring path1;
	wstring path2;
};

struct ViewItem {
	wstring BackGround;
	//wchar_t BackGround[255] = {0};
	wchar_t music[255] = { 0 };
	ButtonItem* buttons = NULL;
	int buttonCount = 0;
	ElementItem* elements = NULL;
	int elementCount = 0;

	int autoChange = 0;
	int BackGroundchangeTime = 1;
	wchar_t TextStr[125] = { 0 };

	wchar_t playonce[255] = { 0 };

	int tx = 0;
	int ty = 0;
};


//sizeof(ViewItem);

BOOL getViewformScript(int id, LPCSTR path, ViewItem* lpItem);



class AVGSYSTEM
{
public:
	AVGSYSTEM(HWND hWnd, DWORD thread);
	~AVGSYSTEM();

	void OrderView(ViewItem* items);

	wstring buttonIconon[100];
	wstring buttonIconoff[100];

	int buttonCount = 0;
	UINT buttonEvents[100];
	POINT buttonPoint[100];
	BOOL isInAreaOfButton[100];
	BOOL autoRedraw = TRUE;

	wstring elementsIcon[100];

	int mtx;
	int mty;
	int elementsCount = 0;
	POINT elementsPoint[100];

	wstring NowBk = L"";

	ViewObject* thisview = NULL;   //主帧，将循环更新
private:
	DWORD hThread;  
};
