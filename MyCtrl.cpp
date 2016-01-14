#include "stdafx.h"
#include "MyCtrl.h"

void WINAPI MyTimer(LPVOID lpParam) //这是计时器用线程函数，刷新绘制区
{
	CMyCtrl *k = (CMyCtrl *)lpParam;
	if (NULL == k)	return;
	while (true)	k->Update();
}

CMyCtrl::CMyCtrl()
{
	mParent = NULL;
	mRect.SetRect(0, 0, 0, 0);
	sx = 0;
	sy = 0;
	width = 0;
	heigh = 0;
	//初设为1000ms即1秒的刷新频率
	fFreq = 1000;  

	//背景色 
	bkColor = RGB(123, 104, 238);
	//文本色
	tColor = RGB(255, 220, 160); 

	mx = 0;
	my = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
CMyCtrl::~CMyCtrl()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void CMyCtrl::Update()
{
	OnFlash();
	::PostMessage(mParent, SSSEX, (WPARAM)&mRect, 0);//向宿主窗口发送刷新消息
	Sleep(fFreq);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void CMyCtrl::SetFlashFrev(long freq)
{
	fFreq = freq;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void CMyCtrl::Show(CDC *pDC)
{
	CDC mDC;
	CBitmap mBK, *oBK;
	mDC.CreateCompatibleDC(pDC);
	mBK.CreateCompatibleBitmap(pDC, width, heigh);
	oBK = mDC.SelectObject(&mBK);
	mDC.FillSolidRect(0, 0, width, heigh, bkColor);
	mDC.SetBkMode(0);
	mDC.SetTextColor(tColor);
	OnDraw(&mDC);
	pDC->BitBlt(sx, sy, width, heigh, &mDC, 0, 0, SRCCOPY);
	mDC.SelectObject(oBK);
	mDC.DeleteDC();
	mBK.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMyCtrl::Create(int x, int y, int w, int h, CWnd *Parent)
{
	if (Parent == NULL) return FALSE;
	mParent = Parent->m_hWnd;
	mRect.SetRect(x, y, x + w, y + h);
	sx = x;
	sy = y;
	width = w;
	heigh = h;
	thTimer = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyTimer, LPVOID(this), 0, &idTimer);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                               ///
///    主要就是这两函数，动态变化的代码加到OnFlash里，画图的代码加到OnDraw里                      ///
///                                                                                               ///
/////////////////////////////////////////////////////////////////////////////////////////////////////

void CMyCtrl::OnFlash()
{
	my--;
	if (my <= -660) my = 300;
}

void CMyCtrl::OnDraw(CDC *pDC)
{
	CString ss[4] =
	{
		_T("床前明月光，"),
		_T("疑是地上霜。"),
		_T("举头望明月，"),
		_T("低头思故乡。"),
	};
	CRect xr;

	CFont xFont, *oFont;
	xFont.CreateFont(50, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (LPCTSTR)("宋体"));
	oFont = pDC->SelectObject(&xFont);
	xr.SetRect(20, my, 480, my + 60);
	pDC->DrawText(_T("静夜思"), xr, 0x20);
	pDC->SelectObject(oFont);
	xFont.DeleteObject();

	xFont.CreateFont(20, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (LPCTSTR)("宋体"));
	oFont = pDC->SelectObject(&xFont);
	xr.SetRect(20, my + 60, 480, my + 85);
	pDC->DrawText(_T("     作者：李白"), xr, 0x20);
	pDC->SelectObject(oFont);
	xFont.DeleteObject();

	xFont.CreateFont(30, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (LPCTSTR)"黑体");
	oFont = pDC->SelectObject(&xFont);
	xr.SetRect(20, my + 60, 480, my + 100);
	for (int i = 0; i<4; i++)
	{
		xr.OffsetRect(0, 40);
		pDC->DrawText(ss[i], xr, 0x20);
	}

	pDC->SelectObject(oFont);
	xFont.DeleteObject();
}
