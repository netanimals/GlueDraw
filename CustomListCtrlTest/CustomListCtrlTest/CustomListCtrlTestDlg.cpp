
// CustomListCtrlTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomListCtrlTest.h"
#include "CustomListCtrlTestDlg.h"
#include "DlgMotionControlPointEditDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCustomListCtrlTestDlg 对话框




CCustomListCtrlTestDlg::CCustomListCtrlTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomListCtrlTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomListCtrlTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_SliderVel);
//	DDX_Control(pDX, IDC_LIST_CA, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CCustomListCtrlTestDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CCustomListCtrlTestDlg 消息处理程序

BOOL CCustomListCtrlTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	ShowWindow(SW_MAXIMIZE);
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化
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
	GetClientRect(&rcWnd);
	rcWnd.top += 70;
	rcWnd.left = 100;
	rcWnd.right = 1000;
	rcWnd.bottom = 800;

	if (NULL == m_ListCtrl.GetSafeHwnd())
	{
		m_ListCtrl.Create( WS_CHILD |WS_BORDER| LVS_REPORT | LVS_SHOWSELALWAYS | LBS_NOTIFY | LVS_OWNERDRAWFIXED, rcWnd, this, 1010 );
	}
	m_ListCtrl.SetExtendedStyle(LVS_EX_DOUBLEBUFFER | LVS_EX_FLATSB  | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );		
	
	//列表头不可拉伸
	m_ListCtrl.GetHeaderCtrl()->EnableWindow(FALSE);

	//插入数据列
	for (int i=0; i<10; ++i)		//m_arrHeader.GetSize()
	{
		m_ListCtrl.InsertColumn(i,m_arrHeader.GetAt(i),LVCFMT_LEFT, 90);
	}
	//m_ListCtrl.SetColumnWidth(1,120);

	//插入数据行
	for(int i=0; i<19; i++)
	{
		CString strText;
		strText.Format(_T("%d"), i);
		m_ListCtrl.InsertItem(i, strText);
	}

	MCPoint mcPoint;
	//设置数据行
	for(int i=0; i<20; i++)
	{
		int nColume = 0;
		CString strText;

		mcPoint.Addr = i;
		strText.Format(_T("%d"), i);
		m_ListCtrl.SetItemText(i, 0, strText);

		strText = m_arrMCType.GetAt(1);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText.Format(_T("%.3f"), mcPoint.X);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText.Format(_T("%.3f"), mcPoint.Y);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText.Format(_T("%.3f"), mcPoint.Z);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText.Format(_T("%.3f"), mcPoint.R);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText.Format(_T("%.3f"), mcPoint.Speed);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText = m_arrGlueSwitch.GetAt(0);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText.Format(_T("%d"), mcPoint.DIDO);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText = m_arrSignMode.GetAt(0);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText.Format(_T("%.3f"), mcPoint.GlueTime);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText.Format(_T("%.3f"), mcPoint.SafeHeight);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText.Format(_T("%.3f"), mcPoint.DelayBegin);
		m_ListCtrl.SetItemText(i, ++nColume, strText);

		strText.Format(_T("%.3f"), mcPoint.DelayEnd);
		m_ListCtrl.SetItemText(i, ++nColume, strText);
	}

	//测试数据--
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
	//m_ListCtrl.SetDataCombo(1,7,m_arrGlueSwitch);
	//m_ListCtrl.SetDataCombo(1,9,m_arrSignMode);
	//设置第M行第N列为编辑框
	//m_ListCtrl.SetDataEdit(1,5);
	//m_ListCtrl.SetDataEdit(1,6);
	m_ListCtrl.m_Data.SetDataCanModify(1);
//	m_ListCtrl.SetHeaderBkColor(150,200,250,2);				//设置头部背景色
//	m_ListCtrl.SetHeaderFgColor(RGB(0x66,0x00,0x99));		//设置头部背景色
//	m_ListCtrl.GetCtrlData()->SetDataBkColor(RGB(0x11,0x22,0x33));
//	m_ListCtrl.GetCtrlData()->SetDataFgColor(RGB(0x55,0xdd,0x11));
//	m_ListCtrl.GetCtrlData()->SetDataBkColor(0,0,RGB(0,255,0));
//	m_ListCtrl.GetCtrlData()->SetDataFgColor(0,0,RGB(255,0,0));

//	m_ListCtrl.SetHeaderHeight(42);
//	m_ListCtrl.SetHeaderFontH(16);
//	m_ListCtrl.SetHeaderFontW(0);
//	m_ListCtrl.SetHeaderFontName(L"黑体");
//	m_ListCtrl.SetRowHeigt(48);
//	m_ListCtrl.SetRowFontH(16);
//	m_ListCtrl.SetRowFontW(10);
	//m_ListCtrl.SetHeaderHeight(0.1);
	m_ListCtrl.SetUiStyle();
//	m_ListCtrl.SetUiStyle_DoubleRow();
//	m_ListCtrl.SetUiStyle_DoubleCol();
//	m_ListCtrl.SetUiStyle_ModifiedRow();
	m_ListCtrl.SetUiStyle_CurrentRow();
	/*for (int i=0; i<m_ListCtrl.GetColNum()/2;++i)
	{
		m_ListCtrl.GetCtrlData()->SetDataBkColorCol(i*2,RGB(0,0,0));
		m_ListCtrl.GetCtrlData()->SetDataFgColorCol(i*2,RGB(255,0,255));

		m_ListCtrl.GetCtrlData()->SetDataBkColorCol(i*2+1,RGB(64,64,64));
		m_ListCtrl.GetCtrlData()->SetDataFgColorCol(i*2+1,RGB(255,255,255));
	}*/
	//for (int i=0; i<m_ListCtrl.GetRowNum()/2;++i)
	//{
	//	m_ListCtrl.GetCtrlData()->SetDataBkColorRow(i*2,	RGB(0x10,0x10,0x10));
	//	m_ListCtrl.GetCtrlData()->SetDataFgColorRow(i*2,	RGB(0xee,0x33,0xee));

	//	m_ListCtrl.GetCtrlData()->SetDataBkColorRow(i*2+1,	RGB(0x10,0x10,0x10));
	//	m_ListCtrl.GetCtrlData()->SetDataFgColorRow(i*2+1,	RGB(0xee,0xee,0xee));
	//}

	m_ListCtrl.ShowWindow(SW_SHOW);

	CString _Content = L"1,2";
	CStringArray _Items;
	CString _Spearator = _T(",");

	_Content = L"";
	Format2String(_Content, _Items, _Spearator);
	_Content = L",";
	Format2String(_Content, _Items, _Spearator);
	_Content = L"1";
	Format2String(_Content, _Items, _Spearator);
	_Content = L"1,";
	Format2String(_Content, _Items, _Spearator);
	_Content = L"111";
	Format2String(_Content, _Items, _Spearator);
	_Content = L"11111,";
	Format2String(_Content, _Items, _Spearator);
	_Content = L"11111.1111,";
	Format2String(_Content, _Items, _Spearator);
	_Content = L",,";
	Format2String(_Content, _Items, _Spearator);
	_Content = L"1,2";
	Format2String(_Content, _Items, _Spearator);
	_Content = L"111,222";
	Format2String(_Content, _Items, _Spearator);
	_Content = L"1,2,";
	Format2String(_Content, _Items, _Spearator);
	_Content = L"1111,222.22,";
	Format2String(_Content, _Items, _Spearator);
	_Content = L",,,,";
	Format2String(_Content, _Items, _Spearator);
	Format2String(_Content, _Items, L",,");
	Format2String(_Content, _Items, L",,,");
	Format2String(_Content, _Items, L",,,,");
	_Content = L",,,,";
	Format2String(_Content, _Items, L",,,,,");
	_Content = L"123,,45678,,";
	Format2String(_Content, _Items, L",,");

	SetTimer(1, 1000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CCustomListCtrlTestDlg::TestArray(CStringArray& _Items)
{
	CString strString;
	CString strString1;
	strString.Format(L"Size - %d : ", _Items.GetSize());
	for (int i=0; i<_Items.GetSize(); ++i)
	{
		strString1.Format(L"%d - %s \t", i, _Items.GetAt(i));
		strString += strString1;
	}
	strString += L"\r\n";

	TRACE1("%s", strString.GetBuffer(0));
}
void CCustomListCtrlTestDlg::Format2String(const CString& _Content, CStringArray& _Items, CString _Spearator)
{
	_Items.RemoveAll();

	CString strSearch;
	CString strData= _Content;

	int nSepLen = _Spearator.GetLength();

	if ( (_Content.GetLength() >= nSepLen) && _Content.Right(nSepLen) != _Spearator) 
	{
		strData +=_Spearator;
	}

	int nStart = 0;
	int nEnd = 0;
	int nLen = 0;
	int nCount = 0;
		
	while ( -1 != (nStart=strData.Find(_Spearator, nCount)) )
	{
		if (0 == nCount)
		{
			strSearch = strData.Mid(0, nStart);
			_Items.Add(strSearch);
		}

		nCount = (nStart+nSepLen);
		nEnd = strData.Find(_Spearator, nCount);

		if (-1 != nEnd)
		{
			strSearch = strData.Mid(nCount, nEnd-nCount);
			_Items.Add(strSearch);
		}
		else
		{
			strSearch = strData.Right(nLen - (nCount));
		}
	}

	TestArray(_Items);

}

void CCustomListCtrlTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (1 == nIDEvent)
	{
		if (NULL != m_ListCtrl.GetSafeHwnd())
		{
			int nCur = m_ListCtrl.m_Data.GetRowCurrent();
			nCur++;
			nCur %= 22; 
			m_ListCtrl.m_Data.SetRowCurrent(nCur);
			m_ListCtrl.Invalidate();
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CCustomListCtrlTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCustomListCtrlTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCustomListCtrlTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCustomListCtrlTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int nVelPos = m_SliderVel.GetPos();
	if (GetDlgItem(IDC_SLIDER1) == pScrollBar)
	{
		
		switch(nSBCode)
		{
		case SB_PAGELEFT:
			{
				TRACE0("SB_PAGELEFT\r\n");
				break;
			}
		case SB_PAGERIGHT:
			{
				TRACE0("SB_PAGERIGHT\r\n");
				break;
			}
		case SB_LEFT:
			{
				TRACE0("SB_LEFT\r\n");
				break;
			}
		case SB_RIGHT:
			{
				TRACE0("SB_RIGHT\r\n");
				break;
			}
		case SB_LINELEFT:
			{
				TRACE0("SB_LINELEFT\r\n");
				break;
			}
		case SB_LINERIGHT:
			{
				TRACE0("SB_LINERIGHT\r\n");
				break;
			}
		case SB_THUMBPOSITION:
			{
				TRACE0("SB_THUMBPOSITION\r\n");
				TRACE1("%d \r\n", nPos);
				break;
			}
		case SB_THUMBTRACK:
			{
				//TRACE0("SB_THUMBTRACK\r\n");
				//TRACE1("%d \r\n", nPos);
				break;
			}
		}
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
