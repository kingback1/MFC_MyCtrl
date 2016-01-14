#include "stdafx.h"
#include "MyCtrl.h"

void WINAPI MyTimer(LPVOID lpParam) //���Ǽ�ʱ�����̺߳�����ˢ�»�����
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
	//����Ϊ1000ms��1���ˢ��Ƶ��
	fFreq = 1000;  

	//����ɫ 
	bkColor = RGB(123, 104, 238);
	//�ı�ɫ
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
	::PostMessage(mParent, SSSEX, (WPARAM)&mRect, 0);//���������ڷ���ˢ����Ϣ
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
///    ��Ҫ����������������̬�仯�Ĵ���ӵ�OnFlash���ͼ�Ĵ���ӵ�OnDraw��                      ///
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
		_T("��ǰ���¹⣬"),
		_T("���ǵ���˪��"),
		_T("��ͷ�����£�"),
		_T("��ͷ˼���硣"),
	};
	CRect xr;

	CFont xFont, *oFont;
	xFont.CreateFont(50, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (LPCTSTR)("����"));
	oFont = pDC->SelectObject(&xFont);
	xr.SetRect(20, my, 480, my + 60);
	pDC->DrawText(_T("��ҹ˼"), xr, 0x20);
	pDC->SelectObject(oFont);
	xFont.DeleteObject();

	xFont.CreateFont(20, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (LPCTSTR)("����"));
	oFont = pDC->SelectObject(&xFont);
	xr.SetRect(20, my + 60, 480, my + 85);
	pDC->DrawText(_T("     ���ߣ����"), xr, 0x20);
	pDC->SelectObject(oFont);
	xFont.DeleteObject();

	xFont.CreateFont(30, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (LPCTSTR)"����");
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
