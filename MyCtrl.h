#ifndef  _MYCTRL_H_
#define  _MYCTRL_H_

#define  SSSEX 0x1234                        //�Զ�����Ϣ��ʮ����4660

void WINAPI MyTimer(LPVOID lpParam);         //��ʱ��

class  CMyCtrl
{
public:

	//������������ʾʱ�����
	void Show(CDC *pDC);

	//��������������ˢ������ʱ�����
	void SetFlashFrev(long freq);

	//����ʱ�����ý���ˢ��
	void Update();

	//���������ڴ������ؼ���ʱ�����
	BOOL Create(int x, int y, int w, int h, CWnd *Parent);

	CMyCtrl();
	~CMyCtrl();

protected:
	//�ؼ������ͼ
	void OnDraw(CDC *pDC);

	//��Ҫˢ�µ����ݼ���
	void OnFlash();

private:
	HWND   mParent;      //���������
	CRect  mRect;        //ռ���������ڵĵ���λ��
	long   sx;           //����������ռ��λ�õ����x
	long   sy;           //����������ռ��λ�õ����y
	long   width;        //����������ռ�ݵ��̵Ŀ��
	long   heigh;        //����������ռ�ݵ��̵ĸ߶�

	long   fFreq;        //ˢ������

	COLORREF bkColor;    //������ɫ
	COLORREF tColor;     //�ı���ɫ

	DWORD  idTimer;
	HANDLE thTimer;

	long mx;             //���������������ʾ�õ�
	long my;             //���������������ʾ�õ�
};

#endif