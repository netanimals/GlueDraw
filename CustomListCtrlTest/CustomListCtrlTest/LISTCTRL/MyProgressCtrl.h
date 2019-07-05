#if !defined(AFX_MYPROGRESSCTRL_H__17917C22_5D4C_4A69_9462_7C88B7D468B3__INCLUDED_)
#define AFX_MYPROGRESSCTRL_H__17917C22_5D4C_4A69_9462_7C88B7D468B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyProgressCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyProgressCtrl window

class CMyProgressCtrl : public CProgressCtrl
{
// Construction
public:
	CMyProgressCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyProgressCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyProgressCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyProgressCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROGRESSCTRL_H__17917C22_5D4C_4A69_9462_7C88B7D468B3__INCLUDED_)
