// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEdit

CMyEdit::CMyEdit()
{
	m_bKeyInput	= false;		//键盘输入
	m_fKeyPrecision = 0.01;		//输入精度

	m_bFont = false;
	m_Font.CreatePointFont(100, L"黑体");

}

CMyEdit::~CMyEdit()
{
	m_Font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers

void CMyEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	::PostMessage(GetParent()->m_hWnd, WM_EDITEND, 0, 0);
}

void CMyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN)
	{
		::PostMessage(GetParent()->m_hWnd, WM_EDITEND, 1, 0);
	}

	if (m_bKeyInput)
	{
		if (nChar == VK_UP)
		{
			CString str;
			// 获取原来编辑框中的字符串
			GetWindowText(str);

			double _fVal = 0.0;
			_fVal = _ttof(str);

			_fVal += m_fKeyPrecision;
			str.Format(L"%0.3f", _fVal);
			SetWindowText(str);
		}
		if (nChar == VK_DOWN)
		{
			CString str;
			// 获取原来编辑框中的字符串
			GetWindowText(str);

			double _fVal = 0.0;
			_fVal = _ttof(str);

			_fVal -= m_fKeyPrecision;
			str.Format(L"%0.3f", _fVal);
			SetWindowText(str);
		}
		if (nChar == VK_LEFT)
		{

		}
		if (nChar == VK_RIGHT)
		{

		}

	}

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CMyEdit::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		::PostMessage(GetParent()->m_hWnd, WM_EDITEND, 2, 0);
		return TRUE;
	}

	return CEdit::PreTranslateMessage(pMsg);
}
