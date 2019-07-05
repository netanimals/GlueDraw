#if !defined(AFX_MYLISTCTRL_H__C3BDAC4C_C89F_43B7_8A1B_7B58243FE804__INCLUDED_)
#define AFX_MYLISTCTRL_H__C3BDAC4C_C89F_43B7_8A1B_7B58243FE804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//
#include "MyEdit.h"
#include "MyComboBox.h"
#include "MyHeaderCtrl.h"
#include "MyListCtrlDef.h"

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window
#define WM_COMBOBOXSELECT			WM_USER+103

class CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();
	virtual ~CMyListCtrl();

// Attributes
public:
	CMyHeaderCtrl m_Header;			//列表头
	CMyEdit		m_edit;				//编辑框
	CMyComboBox	m_combobox;			//列表框
	CSpinButtonCtrl m_spinbutton;	//上下调节按钮
// Operations
public:
	CRect		m_rectSubItem;
	CString		m_strSubItem;
		
	int			m_nItemClick;		//保存行号
	int			m_nSubItemClick;	//保存列号
	int			m_nItemDblClick;	//保存行号
	int			m_nSubItemDblClick;	//保存列号
	int			m_nRowHeight;		//行高
	CListCtrlData	m_Data;			//属性数据

	COLORREF	m_clrRowCurrent[2];	//当前行背景颜色 前景颜色
	COLORREF	m_clrRowModified[2];//修改行背景颜色 前景颜色
	
	int			m_fontHeight;		// 字体高度
	int			m_fontWith;			// 字体宽度
	CString		m_fontName;			// 字体名称

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat=LVCFMT_CENTER, int nWidth=-1, int nSubItem= -1);

	void SetRowHeigt(int nHeight);
	void Construct();
	void ShowSpinButton(bool bShow, int nItem, int nSubItem, CRect rcCtrl);
	void ShowComboBox(bool bShow, int nItem, int nSubItem, CRect rcCtrl);
	void ShowEdit(bool bShow, int nItem, int nSubItem, CRect rcCtrl);

	void RefreshRowColTotal(){m_Data.SetRowColTotal(GetRowNum(), GetColNum());};
	void SetRowColTotal(int _RowTotal, int _ColTotal){m_Data.SetRowColTotal(_RowTotal, _ColTotal);};
	void SetDataEdit(int _Row, int _Col){m_Data.SetDataEdit(_Row, _Col);};
	void SetDataCombo(int _Row, int _Col, CStringArray& _Items){m_Data.SetDataCombo(_Row, _Col, _Items);};
	void SetDataEditCol(int _Col){m_Data.SetDataEditCol(_Col);};
	void SetDataComboCol(int _Col, CStringArray& _Items){m_Data.SetDataComboCol(_Col, _Items);};
	bool UnitIsEdit(int _Row, int _Col) {return m_Data.UnitIsEdit(_Row, _Col);};
	bool UnitIsCombo(int _Row, int _Col){return m_Data.UnitIsCombo(_Row, _Col);};
	CListCtrlUnit GetData(int _Row, int _Col){return m_Data.GetData(_Row, _Col);};
	CListCtrlData* GetCtrlData(){return (&m_Data);};
	void GetItemTextArray(CStringArray& _arrContents);
	void SetItemTextArray(CStringArray& _arrContents);
	void GetRowTextArray(int _Row, CStringArray& _arrContents, int _Begin = 0);
	void GetColTextArray(int _Col, CStringArray& _arrContents, int _Begin = 0);
	void SetRowTextArray(int _Row, CStringArray& _arrContents, int _Begin = 0);
	void SetColTextArray(int _Col, CStringArray& _arrContents, int _Begin = 0);

	int GetRowNum(){return GetItemCount();};
	int GetColNum(){return GetHeaderCtrl()->GetItemCount();};
	int GetGridNum(){return (GetRowNum()*GetColNum());};
	int RemoveCtrlAllText();
	int SetColTextArrayAddr();

	void SetRowFontH(int _fontHeight){m_fontHeight=_fontHeight;};
	void SetRowFontW(int _fontWith){m_fontWith=_fontWith;};

	//header
	void SetHeaderFgColor(COLORREF _clrFg);
	void SetHeaderBkColor(int R, int G, int B, int Gradient=0);
	void SetHeaderHeight(UINT _Height);
	void SetHeaderFontH(int _Height);
	void SetHeaderFontW(int _Width);
	void SetHeaderFontName(CString _Name);

	//e.g
	void SetUiStyle();
	void SetUiStyle_DoubleRow();
	void SetUiStyle_DoubleCol();
	void SetUiStyle_ModifiedRow();
	void SetUiStyle_CurrentRow();
private:
	void DynamicCreate(CWnd* pParent);
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual void PreSubclassWindow();

	//{{AFX_MSG(CMyListCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnEditEnd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnComboBoxEnd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg LRESULT OnSpinButtonCtrlEnd(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__C3BDAC4C_C89F_43B7_8A1B_7B58243FE804__INCLUDED_)
