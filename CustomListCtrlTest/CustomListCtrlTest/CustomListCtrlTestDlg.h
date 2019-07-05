
// CustomListCtrlTestDlg.h : ͷ�ļ�
//

#pragma once

#include ".\LISTCTRL\MyListCtrl.h"
#include "afxcmn.h"

// CCustomListCtrlTestDlg �Ի���
class CCustomListCtrlTestDlg : public CDialog
{
// ����
public:
	CCustomListCtrlTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CUSTOMLISTCTRLTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()


public:
	CMyListCtrl	m_ListCtrl;
	CStringArray m_arrHeader;
	CStringArray m_arrMCType;
	CStringArray m_arrGlueSwitch;
	CStringArray m_arrSignMode;
	CSliderCtrl m_SliderVel;
	
	void Format2String(const CString& _Content, CStringArray& _Items, CString _Spearator = _T(" "));
	void TestArray(CStringArray& _Items);
};
