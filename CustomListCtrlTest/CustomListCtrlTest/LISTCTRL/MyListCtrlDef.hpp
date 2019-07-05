#pragma once

//////////////////////////////////////////////////////////////////////////CListCtrlUnit::

CListCtrlUnit::CListCtrlUnit()
{
	nRow=-1;nCol=-1;nModified=0;eType=LCDT_NONE;arrItems.RemoveAll();clrBk=RGB(255,255,255);clrFg=RGB(10,20,30);
};
CListCtrlUnit::~CListCtrlUnit()
{
	arrItems.RemoveAll();
};
CListCtrlUnit::CListCtrlUnit(const CListCtrlUnit& other)
{
	if (&other == this)
	{
		return ;
	} 
	nRow = other.nRow; 
	nCol = other.nCol;
	nModified = other.nModified;
	eType = other.eType;
	clrBk = other.clrBk; 
	clrFg = other.clrFg;
	arrItems.Copy(other.arrItems);
};	
CListCtrlUnit& CListCtrlUnit::operator=(const CListCtrlUnit& other)
{
	if (&other == this)
	{
		return *this;
	} 

	nRow = other.nRow; 
	nCol = other.nCol;
	nModified = other.nModified;
	eType = other.eType;
	clrBk = other.clrBk; 
	clrFg = other.clrFg;
	arrItems.Copy(other.arrItems);

	return *this;
};

void CListCtrlUnit::SetData(int _Row, int _Col, ListCtrl_DataType _Type, CStringArray& _Items)
{
	nRow = _Row; 
	nCol = _Col;
	eType = _Type;
	arrItems.Copy(_Items);
}
void CListCtrlUnit::SetDataModified(int _Row, int _Col, int _Modified/*=1*/)
{
	nRow = _Row; 
	nCol = _Col;
	nModified = _Modified;
}
void CListCtrlUnit::SetDataEdit(int _Row, int _Col)
{
	nRow = _Row; 
	nCol = _Col;
	eType = LCDT_EDIT;
}
void CListCtrlUnit::SetDataCombo(int _Row, int _Col, CStringArray& _Items)
{
	nRow = _Row; 
	nCol = _Col;
	eType = LCDT_COMBO;
	arrItems.Copy(_Items);
}
	
int CListCtrlUnit::GetItemIndex(CStringArray& _Items, CString& str)
{
	int nIndex = 0;
	for (int i=0; i<_Items.GetSize(); ++i)
	{
		if (str == _Items.GetAt(i))
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}

void CListCtrlUnit::SetDataBk(int _Row, int _Col, COLORREF _clrBk)
{
	nRow	= _Row; 
	nCol	= _Col;
	clrBk	= _clrBk;
}

void CListCtrlUnit::SetDataFg(int _Row, int _Col, COLORREF _clrFg)
{
	nRow	= _Row; 
	nCol	= _Col;
	clrFg	= _clrFg;
}

//////////////////////////////////////////////////////////////////////////CListCtrlData::

CListCtrlData::CListCtrlData()
{
	nRowTotal	= 0;
	nColTotal	= 0;
	nRowCurrent	= -1;
	bRowCurrentModify = false;
	nCanModify  = 0;
	nCanColor	= 0;
	arrDatas.RemoveAll();
};
CListCtrlData::~CListCtrlData()
{
	arrDatas.RemoveAll();
};
CListCtrlData::CListCtrlData(int _RowTotal, int _ColTotal)
{
	SetRowColTotal(_RowTotal, _ColTotal);
};
CListCtrlData::CListCtrlData(const CListCtrlData& other)
{  
	if (&other == this)
	{
		return ;
	} 

	nRowTotal = other.nRowTotal;
	nColTotal = other.nColTotal;
	nCanModify  = other.nCanModify;
	arrDatas.Copy(other.arrDatas);
};	
CListCtrlData& CListCtrlData::operator=(const CListCtrlData& other)
{
	if (&other == this)
	{
		return *this;
	} 
		
	nRowTotal = other.nRowTotal;
	nColTotal = other.nColTotal;

	nCanModify  = other.nCanModify;
	arrDatas.Copy(other.arrDatas);

	return *this;
};
bool CListCtrlData::ListCtrlHasData()
{
	return static_cast<bool>(nRowTotal*nColTotal>0);
}
bool CListCtrlData::GetRowCurrentMofify()
{
	return bRowCurrentModify;
}
void CListCtrlData::SetRowCurrentMofify(bool _bModify/*=true*/)
{
	bRowCurrentModify = _bModify;
}
void CListCtrlData::SetRowCurrent(int _nRowCurrent)
{
	if (nRowCurrent != _nRowCurrent)
	{
		nRowCurrent = _nRowCurrent;
		SetRowCurrentMofify(true);
	}
		
	return ;
}
int CListCtrlData::GetRowCurrent()
{
	return nRowCurrent;
}
void CListCtrlData::SetDataCanModify(int _CanModify)
{
	nCanModify = _CanModify;
}
bool CListCtrlData::IsCanModify()
{ 
	return static_cast<bool>(nCanModify != 0);
}

void CListCtrlData::SetRowColTotal(int _RowTotal, int _ColTotal)
{
	int nUnitTotal	= _RowTotal * _ColTotal;
	nRowTotal	= _RowTotal;
	nColTotal	= _ColTotal;
	arrDatas.RemoveAll();
	arrDatas.SetSize(nUnitTotal);
}

void CListCtrlData::SetData(int _Row, int _Col, ListCtrl_DataType _Type, CStringArray& _Items,COLORREF _clrBk/*=RGB(255,255,255)*/,COLORREF _clrFg/*=RGB(0,0,0)*/)
{
	if ((_Row>=nRowTotal) || _Col>=nColTotal)
	{
		return;
	}
	int _UnitTotal = _Row * nColTotal + _Col;
	if (_UnitTotal>=arrDatas.GetSize() || (_UnitTotal<0))
	{
		return;
	}

	CListCtrlUnit _Unit;

	_Unit.nRow = _Row;
	_Unit.nCol = _Col;
	_Unit.eType = _Type;
	_Unit.arrItems.Copy(_Items);
	_Unit.clrBk=_clrBk;
	_Unit.clrFg=_clrFg;

	arrDatas.GetAt(_UnitTotal) = _Unit;
}

void CListCtrlData::SetData(CListCtrlUnit& _Unit)
{
	SetData(_Unit.nRow, _Unit.nCol, _Unit.eType, _Unit.arrItems, _Unit.clrBk, _Unit.clrFg);
}

void CListCtrlData::SetDataModified(int _Row, int _Col, int _Modified/*=1*/)
{
	int _UnitIndex = GetUnitIndex(_Row, _Col);

	arrDatas.GetAt(_UnitIndex).SetDataModified(_Row, _Col, _Modified);
}

void CListCtrlData::SetDataEdit(int _Row, int _Col)
{
	CListCtrlUnit _Unit;
	_Unit.SetDataEdit(_Row, _Col);
	SetData(_Unit);

}

void CListCtrlData::SetDataCombo(int _Row, int _Col, CStringArray& _Items)
{
	CListCtrlUnit _Unit;
	_Unit.SetDataCombo(_Row, _Col, _Items);
	SetData(_Unit);
}

void CListCtrlData::SetDataRow(int _Row,ListCtrl_DataType _Type, CStringArray& _Items)
{
	int _Col = 0;
	for (int i=0; i<nColTotal; ++i)
	{
		_Col = i;

		SetData(_Row, _Col, _Type, _Items);
	}
}

void CListCtrlData::SetDataCol(int _Col,ListCtrl_DataType _Type, CStringArray& _Items)
{
	for (int i=0; i<nRowTotal; ++i)
	{
		int _Row = nColTotal * i + _Col;

		SetData(_Row, _Col, _Type, _Items);
	}
}
void CListCtrlData::SetDataModifiedRow(int _Row, int _Modified)
{
	int _Col = 0;
	for (int i=0; i<nColTotal; ++i)
	{
		_Col = i;	//_Col = _Row * nColTotal + i;
		SetDataModified(_Row, _Col, _Modified);
	}
}
void CListCtrlData::SetDataEditRow(int _Row)
{
	int _Col = 0;
	for (int i=0; i<nColTotal; ++i)
	{
		_Col = i;

		CListCtrlUnit _Unit;
		_Unit.nRow = _Row;
		_Unit.nCol = i;
		_Unit.eType = LCDT_EDIT;
		SetData(_Unit);
	}
}
void CListCtrlData::SetDataEditCol(int _Col)
{
	for (int i=0; i<nRowTotal; ++i)
	{
		int _Row = nColTotal * i + _Col;

		CListCtrlUnit _Unit;
		_Unit.nRow = i;
		_Unit.nCol = _Col;
		_Unit.eType = LCDT_EDIT;
		SetData(_Unit);
	}
}

void CListCtrlData::SetDataComboRow(int _Row, CStringArray& _Items)
{
	int _Col = 0;
	for (int i=0; i<nColTotal; ++i)
	{
		_Col = i;

		CListCtrlUnit _Unit;
		_Unit.nRow = i;
		_Unit.nCol = _Col;
		_Unit.eType = LCDT_COMBO;
		_Unit.arrItems.Copy(_Items);

		SetData(_Unit);
	}
}
void CListCtrlData::SetDataComboCol(int _Col, CStringArray& _Items)
{
	for (int i=0; i<nRowTotal; ++i)
	{
		int _Row = nColTotal * i + _Col;

		CListCtrlUnit _Unit;
		_Unit.nRow = i;
		_Unit.nCol = _Col;
		_Unit.eType = LCDT_COMBO;
		_Unit.arrItems.Copy(_Items);

		SetData(_Unit);
	}
}

int CListCtrlData::GetUnitIndex(int _Row, int _Col)
{
	return (_Row * nColTotal + _Col);
}

bool CListCtrlData::UnitIsEdit(int _Row, int _Col)
{ 
	int _UnitIndex = GetUnitIndex(_Row, _Col);

	if (_UnitIndex>=arrDatas.GetSize() || _UnitIndex<0)
	{
		return false;
	}

	CListCtrlUnit _Unit;
	_Unit = arrDatas.GetAt(_UnitIndex);

	return static_cast<bool>(_Unit.UnitIsEdit(_Unit));
}

bool CListCtrlData::UnitIsCombo(int _Row, int _Col)
{ 
	int _UnitIndex = GetUnitIndex(_Row, _Col);

	if (_UnitIndex>=arrDatas.GetSize() || _UnitIndex<0)
	{
		return false;
	}

	CListCtrlUnit _Unit;
	_Unit = arrDatas.GetAt(_UnitIndex);

	return static_cast<bool>(_Unit.UnitIsCombo(_Unit));
}

CListCtrlUnit CListCtrlData::GetData(int _Row, int _Col)
{ 
	int _UnitIndex = GetUnitIndex(_Row, _Col);

	return (arrDatas.GetAt(_UnitIndex));
}

void CListCtrlData::SetDataCanColor(int _CanColor/*=1*/)
{
	nCanColor = _CanColor;
}

void CListCtrlData::SetDataBkColor(int _Row, int _Col, COLORREF _clrBk)
{
	int _UnitIndex = GetUnitIndex(_Row, _Col);

	if (_UnitIndex>=arrDatas.GetSize() || _UnitIndex<0)
	{
		return ;
	}

	SetDataCanColor(1);
	arrDatas.GetAt(_UnitIndex).clrBk = _clrBk;
}

void CListCtrlData::SetDataBkColor(COLORREF _clrBk)
{
	for (int _Row=0; _Row<nRowTotal; ++_Row)
	{
		for (int _Col=0; _Col<nColTotal; ++_Col)
		{
			SetDataBkColor(_Row, _Col, _clrBk);
		}
	}
	
}
void CListCtrlData::SetDataBkColorRow(int _Row, COLORREF _clrBk)
{
	int _Col = 0;
	for (int i=0; i<nColTotal; ++i)
	{
		_Col = i;		//_Row * nColTotal + 

		SetDataBkColor(_Row, _Col, _clrBk);
	}
}
void CListCtrlData::SetDataBkColorCol(int _Col, COLORREF _clrBk)
{
	int _Row = 0;
	for (int i=0; i<nRowTotal; ++i)
	{
		_Row = i;	//nColTotal * i + 

		SetDataBkColor(_Row, _Col, _clrBk);
	}
}
COLORREF CListCtrlData::GetDataBkColor(int _Row, int _Col)
{
	int _UnitIndex = GetUnitIndex(_Row, _Col);

	if (_UnitIndex>=arrDatas.GetSize() || _UnitIndex<0)
	{
		return RGB(255,255,255);
	}

	return (arrDatas.GetAt(_UnitIndex).clrBk);
}


void CListCtrlData::SetDataFgColor(int _Row, int _Col, COLORREF _clrFg)
{
	int _UnitIndex = GetUnitIndex(_Row, _Col);

	if (_UnitIndex>=arrDatas.GetSize() || _UnitIndex<0)
	{
		return ;
	}

	SetDataCanColor(1);
	arrDatas.GetAt(_UnitIndex).clrFg = _clrFg;
}

void CListCtrlData::SetDataFgColor(COLORREF _clrFg)
{
	for (int _Row=0; _Row<nRowTotal; ++_Row)
	{
		for (int _Col=0; _Col<nColTotal; ++_Col)
		{
			SetDataFgColor(_Row, _Col, _clrFg);
		}
	}

}
void CListCtrlData::SetDataFgColorRow(int _Row, COLORREF _clrFg)
{
	int _Col = 0;
	for (int i=0; i<nColTotal; ++i)
	{
		_Col = i;		//_Row * nColTotal + 

		SetDataFgColor(_Row, _Col, _clrFg);
	}
}
void CListCtrlData::SetDataFgColorCol(int _Col, COLORREF _clrFg)
{
	int _Row = 0;
	for (int i=0; i<nRowTotal; ++i)
	{
		_Row = i;	//nColTotal * i + 

		SetDataFgColor(_Row, _Col, _clrFg);
	}
}
COLORREF CListCtrlData::GetDataFgColor(int _Row, int _Col)
{
	int _UnitIndex = GetUnitIndex(_Row, _Col);

	if (_UnitIndex>=arrDatas.GetSize() || _UnitIndex<0)
	{
		return RGB(255,255,255);
	}

	return (arrDatas.GetAt(_UnitIndex).clrFg);
}

