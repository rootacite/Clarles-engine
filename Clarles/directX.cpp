#include "elements.h"

ID2D1Factory* pD2DFactory = NULL;
ID2D1HwndRenderTarget* pRenderTarget = NULL;
ID2D1SolidColorBrush* pBlackBrush = NULL;
ID2D1Layer* g_pLayer = NULL;

RECT m_RenderArea = {0};


int directXInit(HWND hWnd, HINSTANCE hInst) {
	GetClientRect(hWnd, &m_RenderArea);
	
	HRESULT hrFory;
	hrFory =
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (FAILED(hrFory))
		return 0;
	hrFory=pD2DFactory->CreateHwndRenderTarget
	(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties
		(
			hWnd,
			D2D1::SizeU(m_RenderArea.right - m_RenderArea.left, m_RenderArea.bottom - m_RenderArea.top)
		),
		&pRenderTarget
	);
	if (FAILED(hrFory))
		return 0;

	hrFory = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBlackBrush);
	if (FAILED(hrFory))
		return 0;
	hrFory = pRenderTarget->CreateLayer(NULL, &g_pLayer);
	if (FAILED(hrFory))
		return 0;


	return 1;

}