#pragma once

//数据输入类型
enum ListCtrl_DataType
{
	LCDT_NONE,
	LCDT_EDIT,
	LCDT_COMBO,
	LCDT_SPIN,
};

//列表单元格数据
class CListCtrlUnit
{
public:
	int nRow;
	int nCol;
	int nModified;
	ListCtrl_DataType eType;
	COLORREF clrBk;
	COLORREF clrFg;
	CStringArray arrItems;
public:
	inline CListCtrlUnit();
	inline virtual ~CListCtrlUnit();
	inline CListCtrlUnit(const CListCtrlUnit& other);	
	inline CListCtrlUnit& operator=(const CListCtrlUnit& other);
public:
	inline bool UnitIsNone(CListCtrlUnit& _Unit){ return static_cast<bool>(_Unit.eType == LCDT_NONE);}
	inline bool UnitIsEdit(CListCtrlUnit& _Unit){ return static_cast<bool>(_Unit.eType == LCDT_EDIT);}
	inline bool UnitIsCombo(CListCtrlUnit& _Unit){ return static_cast<bool>(_Unit.eType == LCDT_COMBO);}
	inline bool UnitIsModified(CListCtrlUnit& _Unit){ return static_cast<bool>(_Unit.nModified != 0);}
	inline bool UnitIsNone(ListCtrl_DataType _Unit){ return static_cast<bool>(_Unit == LCDT_NONE);}
	inline bool UnitIsEdit(ListCtrl_DataType _Unit){ return static_cast<bool>(_Unit == LCDT_EDIT);}
	inline bool UnitIsCombo(ListCtrl_DataType _Unit){ return static_cast<bool>(_Unit == LCDT_COMBO);}
	inline bool UnitIsModified(){ return static_cast<bool>(nModified != 0);}

	inline void SetData(int _Row, int _Col, ListCtrl_DataType _Type, CStringArray& _Items);
	inline void SetDataModified(int _Row, int _Col, int _Modified=1);
	inline void SetDataEdit(int _Row, int _Col);
	inline void SetDataCombo(int _Row, int _Col, CStringArray& _Items);
	inline int  GetItemIndex(CStringArray& _Items, CString& str);
	inline void SetDataBk(int _Row, int _Col, COLORREF _clrBk);
	inline void SetDataFg(int _Row, int _Col, COLORREF _clrFg);
};

typedef CArray<CListCtrlUnit, CListCtrlUnit&> arrListCtrlData;

//列表数据项
class CListCtrlData
{
public:
	int nRowTotal;
	int nColTotal;
	int nRowCurrent;
	bool bRowCurrentModify;
	int nCanModify;
	int nCanColor;
	arrListCtrlData arrDatas;
public:
	inline CListCtrlData();
	inline virtual ~CListCtrlData();
	inline CListCtrlData(int _RowTotal, int _ColTotal);
	inline CListCtrlData(const CListCtrlData& other);	
	inline CListCtrlData& operator=(const CListCtrlData& other);
	inline arrListCtrlData* GetCtrlData(){return (&arrDatas);};
public:
	inline bool ListCtrlHasData();
	inline bool GetRowCurrentMofify();
	inline void SetRowCurrentMofify(bool _bModify=true);
	inline void SetRowCurrent(int _nRowCurrent);
	inline int  GetRowCurrent();
	inline void SetDataCanModify(int _CanModify);
	inline bool IsCanModify();
	inline void SetRowColTotal(int _RowTotal, int _ColTotal);
	inline void SetData(int _Row, int _Col, ListCtrl_DataType _Type, CStringArray& _Items,COLORREF _clrBk=RGB(255,255,255),COLORREF _clrFg=RGB(0,0,0));
	inline void SetData(CListCtrlUnit& _Unit);
	inline void SetDataModified(int _Row, int _Col, int _Modified=1);
	inline void SetDataEdit(int _Row, int _Col);
	inline void SetDataCombo(int _Row, int _Col, CStringArray& _Items);
	inline void SetDataRow(int _Row,ListCtrl_DataType _Type, CStringArray& _Items);
	inline void SetDataCol(int _Col,ListCtrl_DataType _Type, CStringArray& _Items);
	inline void SetDataModifiedRow(int _Row, int _Modified=1);
	inline void SetDataEditRow(int _Row);
	inline void SetDataEditCol(int _Col);
	inline void SetDataComboRow(int _Row, CStringArray& _Items);
	inline void SetDataComboCol(int _Col, CStringArray& _Items);
	inline int  GetUnitIndex(int _Row, int _Col);
	inline bool UnitIsEdit(int _Row, int _Col);
	inline bool UnitIsCombo(int _Row, int _Col);
	inline CListCtrlUnit GetData(int _Row, int _Col);

	inline bool GetDataCanColor(){return (nCanColor!=0);};
	inline void SetDataCanColor(int _CanColor=1);
	inline void SetDataBkColor(COLORREF _clrBk=RGB(255,255,255));
	inline void SetDataBkColor(int _Row, int _Col, COLORREF _clrBk=RGB(255,255,255));
	inline void SetDataBkColorRow(int _Row, COLORREF _clrBk=RGB(255,255,255));
	inline void SetDataBkColorCol(int _Col, COLORREF _clrBk=RGB(255,255,255));
	inline COLORREF GetDataBkColor(int _Row, int _Col);

	inline void SetDataFgColor(COLORREF _clrFg=RGB(0,0,0));
	inline void SetDataFgColor(int _Row, int _Col, COLORREF _clrFg=RGB(0,0,0));
	inline void SetDataFgColorRow(int _Row, COLORREF _clrFg=RGB(0,0,0));
	inline void SetDataFgColorCol(int _Col, COLORREF _clrFg=RGB(0,0,0));
	inline COLORREF GetDataFgColor(int _Row, int _Col);

};

#include "MyListCtrlDef.hpp"