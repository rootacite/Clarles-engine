#include "AVGSystem.h"

extern MSG msg;

extern ID2D1Factory* pD2DFactory;
extern ID2D1HwndRenderTarget* pRenderTarget;
extern ID2D1SolidColorBrush* pBlackBrush;
extern ID2D1Layer* g_pLayer;
IWICImagingFactory* g_image_factory = NULL;

AVGSYSTEM *sysObject = NULL;


int WINAPI _tWinMain(
	_In_ HINSTANCE hInst,
	_In_ HINSTANCE provHInst,
	_In_ LPTSTR cmdLine,
	_In_ int nCmdShow
) {
	//MessageBox(0,L"",L"",0);
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof(g_image_factory), (LPVOID*)&g_image_factory);

	HWND m_hWnd; 
	if (!(m_hWnd = WindowInit(hInst, nCmdShow))) {
		MessageBox(0, L"fail to create window", L"error", MB_ICONERROR);
		return -1;
	}
	//MainView = new ViewObject(m_hWnd, GetCurrentThreadId());
	sysObject = new AVGSYSTEM(m_hWnd, GetCurrentThreadId());
	HANDLE hThread = CreateThread(NULL, 0, renderThread, NULL, 0, NULL);

	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

		}
	}

	CloseHandle(hThread);
	UnregisterClass(WND_CLASSNAME,hInst);

	return 0;
}

