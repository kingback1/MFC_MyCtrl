#介绍

visual studio 13 MFC原生态的简单的自动刷新控件，用的是宿主窗口DC，没用派生类。

#安装


此MFC工程用cmake构建。建立build目录，在build下用命令`cmake ..`即可创建工程。


#此控件类用法

1. 在对话框或窗口类头文件包含控件头文件

```
    #include "MyCtrl.h".
```

2. 在对话框头或窗口类头文件定义控件变量

```
    private:
        CMyCtrl xCtrl;
```

3. 在对话框或窗口类源文件初始化的地方创建控件

```
    BOOL CTestDlg::OnInitDialog()
    {
        CDialog::OnInitDialog();

        SetIcon(m_hIcon, TRUE);            // Set big icon
        SetIcon(m_hIcon, FALSE);        // Set small icon

        xCtrl.Create(10,10,500,300,this); //创建控件
        xCtrl.SetFlashFrev(50);//设置刷新频率
        return TRUE;
    }
```

4. 在对话框或窗口类源文件OnPaint里现实控件

```
    void CTestDlg::OnPaint()
    {
        CPaintDC dc(this);
        xCtrl.Show(&dc);//显示控件
    }
```

5. 用向导给对话框或窗口类增加函数UpdateMyCtrl

```
    LRESULT CTestDlg::UpdateMyCtrl(WPARAM hKey, LPARAM lKey)
    {
        InvalidateRect((CRect *)hKey);
    }
```

6. 给对话框或窗口类添加消息映射

```
    BEGIN_MESSAGE_MAP(CTestDlg, CDialog)

        ON_WM_PAINT()
        ON_WM_QUERYDRAGICON()
        ON_WM_ERASEBKGND()

        ON_MESSAGE(SSSEX,UpdateMyCtrl) //这个是增加的
    END_MESSAGE_MAP()
```