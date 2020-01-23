#include "AVGSystem.h"
#include <fstream>



extern IWICImagingFactory* g_image_factory;

extern MSG msg;

extern ID2D1Factory* pD2DFactory;
extern ID2D1HwndRenderTarget* pRenderTarget;
extern ID2D1SolidColorBrush* pBlackBrush;
extern ID2D1Layer* g_pLayer;

extern HWND m_hWnd;

ViewItem Allitems[1024] ;

BOOL getViewformScript(int id, LPCSTR path, ViewItem* lpItem) {
	wifstream scriptObj(path, ios::in);
	if (!scriptObj.is_open()) {
		return FALSE;
	}
	wstring buffer;
	wchar_t flagId[40];
	wsprintf(flagId, L"%s%d%c", L"<id=", id, L'>');
	while (getline(scriptObj, buffer)) {
		if (!_tcsstr(buffer.c_str(), flagId)) continue;
		while (getline(scriptObj, buffer)) {
			const wchar_t* nPoint = NULL;
			if ((nPoint = _tcsstr(buffer.c_str(), L"<background>")) != 0) {
				wstring thisPoint = nPoint;
				thisPoint.erase(0, 12);
				unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</background>") - (unsigned long long)thisPoint.c_str();
				wstring realData = thisPoint.substr(0, posofend/2);
				//lstrcpyW(lpItem->BackGround, realData.c_str());
				lpItem->BackGround = realData.c_str();
				continue;
			}
			if ((nPoint = _tcsstr(buffer.c_str(), L"<bkct>")) != 0) {
				wstring thisPoint = nPoint;
				thisPoint.erase(0, 6);
				unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</bkct>") - (unsigned long long)thisPoint.c_str();
				wstring realData = thisPoint.substr(0, posofend / 2);

				lpItem->BackGroundchangeTime = _wtoi(realData.c_str());
				continue;
			}
			if ((nPoint = _tcsstr(buffer.c_str(), L"<playonce>")) != 0) {
				wstring thisPoint = nPoint;
				thisPoint.erase(0, 10);
				unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</playonce>") - (unsigned long long)thisPoint.c_str();
				wstring realData = thisPoint.substr(0, posofend / 2);

				lstrcpyW(lpItem->playonce, realData.c_str());
				continue;
			}
			if ((nPoint = _tcsstr(buffer.c_str(), L"<auto>")) != 0) {
				wstring thisPoint = nPoint;
				thisPoint.erase(0, 6);
				unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</auto>") - (unsigned long long)thisPoint.c_str();
				wstring realData = thisPoint.substr(0, posofend / 2);
				//lstrcpyW(lpItem->autoChange, realData.c_str());
				lpItem->autoChange = _wtoi(realData.c_str());
				continue;
			}
			if ((nPoint = _tcsstr(buffer.c_str(), L"<text>")) != 0) {
				wstring thisPoint = nPoint;
				thisPoint.erase(0, 6);
				unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</text>") - (unsigned long long)thisPoint.c_str();
				wstring realData = thisPoint.substr(0, posofend / 2);
			lstrcpyW(lpItem->TextStr, realData.c_str());
				continue;
			}
			if ((nPoint = _tcsstr(buffer.c_str(), L"<tx>")) != 0) {
				wstring thisPoint = nPoint;
				thisPoint.erase(0, 4);
				unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</tx>") - (unsigned long long)thisPoint.c_str();
				wstring realData = thisPoint.substr(0, posofend / 2);
				lpItem->tx = _wtoi(realData.c_str());
				//	AfxMessageBox(realData.c_str());
				continue;
			}
			if ((nPoint = _tcsstr(buffer.c_str(), L"<ty>")) != 0) {
				wstring thisPoint = nPoint;
				thisPoint.erase(0, 4);
				unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</ty>") - (unsigned long long)thisPoint.c_str();
				wstring realData = thisPoint.substr(0, posofend / 2);
				lpItem->ty = _wtoi(realData.c_str());
				continue;
			}
			if ((nPoint = _tcsstr(buffer.c_str(), L"<music>")) != 0) {
				wstring thisPoint = nPoint;
				thisPoint.erase(0, 7);
				unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</music>") - (unsigned long long)thisPoint.c_str();
				wstring realData = thisPoint.substr(0, posofend / 2);
				lstrcpyW(lpItem->music, realData.c_str());
				continue;
			}

			if ((nPoint = _tcsstr(buffer.c_str(), L"<buttons=")) != 0) {
				wstring formLete = _tcsstr(nPoint, L"=");
				formLete.erase(0, 1);
				formLete.erase(formLete.length() - 1, 1);

				lpItem->buttonCount = _wtoi(formLete.c_str());
				lpItem->buttons = new ButtonItem[lpItem->buttonCount];
				int thisCountOfb = 0;
				while (getline(scriptObj, buffer)) {
					if (_tcsstr(buffer.c_str(), L"</buttons>") != 0)break;
					if (_tcsstr(buffer.c_str(), L"<button>") != 0)
						while (getline(scriptObj, buffer)) {
							if (_tcsstr(buffer.c_str(), L"</button>") != 0) {
								thisCountOfb++;
								break;
							}
							if ((nPoint = _tcsstr(buffer.c_str(), L"<path1>")) != 0) {
								wstring thisPoint = nPoint;
								thisPoint.erase(0, 7);
								unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</path1>") - (unsigned long long)thisPoint.c_str();
								wstring realData = thisPoint.substr(0, posofend / 2);
								//lstrcpyW(lpItem->buttons[thisCountOfb].path1, realData.c_str());
								lpItem->buttons[thisCountOfb].path1 = realData.c_str();
								continue;
							}
							if ((nPoint = _tcsstr(buffer.c_str(), L"<path2>")) != 0) {
								wstring thisPoint = nPoint;
								thisPoint.erase(0, 7);
								unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</path2>") - (unsigned long long)thisPoint.c_str();
								wstring realData = thisPoint.substr(0, posofend / 2);
								//lstrcpyW(lpItem->buttons[thisCountOfb].path2, realData.c_str());
								lpItem->buttons[thisCountOfb].path2 = realData.c_str();
								//	thisCountOfb++;
								continue;
							}
							if ((nPoint = _tcsstr(buffer.c_str(), L"<event>")) != 0) {
								wstring thisPoint = nPoint;
								thisPoint.erase(0, 7);
								unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</event>") - (unsigned long long)thisPoint.c_str();
								wstring realData = thisPoint.substr(0, posofend / 2);
								lpItem->buttons[thisCountOfb].msg = _wtoi(realData.c_str()) + WM_USER + 100;
								//thisCountOfb++;
								continue;
							}
							if ((nPoint = _tcsstr(buffer.c_str(), L"<px>")) != 0) {
								wstring thisPoint = nPoint;
								thisPoint.erase(0, 4);
								unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</px>") - (unsigned long long)thisPoint.c_str();
								wstring realData = thisPoint.substr(0, posofend / 2);
								lpItem->buttons[thisCountOfb].position.x = _wtoi(realData.c_str());
								//thisCountOfb++;
								continue;
							}
							if ((nPoint = _tcsstr(buffer.c_str(), L"<py>")) != 0) {
								wstring thisPoint = nPoint;
								thisPoint.erase(0, 4);
								unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</py>") - (unsigned long long)thisPoint.c_str();
								wstring realData = thisPoint.substr(0, posofend / 2);
								lpItem->buttons[thisCountOfb].position.y = _wtoi(realData.c_str());
								//thisCountOfb++;
								continue;
							}
						}
				}
			}
			if ((nPoint = _tcsstr(buffer.c_str(), L"<elements=")) != 0) {
				wstring formLete = _tcsstr(nPoint, L"=");
				formLete.erase(0, 1);
				formLete.erase(formLete.length() - 1, 1);

				lpItem->elementCount = _wtoi(formLete.c_str());
				lpItem->elements = new ElementItem[lpItem->elementCount];
				int thisCountOfb = 0;
				while (getline(scriptObj, buffer)) {
					if (_tcsstr(buffer.c_str(), L"</elements>") != 0)break;
					if (_tcsstr(buffer.c_str(), L"<element>") != 0)
						while (getline(scriptObj, buffer)) {
							if (_tcsstr(buffer.c_str(), L"</element>") != 0) {
								thisCountOfb++;
								break;
							}
							if ((nPoint = _tcsstr(buffer.c_str(), L"<path>")) != 0) {
								wstring thisPoint = nPoint;
								thisPoint.erase(0, 6);
								unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</path>") - (unsigned long long)thisPoint.c_str();
								wstring realData = thisPoint.substr(0, posofend / 2);
								//lstrcpyW(lpItem->elements[thisCountOfb].path, realData.c_str());
								lpItem->elements[thisCountOfb].path = realData.c_str();

								continue;
							}
							if ((nPoint = _tcsstr(buffer.c_str(), L"<elct>")) != 0) {
								wstring thisPoint = nPoint;
								thisPoint.erase(0, 6);
								unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</elct>") - (unsigned long long)thisPoint.c_str();
								wstring realData = thisPoint.substr(0, posofend / 2);

								lpItem->elements[thisCountOfb].ChangeTime = _wtoi(realData.c_str());
								continue;
							}
							if ((nPoint = _tcsstr(buffer.c_str(), L"<px>")) != 0) {
								wstring thisPoint = nPoint;
								thisPoint.erase(0, 4);
								unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</px>") - (unsigned long long)thisPoint.c_str();
								wstring realData = thisPoint.substr(0, posofend / 2);
								lpItem->elements[thisCountOfb].position.x = _wtoi(realData.c_str());
								//thisCountOfb++;
								continue;
							}
							if ((nPoint = _tcsstr(buffer.c_str(), L"<py>")) != 0) {
								wstring thisPoint = nPoint;
								thisPoint.erase(0, 4);
								unsigned long long posofend = (unsigned long long)_tcsstr(thisPoint.c_str(), L"</py>") - (unsigned long long)thisPoint.c_str();
								wstring realData = thisPoint.substr(0, posofend / 2);
								lpItem->elements[thisCountOfb].position.y = _wtoi(realData.c_str());
								//thisCountOfb++;
								continue;
							}
						}
				}
			}
			if (_tcsstr(buffer.c_str(), L"</id>"))
				break;
		}
		return TRUE;;
	}

	return FALSE;
}

AVGSYSTEM::AVGSYSTEM(HWND hWnd, DWORD thread)
{
	thisview = new ViewObject(hWnd, thread);
	POINT p;
	p.x = 200;
	p.y = 200;


	//AfxMessageBox("正在加载资源。。");
	NowBk = L"Ining.png";
	thisview->clear();
	thisview->setBkground(thisview->LoadImageTo(L"Ining.png"));
	thisview->complete();
	
	Sleep(3000);
	char nunstr[100];
	for (int i = 0; i < 100; i++) {
		_itoa_s(i,nunstr,10);
		SetWindowTextA(hWnd,nunstr);
		getViewformScript(i, "script.htm", &Allitems[i]);
	}

	//AfxMessageBox("资源已经全部加载完毕。");
	this->OrderView(&Allitems[0]);

	hThread = thread;

	//this->ButtonUpdata();
}

AVGSYSTEM::~AVGSYSTEM()
{
	SAFE_RELEASE(pRenderTarget);
	SAFE_RELEASE(pBlackBrush);
	SAFE_RELEASE(pD2DFactory)
		SAFE_RELEASE(g_pLayer);
}

DWORD WINAPI AutoChangeFlah(LPVOID lPvoid) {
	int* Seconds = (int*)lPvoid;

	Sleep(*Seconds);
	SendMessage(m_hWnd, VIEW_EVENT_NEXT, MEVENT_CLICK, 0);
	delete Seconds;
	return 0;
}

void AVGSYSTEM::OrderView(ViewItem* items) {
	//		this->ChangeBackGround(items->BackGround.c_str(), items->BackGroundchangeTime);

	ID2D1Bitmap * m_BitMap = NULL;

	thisview->clear();

	////////////////////////////////////////////切换背景///////////////////////////////////////////////////////////
	if (items->BackGroundchangeTime == 1) {
		thisview->setBkground(m_BitMap=thisview->LoadImageTo(items->BackGround.c_str()));
		m_BitMap->Release();
	}
	else {
		thisview->setBkground(m_BitMap = thisview->LoadImageTo(NowBk.c_str()));
		thisview->complete();
		for (int i = 0; i <= items->BackGroundchangeTime; i++) {
			thisview->clear();
			thisview->setBkground(m_BitMap = thisview->LoadImageTo(NowBk.c_str()));
			m_BitMap->Release();
			thisview->addElement(m_BitMap = thisview->LoadImageTo(items->BackGround.c_str()), {0,0},NULL, (1.0 / items->BackGroundchangeTime) * i);
			m_BitMap->Release();
			if (items->BackGroundchangeTime != 1)
				thisview->complete();
			Sleep(3);
			//	AfxMessageBox("jjjjjj");
		}
		thisview->clear();
		thisview->setBkground(m_BitMap = thisview->LoadImageTo(items->BackGround.c_str()));
		NowBk = items->BackGround.c_str();
	}
	/////////////////////////////////////////////////////////////////////////////////////////////


	if (this->buttonCount > 0 || this->elementsCount > 0) {
		buttonCount = 0;
		elementsCount = 0;
	}

	if (items->music[0] != 0) {
		thisview->setBkmusic(items->music);
	}

	for (int i = 0; i < items->elementCount; i++) {

		if (items->elements[i].ChangeTime == 1) {
			thisview->addElement(m_BitMap = thisview->LoadImageTo(items->elements[i].path.c_str()), items->elements[i].position, NULL, 1.0f);
			m_BitMap->Release();
		}
		else {
			thisview->complete();
			for (int j = 0; j <= items->elements[i].ChangeTime; j++) {
				thisview->clear();
				thisview->setBkground(m_BitMap = thisview->LoadImageTo(NowBk.c_str()));
				m_BitMap->Release();
				for (int q = 0; q < elementsCount; q++) {
				
					thisview->addElement(m_BitMap = thisview->LoadImageTo(elementsIcon[q]), elementsPoint[q], NULL, 1.0f);
					m_BitMap->Release();
				}

				thisview->addElement(m_BitMap = thisview->LoadImageTo(items->elements[i].path.c_str()), items->elements[i].position, NULL, (1.0 / items->elements[i].ChangeTime) * j);
				m_BitMap->Release();
				if (items->elements[i].ChangeTime != 1)
					thisview->complete();
				Sleep(3);
				//	AfxMessageBox("jjjjjj");
			}
			thisview->clear();
			thisview->setBkground(m_BitMap = thisview->LoadImageTo(NowBk.c_str()));
			m_BitMap->Release();
			for (int q = 0; q < elementsCount; q++) {

				thisview->addElement(m_BitMap = thisview->LoadImageTo(elementsIcon[q]), elementsPoint[q], NULL, 1.0f);
				m_BitMap->Release();
			}
			thisview->addElement(m_BitMap = thisview->LoadImageTo(items->elements[i].path.c_str()), items->elements[i].position, NULL, 1.0f);
			m_BitMap->Release();
		}
		//this->AddElement(items->elements[i].path.c_str(), items->elements[i].position, items->elements[i].ChangeTime);
		
		
		elementsIcon[elementsCount]= items->elements[i].path.c_str();
		elementsPoint[elementsCount] = items->elements[i].position;
		elementsCount++;
	}
	for (int i = 0; i < items->buttonCount; i++) {
		buttonIconon[buttonCount]=items->buttons[i].path1.c_str();
		buttonIconoff[buttonCount]= items->buttons[i].path2.c_str();
		buttonEvents[buttonCount] = items->buttons[i].msg;
		buttonPoint[buttonCount] = items->buttons[i].position;
		buttonCount++;

		this->thisview->addElement(m_BitMap = thisview->LoadImageTo(items->buttons[i].path1.c_str()), items->buttons[i].position, items->buttons[i].msg, 1.0f);
		m_BitMap->Release();

		//this->AddButton(items->buttons[i].path1.c_str(), items->buttons[i].path2.c_str(), items->buttons[i].position, items->buttons[i].msg);
	}


	if (items->autoChange > 0) {
		int* FlagNow = new int;
		*FlagNow = items->autoChange;
		HANDLE hChangeAuto = CreateThread(NULL, NULL, AutoChangeFlah, FlagNow, 0, 0);
		CloseHandle(hChangeAuto);
	}


	if (items->playonce[0] != 0) {
		//thisview->Text2Img(items->TextStr, items->tx, items->ty, 255, 255, 255);
		//this->PlayMusicOnce(items->playonce);
		PlaySound(items->playonce, NULL, SND_FILENAME | SND_ASYNC);
	}
	thisview->complete();
}

