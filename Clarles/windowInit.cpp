#include "AVGSystem.h"


WNDCLASSEX wc = { 0 };
HWND m_hWnd = NULL;
MSG msg;

extern ID2D1Factory* pD2DFactory;
extern ID2D1HwndRenderTarget* pRenderTarget;
extern ID2D1SolidColorBrush* pBlackBrush;
extern ID2D1Layer* g_pLayer;
extern ViewObject* MainView;

int nowFarm = 0;
extern AVGSYSTEM* sysObject;
extern ViewItem Allitems[1024];

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	ID2D1Bitmap* m_Bitmap = NULL;
	switch (msg) {
	case VIEW_EVENT_START: {
		if (wParam == MEVENT_CLICK) {
			nowFarm = 1;
			sysObject->OrderView(&Allitems[nowFarm]);

			//	delete items;
		}
		break;
	}
	case VIEW_EVENT_NEXT: {
		if (wParam == MEVENT_CLICK) {
			nowFarm += 1;
			sysObject->OrderView(&Allitems[nowFarm]);
			//	delete items;
		}
		break;
	}
	case VIEW_EVENT_EXIT: {
		if (wParam == MEVENT_CLICK) {
			DestroyWindow(hWnd);
		}
		break;
	}
	case WM_DESTROY:
			PostQuitMessage(9);
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND WindowInit(HINSTANCE hInst, int nCmdShow) {
	wc = {
	sizeof(WNDCLASSEX),
	WND_COLSTYLE,
	WND_CALLBACKROC,
	0,
	0,
	hInst,
	WND_ICON,
	LoadCursor(NULL,IDC_ARROW),
	WND_BKGROUND,
	WND_MENUNAME,
	WND_CLASSNAME,
	WND_ICONSM
	};

	RegisterClassEx(&wc);

	m_hWnd = CreateWindow(WND_CLASSNAME, WND_TITLE,
		WND_WNDSTYLE,0, 0,1296, 759,
		GetDesktopWindow(), NULL, hInst, NULL);

	if (!m_hWnd) {
		return 0;
	}

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return m_hWnd;
}