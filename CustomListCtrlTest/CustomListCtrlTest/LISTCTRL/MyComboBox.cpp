// MyComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "MyComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyComboBox
#define WM_COMBOBOXEND	WM_USER+101
CMyComboBox::CMyComboBox()
{
}

CMyComboBox::~CMyComboBox()
{
}


BEGIN_MESSAGE_MAP(CMyComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMyComboBox)
	ON_WM_KILLFOCUS()
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyComboBox message handlers

void CMyComboBox::OnKillFocus(CWnd* pNewWnd) 
{
	CComboBox::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
}


void CMyComboBox::OnSelchange() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->m_hWnd, WM_COMBOBOXEND, 1, 0);
}

void CMyComboBox::OnKillfocus() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->m_hWnd, WM_COMBOBOXEND, 0, 0);
}
