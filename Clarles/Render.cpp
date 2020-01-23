#include "AVGSystem.h"

extern MSG msg;

extern ID2D1Factory* pD2DFactory;
extern ID2D1HwndRenderTarget* pRenderTarget;
extern ID2D1SolidColorBrush* pBlackBrush;
extern ID2D1Layer* g_pLayer;
extern ViewObject* MainView;

extern HWND  m_hWnd;

extern AVGSYSTEM* sysObject;

DWORD WINAPI renderThread(LPVOID pValue) {            

	
	while (1)
		Sleep(1);

	return 0;
}