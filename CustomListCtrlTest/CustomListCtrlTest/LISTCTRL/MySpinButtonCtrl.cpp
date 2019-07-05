// MySpinButtonCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MySpinButtonCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySpinButtonCtrl
#define WM_SPINBUTTONCTRL	WM_USER+102
CMySpinButtonCtrl::CMySpinButtonCtrl()
{
}

CMySpinButtonCtrl::~CMySpinButtonCtrl()
{
}


BEGIN_MESSAGE_MAP(CMySpinButtonCtrl, CSpinButtonCtrl)
	//{{AFX_MSG_MAP(CMySpinButtonCtrl)
	ON_WM_VSCROLL()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySpinButtonCtrl message handlers

void CMySpinButtonCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CSpinButtonCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMySpinButtonCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CSpinButtonCtrl::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	::PostMessage(GetParent()->m_hWnd, WM_SPINBUTTONCTRL, 0, 0);
}
