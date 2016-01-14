#ifndef  _MYCTRL_H_
#define  _MYCTRL_H_

#define  SSSEX 0x1234                        //自定义消息，十进制4660

void WINAPI MyTimer(LPVOID lpParam);         //定时器

class  CMyCtrl
{
public:

	//供宿主窗口显示时候调用
	void Show(CDC *pDC);

	//供宿主窗口设置刷新周期时候调用
	void SetFlashFrev(long freq);

	//供定时器调用进行刷新
	void Update();

	//供宿主窗口创建本控件的时候调用
	BOOL Create(int x, int y, int w, int h, CWnd *Parent);

	CMyCtrl();
	~CMyCtrl();

protected:
	//控件本身绘图
	void OnDraw(CDC *pDC);

	//需要刷新的数据计算
	void OnFlash();

private:
	HWND   mParent;      //宿主窗句柄
	CRect  mRect;        //占据宿主窗口的地盘位置
	long   sx;           //在宿主窗的占据位置的起点x
	long   sy;           //在宿主窗的占据位置的起点y
	long   width;        //在宿主窗的占据地盘的宽度
	long   heigh;        //在宿主窗的占据地盘的高度

	long   fFreq;        //刷新周期

	COLORREF bkColor;    //背景颜色
	COLORREF tColor;     //文本颜色

	DWORD  idTimer;
	HANDLE thTimer;

	long mx;             //这个数据是拿来演示用的
	long my;             //这个数据是拿来演示用的
};

#endif