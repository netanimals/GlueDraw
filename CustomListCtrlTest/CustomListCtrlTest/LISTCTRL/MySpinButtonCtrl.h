#if !defined(AFX_MYSPINBUTTONCTRL_H__6099357B_1235_4A35_954B_E0E120BBE704__INCLUDED_)
#define AFX_MYSPINBUTTONCTRL_H__6099357B_1235_4A35_954B_E0E120BBE704__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySpinButtonCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMySpinButtonCtrl window

class CMySpinButtonCtrl : public CSpinButtonCtrl
{
// Construction
public:
	CMySpinButtonCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySpinButtonCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMySpinButtonCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMySpinButtonCtrl)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPINBUTTONCTRL_H__6099357B_1235_4A35_954B_E0E120BBE704__INCLUDED_)
