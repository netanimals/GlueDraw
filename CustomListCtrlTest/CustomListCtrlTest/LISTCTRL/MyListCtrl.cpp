// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl
#define WM_EDITEND					WM_USER+100
#define WM_COMBOBOXEND				WM_USER+101
#define WM_SPINBUTTONCTRL			WM_USER+102


#define ID_MY_CONTROL_EDIT			2000
#define ID_MY_CONTROL_COMBOBOX		2001
#define ID_MY_CONTROL_SPINBUTTON	2002

CMyListCtrl::CMyListCtrl()
{
	Construct();
}

void CMyListCtrl::Construct()
{
	m_fontWith			=(8);
	m_fontHeight		=(16);
	m_fontName			= L"黑体";
	m_nRowHeight		= 36;
	m_nItemClick		= -1;
	m_nSubItemClick		= -1;
	m_nItemDblClick		= -1;
	m_nSubItemDblClick	= -1;
	m_rectSubItem		= CRect(0,0,0,0);

	m_clrRowCurrent[0]	= RGB(0,128,0);			//255,128,32
	m_clrRowCurrent[1]	= RGB(128,0,128);
	m_clrRowModified[0]	= RGB(255,128,32);
	m_clrRowModified[1]	= RGB(255,255,255);

	m_edit.Create(WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, CRect(0, 0, 0, 0), this, ID_MY_CONTROL_EDIT);
	m_combobox.Create(WS_CHILD|WS_VSCROLL|CBS_DROPDOWN|CBS_DROPDOWNLIST, CRect(0, 0, 0, 0), this, ID_MY_CONTROL_COMBOBOX);
	m_spinbutton.Create(WS_CHILD|UDS_SETBUDDYINT|UDS_AUTOBUDDY|UDS_ALIGNRIGHT , CRect(0, 0, 0, 0), this, ID_MY_CONTROL_SPINBUTTON);

}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_MEASUREITEM()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_MESSAGE(WM_EDITEND,			&CMyListCtrl::OnEditEnd)
	ON_MESSAGE(WM_COMBOBOXEND,		&CMyListCtrl::OnComboBoxEnd)
	ON_MESSAGE(WM_SPINBUTTONCTRL,	&CMyListCtrl::OnSpinButtonCtrlEnd)
//	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

int CMyListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	ModifyStyle(0,LVS_OWNERDRAWFIXED);
	CHeaderCtrl *pHeader = GetHeaderCtrl();
	m_Header.SubclassWindow(pHeader->GetSafeHwnd());

	return 0;
}

void CMyListCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	//ModifyStyle(0,LVS_OWNERDRAWFIXED);
	//
	//CHeaderCtrl *pHeader = GetHeaderCtrl();
	//m_Header.SubclassWindow(pHeader->GetSafeHwnd());
	CListCtrl::PreSubclassWindow();
}
void CMyListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//TRACE1("%d\r\n", nChar);
	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyListCtrl::SetRowHeigt(int nHeight)
{
	m_nRowHeight = nHeight;
	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}
void CMyListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
void CMyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (m_nRowHeight>0)
	{
		lpMeasureItemStruct->itemHeight = m_nRowHeight;
	}
}

void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	int _nRow = 0;
	_nRow = lpDrawItemStruct->itemID;

	// TODO:  添加您的代码以绘制指定项
	// TODO: Add your code to draw the specified item  
	ASSERT(lpDrawItemStruct->CtlType == ODT_LISTVIEW);  
	CDC dc;   
	dc.Attach(lpDrawItemStruct->hDC);  
	ASSERT(NULL != dc.GetSafeHdc());  
	// Save these value to restore them when done drawing.  
	COLORREF crOldTextColor = dc.GetTextColor();  
	COLORREF crOldBkColor = dc.GetBkColor();  

	// If this item is selected, set the background color   
	// and the text color to appropriate values. Also, erase  
	// rect by filling it with the background color.  
	if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&  
		(lpDrawItemStruct->itemState & ODS_SELECTED))  
	{  
		dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)); 
		dc.FillSolidRect(&lpDrawItemStruct->rcItem,::GetSysColor(COLOR_HIGHLIGHT));  
	}  
	else  
	{  
		
		//单元格颜色
		if (m_Data.GetDataCanColor())
		{
			//每列
			for (int _nCol=0;_nCol<GetHeaderCtrl()->GetItemCount(); ++_nCol)
			{
				CRect rcItem;
				GetSubItemRect(_nRow,_nCol,LVIR_LABEL,rcItem);

				if (0 == _nCol)
				{
					rcItem.left -=3;
				}

				COLORREF _clrBk = m_Data.GetDataBkColor(_nRow, _nCol);
				COLORREF _clrFg = m_Data.GetDataFgColor(_nRow, _nCol);
				dc.FillSolidRect(&rcItem, _clrBk);
				dc.SetTextColor(_clrFg);
			}
			
		}
		if (m_Data.ListCtrlHasData())
		{
			//数据修改行
			if (m_Data.GetData(lpDrawItemStruct->itemID, 0).UnitIsModified())
			{
				dc.SetTextColor(m_clrRowModified[1]);
				//dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
				dc.FillSolidRect(&lpDrawItemStruct->rcItem, m_clrRowModified[0]);
			}
			//指令当前运行
			if (lpDrawItemStruct->itemID == m_Data.GetRowCurrent())
			{
				dc.SetTextColor(m_clrRowCurrent[1]);
				//dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
				dc.FillSolidRect(&lpDrawItemStruct->rcItem, m_clrRowCurrent[0]);
			}
		}
	}  

	// If this item has the focus, draw a red frame around the item's rect
	if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&  
		(lpDrawItemStruct->itemState & ODS_FOCUS))  
	{  
		CBrush br(RGB(0xff,0x99,0x0));  //RGB(0xff,0x99,0x0)
		dc.FrameRect(&lpDrawItemStruct->rcItem, &br);  
	}  


	// Draw the text.  
	CString strText(_T(""));  
	CRect rcItem;  

	for(int _nCol=0; _nCol<GetHeaderCtrl()->GetItemCount(); _nCol++)  
	{  
		COLORREF _clrFg = m_Data.GetDataFgColor(_nRow, _nCol);
		dc.SetTextColor(_clrFg);

		CFont nFont ,* nOldFont; 
		nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("宋体"));//创建字体 
		nOldFont = dc.SelectObject(&nFont);
		strText = GetItemText(lpDrawItemStruct->itemID, _nCol);  
		GetSubItemRect(lpDrawItemStruct->itemID, _nCol, LVIR_LABEL, rcItem);  
		rcItem.left += 5;  
		dc.DrawText(strText,strText.GetLength(),&rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		dc.SelectStockObject(SYSTEM_FONT);
	}  

	// Reset the background color and the text color back to their  
	// original values.  
	dc.SetTextColor(crOldTextColor);  
	dc.SetBkColor(crOldBkColor);  

	dc.Detach();  
}

void CMyListCtrl::ShowEdit(bool bShow, int nItem, int nSubItem, CRect rcCtrl)
{
 	CRect rectClient;
 	GetClientRect(&rectClient);
	//编辑框显示的区域
	if(m_edit.m_hWnd == NULL)
	{	
		m_edit.Create(WS_CHILD | WS_BORDER | ES_CENTER , CRect(0, 0, 0, 0), this, ID_MY_CONTROL_EDIT);
	}
	m_edit.MoveWindow(rcCtrl.left, rcCtrl.top, rcCtrl.Width(), rcCtrl.Height());
	m_edit.ShowWindow(SW_SHOW);

	CString str;
	str = this->GetItemText(nItem, nSubItem);
	m_edit.SetWindowText(str);
	m_edit.SetSel(0,-1);
	m_edit.SetFocus();
	
}

void CMyListCtrl::ShowComboBox(bool bShow, int nItem, int nSubItem, CRect rcCtrl)
{
	if (!bShow)
	{
		if(m_combobox.m_hWnd != NULL)
		{
			m_combobox.ShowWindow(SW_HIDE);
			m_combobox.MoveWindow(0,0,0,0);
		}
		return;
	}
	CRect rectClient;
	GetClientRect(&rectClient);

	if(m_combobox.m_hWnd == NULL)
	{	
		m_combobox.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWN|CBS_DROPDOWNLIST, CRect(0, 0, 0, 0), this, ID_MY_CONTROL_COMBOBOX);
		if(m_combobox.m_hWnd == NULL)
		{
			return;
		}
	}
	
	CListCtrlUnit _Unit;
	_Unit = m_Data.GetData(m_nItemClick, m_nSubItemClick);

	//获取列表数据项
	m_combobox.ResetContent();

	for (int i=0; i<_Unit.arrItems.GetSize(); ++i)
	{
		m_combobox.AddString(_Unit.arrItems.GetAt(i));
	}

	CString str;
	str = this->GetItemText(nItem, nSubItem);
	m_combobox.SetWindowText(str);

	int nItemIndex = _Unit.GetItemIndex(_Unit.arrItems, str);
	m_combobox.SetCurSel(nItemIndex);
	
	m_combobox.MoveWindow(rcCtrl.left, rcCtrl.top, rcCtrl.Width(), 150); //下拉列表的高度
	m_combobox.ShowWindow(SW_SHOW);

	//m_combobox.SetFocus();

}

void CMyListCtrl::ShowSpinButton(bool bShow, int nItem, int nSubItem, CRect rcCtrl)
{
	CRect rectClient;
	GetClientRect(&rectClient);
	
}

LRESULT CMyListCtrl::OnEditEnd(WPARAM wParam, LPARAM lParam)
{
	//窗口是否可见  
	if (!m_edit.IsWindowVisible())
	{
		return (LRESULT)(0);
	}

	if(m_edit.m_hWnd != NULL)
	{
		CString strMsg;
		CString str;
		int		iCurrentValue = 0;
		m_edit.GetWindowText(str);
		
		bool bKey = false;

		//过滤掉关键词
		bKey = (-1 == str.Find(L","));
				
		if (bKey)
		{
			//回填新的数据
			CListCtrl::SetItemText(m_nItemDblClick, m_nSubItemDblClick, str);
		}

		m_edit.ShowWindow(SW_HIDE);
		m_edit.MoveWindow(0,0,0,0);

		//Invalidate();
	}

	return (LRESULT)(0);
}

LRESULT CMyListCtrl::OnComboBoxEnd(WPARAM wParam, LPARAM lParam)
{
	if(m_combobox.m_hWnd != NULL)
	{
		if(wParam == 1)
		{
			CString str;
			m_combobox.GetWindowText(str);
			CListCtrl::SetItemText(m_nItemClick, m_nSubItemClick, str);
			
			HWND hWndParent = NULL;
			if (NULL != GetParent())
			{
				hWndParent = GetParent()->GetSafeHwnd();
			}
			int nCurSel = m_combobox.GetCurSel();
			//发送当前下拉选项值
			::PostMessage(hWndParent, WM_COMBOBOXSELECT,m_nSubItemClick,nCurSel);
		}
		m_combobox.ShowWindow(SW_HIDE);
		m_combobox.MoveWindow(0,0,0,0);
		//Invalidate();
	}

	return (LRESULT)(0);
}

LRESULT CMyListCtrl::OnSpinButtonCtrlEnd(WPARAM wParam, LPARAM lParam)
{
	if(m_spinbutton.m_hWnd != NULL)
	{
		m_spinbutton.ShowWindow(SW_HIDE);
		m_spinbutton.MoveWindow(0,0,0,0);
		//Invalidate();
	}

	return (LRESULT)(0);
}

void CMyListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//if(!m_rectSubItem.PtInRect(point))
	//{
	//	if(m_spinbutton.m_hWnd != NULL)
	//	{ //鼠标移出SUBITEM区域，CSpinButtonCtrl隐藏
	//		if(m_spinbutton.IsWindowVisible())
	//		{
	//			OnSpinButtonCtrlEnd(0,0);
	//		}
	//	}
	//}
	CListCtrl::OnMouseMove(nFlags, point);
}


void CMyListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//获取当前点击区域所在的LISTCTRL行号和列号
	int nResult;
	CRect rect;
	CString str;
	LVHITTESTINFO lvtestinfo;

	lvtestinfo.pt = point;
	nResult = CListCtrl::SubItemHitTest(&lvtestinfo);
	if(nResult == -1)
	{
		m_nItemDblClick = -1;
		m_nSubItemDblClick = -1;
		return;
	}
	else
	{
		m_nItemDblClick = lvtestinfo.iItem;
		m_nSubItemDblClick = lvtestinfo.iSubItem;
	}
	//SUBITEM的文本内容
	m_strSubItem =  GetItemText(m_nItemDblClick, m_nSubItemDblClick);

	//获取SUBITEM的RECT 
	CListCtrl::GetSubItemRect(m_nItemDblClick, m_nSubItemDblClick, LVIR_LABEL, m_rectSubItem);


	//动态显示控件
	if (m_Data.IsCanModify() && m_Data.UnitIsEdit(m_nItemDblClick, m_nSubItemDblClick))
	{
		ShowEdit(true, m_nItemDblClick, m_nSubItemDblClick, m_rectSubItem);
	}

	CListCtrl::OnLButtonDblClk(nFlags, point);
}

void CMyListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//获取当前点击区域所在的LISTCTRL行号和列号
	int nResult;
	CRect rect;
	CString str;
	LVHITTESTINFO lvtestinfo;

	lvtestinfo.pt = point;
	nResult = CListCtrl::SubItemHitTest(&lvtestinfo);
	if(nResult == -1)
	{
		m_nItemClick = -1;
		m_nSubItemClick = -1;
		return;
	}
	else
	{
		m_nItemClick = lvtestinfo.iItem;
		m_nSubItemClick = lvtestinfo.iSubItem;
	}
	//SUBITEM的文本内容
	m_strSubItem =  GetItemText(m_nItemClick, m_nSubItemClick);

	//获取SUBITEM的RECT 
	CListCtrl::GetSubItemRect(m_nItemClick, m_nSubItemClick, LVIR_LABEL, m_rectSubItem);

	bool bShow = (m_Data.IsCanModify() && m_Data.UnitIsCombo(m_nItemClick, m_nSubItemClick));

	ShowComboBox(bShow, m_nItemClick, m_nSubItemClick, m_rectSubItem);

	
	CListCtrl::OnLButtonDown(nFlags, point);
}

void CMyListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	LVHITTESTINFO lvtestinfo;
	int	nItem = -1;
	int	nSubItem = -1;
	lvtestinfo.pt = point;
	int nResult = CListCtrl::SubItemHitTest(&lvtestinfo);
	if(nResult == -1)
	{
		nItem = -1;
		nSubItem = -1;
		return;
	}
	else
	{
		m_nItemClick = lvtestinfo.iItem;
		m_nSubItemClick = lvtestinfo.iSubItem;
	}
	
	CListCtrl::OnLButtonDown(nFlags, point);
}


//用于相应CSpinButtonCtrl的UP/DOWN滚动操作
void CMyListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(nSBCode == SB_ENDSCROLL)
	{ //
		OnSpinButtonCtrlEnd(0, 0);
	}
	if(m_spinbutton.m_hWnd != NULL)
	{
		CString str;
		str.Format(_T("%d"), nPos);
		str = m_strSubItem.Left(m_strSubItem.GetLength() - 2) + str;
	}
	if(m_combobox.m_hWnd != NULL)
	{
		m_combobox.ShowWindow(SW_HIDE);
		m_combobox.MoveWindow(0,0,0,0);
	}
	if(m_edit.m_hWnd != NULL)
	{
		m_edit.ShowWindow(SW_HIDE);
		m_edit.MoveWindow(0,0,0,0);
	}

	Invalidate();
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

int CMyListCtrl::RemoveCtrlAllText()
{
	CStringArray _arrContents;
	_arrContents.RemoveAll();
	_arrContents.SetSize(GetGridNum());

	SetItemTextArray(_arrContents);

	return 0;
}
void CMyListCtrl::SetHeaderFgColor(COLORREF _clrFg)
{
	m_Header.m_color = _clrFg;
}
void CMyListCtrl::SetHeaderBkColor(int R, int G, int B, int Gradient) //设置表头背景色
{
	m_Header.m_R = R;
	m_Header.m_G = G;
	m_Header.m_B = B;
	m_Header.m_Gradient = Gradient;
}

void CMyListCtrl::SetHeaderHeight(UINT _Height)
{
	m_Header.m_Height = _Height;
}


void CMyListCtrl::SetHeaderFontH(int _Height)
{
	m_Header.m_fontHeight = _Height;
}
void CMyListCtrl::SetHeaderFontW(int _Width)
{
	m_Header.m_fontWith = _Width;
}
void CMyListCtrl::SetHeaderFontName(CString _Name)
{
	m_Header.m_fontName = _Name;
}

int CMyListCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat /* = LVCFMT_LEFT */, int nWidth /* = -1 */, int nSubItem /* = -1 */)
{
	m_Header.m_HChar.Add(lpszColumnHeading);
	
	return CListCtrl::InsertColumn(nCol,lpszColumnHeading,nFormat,nWidth,nSubItem);
}
int CMyListCtrl::SetColTextArrayAddr()
{
	int _Col = 0;
	CStringArray _arrContents;
	_arrContents.SetSize(GetRowNum());
	CString strString;
	for (int i=0; i<_arrContents.GetSize(); ++i)
	{
		strString.Format(L"%d", i);
		_arrContents.SetAt(i, strString);
	}
	int _Begin = 0;
	SetColTextArray(_Col, _arrContents, _Begin);

	return 0;
}
void CMyListCtrl::GetItemTextArray(CStringArray& _arrContents)
{
	int nItemNum = GetItemCount();
	int nHeadNum = GetHeaderCtrl()->GetItemCount();

	_arrContents.RemoveAll();
	_arrContents.SetSize(nItemNum*nHeadNum);

	CString str;
	for (int i=0; i<nItemNum; i++)
	{
		for (int j=0; j<nHeadNum; j++)
		{
			str = GetItemText(i, j);
			_arrContents.SetAt(i*nHeadNum+j, str);
		}
	}
}

void CMyListCtrl::GetRowTextArray(int _Row, CStringArray& _arrContents, int _Begin)
{
	int nItemNum = GetItemCount();
	int nHeadNum = GetHeaderCtrl()->GetItemCount();

	if ((_Row >= nItemNum) || (_Row < 0))
	{
		return;
	}

	if ((_Begin >= nHeadNum) || (_Begin < 0))
	{
		return;
	}

	_arrContents.RemoveAll();
	_arrContents.SetSize(nHeadNum);

	CString str;
	int i = _Row;
	for (int j=_Begin; j<nHeadNum; j++)
	{
		str = GetItemText(i, j);
		_arrContents.SetAt(j, str);
	}
}
void CMyListCtrl::GetColTextArray(int _Col, CStringArray& _arrContents, int _Begin)
{
	int nItemNum = GetItemCount();
	int nHeadNum = GetHeaderCtrl()->GetItemCount();

	if ((_Col >= nHeadNum) || (_Col < 0))
	{
		return;
	}
	if ((_Begin >= nItemNum) || (_Begin < 0))
	{
		return;
	}


	_arrContents.RemoveAll();
	_arrContents.SetSize(nItemNum);

	CString str;
	int j = _Col;
	for (int i=_Begin; i<nItemNum; i++)
	{
		str = GetItemText(i, j);
		_arrContents.SetAt(i, str);
	}
}

void CMyListCtrl::SetItemTextArray(CStringArray& _arrContents)
{
	int nItemNum = GetItemCount();
	int nHeadNum = GetHeaderCtrl()->GetItemCount();

	CString str;
	for (int i=0; i<nItemNum; i++)
	{
		for (int j=0; j<nHeadNum; j++)
		{
			int nIndex = i*nHeadNum+j;
			if ( (nIndex >=0) && (nIndex < _arrContents.GetSize()))
			{
				str = _arrContents.GetAt(nIndex);
				SetItemText(i, j, str);
			}
		}
	}
}

void CMyListCtrl::SetRowTextArray(int _Row, CStringArray& _arrContents, int _Begin)
{
	int nItemNum = GetItemCount();
	int nHeadNum = GetHeaderCtrl()->GetItemCount();

	if ((_Row >= nItemNum) || (_Row < 0))
	{
		return;
	}

	if ((_Begin >= nHeadNum) || (_Begin < 0))
	{
		return;
	}

	//_arrContents.RemoveAll();
	//_arrContents.SetSize(nHeadNum);

	CString str;
	int i = _Row;
	for (int j=_Begin; j<nHeadNum; j++)
	{
		if (j < _arrContents.GetSize())
		{
			str = _arrContents.GetAt(j);
			SetItemText(i, j, str);
		}
	}
}
void CMyListCtrl::SetColTextArray(int _Col, CStringArray& _arrContents, int _Begin)
{
	int nItemNum = GetItemCount();
	int nHeadNum = GetHeaderCtrl()->GetItemCount();

	if ((_Col >= nHeadNum) || (_Col < 0))
	{
		return;
	}
	if ((_Begin >= nItemNum) || (_Begin < 0))
	{
		return;
	}

	//_arrContents.RemoveAll();
	//_arrContents.SetSize(nItemNum);

	CString str;
	int j = _Col;
	for (int i=_Begin; i<nItemNum; i++)
	{
		if (i<_arrContents.GetSize())
		{
			str = _arrContents.GetAt(i);
			SetItemText(i, j, str);
		}
	}
}


//样例
void CMyListCtrl::SetUiStyle()
{
	GetCtrlData()->SetDataBkColor(RGB(0x11,0x22,0x33));
	GetCtrlData()->SetDataFgColor(RGB(0x55,0xdd,0x11));
}
void CMyListCtrl::SetUiStyle_DoubleRow()
{
	for (int i=0; i<GetRowNum()/2;++i)
	{
		GetCtrlData()->SetDataBkColorRow(i*2,	RGB(0x10,0x10,0x10));
		GetCtrlData()->SetDataFgColorRow(i*2,	RGB(0xee,0x33,0xee));

		GetCtrlData()->SetDataBkColorRow(i*2+1,	RGB(0x10,0x10,0x10));
		GetCtrlData()->SetDataFgColorRow(i*2+1,	RGB(0xee,0xee,0xee));
	}
}
void CMyListCtrl::SetUiStyle_DoubleCol()
{
	for (int i=0; i<GetColNum()/2;++i)
	{
		GetCtrlData()->SetDataBkColorCol(i*2+1,RGB(0,0,0));
		GetCtrlData()->SetDataFgColorCol(i*2+1,RGB(255,0,255));

		GetCtrlData()->SetDataBkColorCol(i*2,RGB(64,64,64));
		GetCtrlData()->SetDataFgColorCol(i*2,RGB(255,255,255));
	}
}

void CMyListCtrl::SetUiStyle_ModifiedRow()
{
	for (int i=0; i<GetRowNum()/2;++i)
	{
		GetCtrlData()->SetDataModifiedRow(i*2,1);
	}
}

void CMyListCtrl::SetUiStyle_CurrentRow()
{
	GetCtrlData()->SetRowCurrent(5);
}
void CMyListCtrl::DynamicCreate(CWnd* pParent)
{
	CMyListCtrl	m_ListCtrl;
	CStringArray m_arrHeader;
	CStringArray m_arrMCType;
	CStringArray m_arrGlueSwitch;
	CStringArray m_arrSignMode;
	CSliderCtrl m_SliderVel;

	m_arrHeader.RemoveAll();
	m_arrHeader.Add(_T("地址"));
	m_arrHeader.Add(_T("类型"));
	m_arrHeader.Add(_T("X(mm)"));
	m_arrHeader.Add(_T("Y(mm)"));
	m_arrHeader.Add(_T("Z(mm)"));
	m_arrHeader.Add(_T("R(deg)"));
	m_arrHeader.Add(_T("速度(mm/s)"));
	m_arrHeader.Add(_T("点胶开关"));
	m_arrHeader.Add(_T("输入输出"));
	m_arrHeader.Add(_T("信号模式"));
	m_arrHeader.Add(_T("点涂时间"));
	m_arrHeader.Add(_T("安全高度"));
	m_arrHeader.Add(_T("开始延时"));
	m_arrHeader.Add(_T("结束延时"));

	m_arrMCType.RemoveAll();
	m_arrMCType.Add(_T("无"));
	m_arrMCType.Add(_T("线段开始点"));
	m_arrMCType.Add(_T("线段经过点"));
	m_arrMCType.Add(_T("线段结束点"));
	m_arrMCType.Add(_T("圆弧中间点"));
	m_arrMCType.Add(_T("延时"));

	m_arrGlueSwitch.RemoveAll();
	m_arrGlueSwitch.Add(_T("开胶"));
	m_arrGlueSwitch.Add(_T("关胶"));

	m_arrSignMode.RemoveAll();
	m_arrSignMode.Add(_T("导电胶"));
	m_arrSignMode.Add(_T("AB胶"));


	CRect rcWnd;
	//GetClientRect(&rcWnd);
	rcWnd.top = 50;
	rcWnd.left = 30;
	rcWnd.right = 1000;
	rcWnd.bottom = 800;

	//动态创建列表
	if (NULL == m_ListCtrl.GetSafeHwnd())
	{
		m_ListCtrl.Create( WS_CHILD |WS_BORDER| LVS_REPORT | LVS_SHOWSELALWAYS | LBS_NOTIFY | LVS_OWNERDRAWFIXED, rcWnd, pParent, 0x1010 );
	}
	m_ListCtrl.SetExtendedStyle(LVS_EX_FLATSB  | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );		

	//列表头不可拉伸
	m_ListCtrl.GetHeaderCtrl()->EnableWindow(FALSE);

	//插入数据列
	for (int i=0; i<12; ++i)		//m_arrHeader.GetSize()
	{
		m_ListCtrl.InsertColumn(i,m_arrHeader.GetAt(i),LVCFMT_LEFT, 70);
	}
	m_ListCtrl.SetColumnWidth(1,120);

	//插入数据行
	for(int i=0; i<10; i++)
	{
		CString strText;
		strText.Format(_T("%d"), i);
		m_ListCtrl.InsertItem(i, strText);
	}

	//MCPoint mcPoint;
	//设置数据行
	for(int i=0; i<20; i++)
	{
		int nColume = 0;
		CString strText;
		strText.Format(_T("%d"), i);
		m_ListCtrl.SetItemText(i, 0, strText);

	}

	//-=样例=-
	//设置行数和列数
	m_ListCtrl.SetRowColTotal(100, 14);
	//设置某列为下拉列表
	m_ListCtrl.SetDataComboCol(1, m_arrMCType);
	m_ListCtrl.SetDataComboCol(7, m_arrGlueSwitch);
	m_ListCtrl.SetDataComboCol(9, m_arrSignMode);
	//设置某列为编辑框
	m_ListCtrl.SetDataEditCol(2);
	m_ListCtrl.SetDataEditCol(3);
	m_ListCtrl.SetDataEditCol(4);
	m_ListCtrl.SetDataEditCol(5);
	m_ListCtrl.SetDataEditCol(6);
	m_ListCtrl.SetDataEditCol(8);
	m_ListCtrl.SetDataEditCol(10);
	m_ListCtrl.SetDataEditCol(11);
	m_ListCtrl.SetDataEditCol(12);
	m_ListCtrl.SetDataEditCol(13);
	//设置第M行第N列为下拉列表
	m_ListCtrl.SetDataCombo(1,7,m_arrGlueSwitch);
	m_ListCtrl.SetDataCombo(1,9,m_arrSignMode);
	//设置第M行第N列为编辑框
	m_ListCtrl.SetDataEdit(1,5);
	m_ListCtrl.SetDataEdit(1,6);
	//设置数据单元格是否编辑
	m_ListCtrl.m_Data.SetDataCanModify(1);

	//背景色前景色设置:全部|单行|单列|X行Y列
	m_ListCtrl.SetHeaderBkColor(150,200,250,2);				//设置头部背景色
	m_ListCtrl.SetHeaderFgColor(RGB(0x66,0x00,0x99));		//设置头部背景色
	m_ListCtrl.GetCtrlData()->SetDataBkColor(RGB(0,0,255));
	m_ListCtrl.GetCtrlData()->SetDataFgColor(RGB(128,192,0));
	m_ListCtrl.GetCtrlData()->SetDataBkColor(0,0,RGB(0,255,0));
	m_ListCtrl.GetCtrlData()->SetDataFgColor(0,0,RGB(255,0,0));

	//列表头字体
	m_ListCtrl.SetHeaderHeight(42);
	m_ListCtrl.SetHeaderFontH(16);
	m_ListCtrl.SetHeaderFontW(0);
	m_ListCtrl.SetHeaderFontName(L"黑体");

	//列表行字体
	m_ListCtrl.SetRowHeigt(48);
	m_ListCtrl.SetRowFontH(16);
	m_ListCtrl.SetRowFontW(10);
	m_ListCtrl.SetHeaderHeight(36);

	//单双列显示
	for (int i=0; i<m_ListCtrl.GetColNum()/2;++i)
	{
		m_ListCtrl.GetCtrlData()->SetDataBkColorCol(i*2,RGB(0,0,0));
		m_ListCtrl.GetCtrlData()->SetDataFgColorCol(i*2,RGB(255,0,255));

		m_ListCtrl.GetCtrlData()->SetDataBkColorCol(i*2+1,RGB(64,64,64));
		m_ListCtrl.GetCtrlData()->SetDataFgColorCol(i*2+1,RGB(255,255,255));
	}

	//单双行显示
	for (int i=0; i<m_ListCtrl.GetRowNum()/2;++i)
	{
		m_ListCtrl.GetCtrlData()->SetDataBkColorRow(i*2,RGB( 32, 32, 32));
		m_ListCtrl.GetCtrlData()->SetDataFgColorRow(i*2,RGB(0xff,0xee,0xdd));

		m_ListCtrl.GetCtrlData()->SetDataBkColorRow(i*2+1,RGB( 22, 12, 02));
		m_ListCtrl.GetCtrlData()->SetDataFgColorRow(i*2+1,RGB(0xff,0xcc,0xaa));
	}

	m_ListCtrl.ShowWindow(SW_SHOW);

}