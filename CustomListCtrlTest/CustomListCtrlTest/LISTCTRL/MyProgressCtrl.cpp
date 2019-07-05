// MyProgressCtrl.cpp : implementation file
//

#include "stdafx.h"
/*#include "md380.h"*/
#include "MyProgressCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyProgressCtrl

CMyProgressCtrl::CMyProgressCtrl()
{
}

CMyProgressCtrl::~CMyProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyProgressCtrl, CProgressCtrl)
	//{{AFX_MSG_MAP(CMyProgressCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyProgressCtrl message handlers

void CMyProgressCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	int lower, upper;
	GetRange(lower, upper);
	int pos=GetPos();
	CString sPercent;
	sPercent.Format(_T("%d%%"),int(pos*1.0/(upper-lower)*100));
	CRect rect;
	GetClientRect(rect);
	int width=int(pos*1.0/(upper-lower)*rect.Width());
	CRect fillrect;
	fillrect.left=rect.left;
	fillrect.top=rect.top;
	fillrect.bottom=rect.bottom;
	fillrect.right=width;
	CBrush fbrush,hbrush;
	hbrush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	dc.FillRect(rect,&hbrush);
	fbrush.CreateSolidBrush(RGB(128,128,255));
	dc.FillRect(fillrect,&fbrush);
	CFont font, *pOldfont;
//  	font.CreateFont(0,20,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS 
//  ,DEFAULT_QUALITY ,DEFAULT_PITCH,NULL);
	font.CreatePointFont(120,_T("ËÎÌו"));
	pOldfont=dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);
//	dc.SetBkColor(GetSysColor(COLOR_3DFACE ));
	dc.DrawText(sPercent,rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	dc.SelectObject(pOldfont);

	// Do not call CProgressCtrl::OnPaint() for painting messages
}
