
#include "AVGSystem.h"

LRESULT CALLBACK MouseEventProc(int nCode, WPARAM wParam, LPARAM lParam);
BOOL isDrawing =NULL;

extern ID2D1Factory* pD2DFactory;
extern ID2D1HwndRenderTarget* pRenderTarget;
extern ID2D1SolidColorBrush* pBlackBrush;
extern ID2D1Layer* g_pLayer;




ViewObject::ViewObject(HWND hWnd, DWORD thread)
{
	ZeroMemory(eventArea, 100 * sizeof(RECT));
	ZeroMemory(isInArea, 100 * sizeof(BOOL));
	ZeroMemory(msgList, 100 * sizeof(UINT));
	directXInit(hWnd, NULL);
	this->m_hWnd = hWnd;

	ccThreadId = thread;

	hMouse=SetWindowsHookEx(WH_MOUSE, MouseEventProc,NULL, ccThreadId);
}
ViewObject::~ViewObject()
{
	if (hMouse != NULL) {
		UnhookWindowsHookEx(hMouse);
	}
}

BOOL PointInRect(POINT p, RECT rect) {
	if ((p.x > rect.left&& p.x < rect.right) && (p.y > rect.top&& p.y < rect.bottom))
		return TRUE;
	else
		return FALSE;
}
int ViewObject::addElement(ID2D1Bitmap* elementIni, POINT area, UINT msg, double Tranl) {

	//	Mat elementIni = imread(path.c_str(),-1);
	if (elementIni==NULL) {
		return -1;
	}
	D2D1_SIZE_F size = elementIni->GetSize();
	D2D1_RECT_F imgr = { area.x, area.y, area.x + size.width, area.y + size.height };
	if (msg != NULL) {
		RECT onceRect;
		onceRect.left = area.x;
		onceRect.top = area.y;
		onceRect.right = area.x + size.width;
		onceRect.bottom = area.y + size.height;

		eventArea[eventCount] = onceRect;
		msgList[eventCount] = msg;

		POINT pMou;
		GetCursorPos(&pMou);
		ScreenToClient(m_hWnd, &pMou);


		isInArea[eventCount] = PointInRect(pMou, eventArea[eventCount]);
		eventCount++;

	}
	

	pRenderTarget->PushLayer(
		D2D1::LayerParameters(imgr, NULL, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE, D2D1::IdentityMatrix(),
			Tranl,NULL, D2D1_LAYER_OPTIONS_NONE),
		g_pLayer
	);

	//pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	pRenderTarget->DrawBitmap(elementIni, imgr);

	//pRenderTarget->DrawRectangle(imgr,pBlackBrush);
	pRenderTarget->PopLayer();

	//Mat imageROI = View(Rect(area.x, area.y, elementIni.cols, elementIni.rows));

	//Mat2CImage(&View,m_Image);
	return eventCount;
}


BOOL ViewObject::setBkground(ID2D1Bitmap* path)
{
	D2D1_SIZE_F size = pRenderTarget->GetSize();
	D2D1_RECT_F imgr = { 0, 0, size.width, size.height };

	pRenderTarget->PushLayer(
		D2D1::LayerParameters(),
		g_pLayer
	);

	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	pRenderTarget->DrawBitmap(path, imgr);
	pRenderTarget->PopLayer();


	return TRUE;
}

BOOL ViewObject::complete() {
	isDrawing = FALSE;

	if (musicPath != NULL) {
		PlaySoundW(NULL, NULL, SND_FILENAME);
		PlaySoundW(musicPath, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	//Mat2CImage(&View, m_Image);
	pRenderTarget->EndDraw();
	return 0;
}

void ViewObject::clear() {
	isDrawing = TRUE;

	eventCount = 0;
	musicPath = NULL;


	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void ViewObject::clearWithoutEvent() {
	isDrawing = TRUE;

	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

BOOL ViewObject::setBkmusic(wstring path) {

	if (musicPath != NULL)
		delete[] musicPath;
	musicPath = new wchar_t[path.length() + 1];

   lstrcpyW(musicPath, path.c_str());
	this->m_Bkmusic = path.c_str();

	//	Mat2CImage(&View, m_Image);
	return 0;
}
extern AVGSYSTEM* sysObject;
LRESULT CALLBACK MouseEventProc(int nCode, WPARAM wParam, LPARAM lParam) {
	while (isDrawing)
		Sleep(1);
	POINT pm;
	GetCursorPos(&pm);
	ScreenToClient(sysObject->thisview->m_hWnd, &pm);

	switch (wParam) {
	case WM_MOUSEMOVE:
		for (int i = 0; i < sysObject->thisview->eventCount; i++)
			if (PointInRect(pm, sysObject->thisview->eventArea[i])) {
				if (!sysObject->thisview->isInArea[i])
				{
					sysObject->thisview->isInArea[i] = TRUE;
					SendMessage(sysObject->thisview->m_hWnd, sysObject->thisview->msgList[i], MEVENT_MOVEIN, NULL);
				}
			}
			else {
				if (sysObject->thisview->isInArea[i]) {
					sysObject->thisview->isInArea[i] = FALSE;
					SendMessage(sysObject->thisview->m_hWnd, sysObject->thisview->msgList[i], MEVENT_MOVEOUT, NULL);
				}
			}
		break;
	case WM_LBUTTONDOWN:
		for (int i = 0; i < sysObject->thisview->eventCount; i++)
			if (PointInRect(pm, sysObject->thisview->eventArea[i])) {
				SendMessage(sysObject->thisview->m_hWnd, sysObject->thisview->msgList[i], MEVENT_CLICK, NULL);
			}
		break;
	default:
		break;
	}

	return CallNextHookEx(sysObject->thisview->hMouse, nCode, wParam, lParam);

}



extern IWICImagingFactory* g_image_factory ;


ID2D1Bitmap* ViewObject::LoadImageTo(wstring path)
{
	ID2D1Bitmap* ReturnCalue = NULL;


	IWICBitmapDecoder* bitmapdecoder = NULL;
	g_image_factory->CreateDecoderFromFilename(path.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &bitmapdecoder);//
	if (!bitmapdecoder)
		MessageBox(0, L"cannot find res", L"error", MB_ICONERROR);
	IWICBitmapFrameDecode* pframe = NULL;
	bitmapdecoder->GetFrame(0, &pframe);

	IWICFormatConverter* fmtcovter = NULL;
	g_image_factory->CreateFormatConverter(&fmtcovter);
	fmtcovter->Initialize(pframe, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	pRenderTarget->CreateBitmapFromWicBitmap(fmtcovter, NULL, &ReturnCalue);

	fmtcovter->Release();
	pframe->Release();
	bitmapdecoder->Release();

	return ReturnCalue;
}