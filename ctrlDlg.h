
// ctrlDlg.h : ͷ�ļ�
//

#pragma once
#include "MyCtrl.h"

// CctrlDlg �Ի���
class CctrlDlg : public CDialogEx
{
// ����
public:
	CctrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	LRESULT UpdateMyCtrl(WPARAM hKey, LPARAM lKey);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CMyCtrl xCtrl;
};
