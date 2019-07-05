#if !defined(AFX_MYEDIT_H__33215100_2563_43ED_A9FE_1FB201A01C29__INCLUDED_)
#define AFX_MYEDIT_H__33215100_2563_43ED_A9FE_1FB201A01C29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyEdit.h : header file
//
#define WM_EDITEND	WM_USER+100
/////////////////////////////////////////////////////////////////////////////
// CMyEdit window

class CMyEdit : public CEdit
{
// Construction
public:
	CMyEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEdit)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	bool	m_bKeyInput;		//键盘输入
	double	m_fKeyPrecision;	//输入精度
	bool	m_bFont;
	CFont	m_Font;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEDIT_H__33215100_2563_43ED_A9FE_1FB201A01C29__INCLUDED_)
