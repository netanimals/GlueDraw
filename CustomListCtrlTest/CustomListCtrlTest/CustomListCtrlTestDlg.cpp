
// CustomListCtrlTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CustomListCtrlTest.h"
#include "CustomListCtrlTestDlg.h"
#include "DlgMotionControlPointEditDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCustomListCtrlTestDlg �Ի���




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


// CCustomListCtrlTestDlg ��Ϣ�������

BOOL CCustomListCtrlTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_arrHeader.RemoveAll();
	m_arrHeader.Add(_T("��ַ"));
	m_arrHeader.Add(_T("����"));
	m_arrHeader.Add(_T("X(mm)"));
	m_arrHeader.Add(_T("Y(mm)"));
	m_arrHeader.Add(_T("Z(mm)"));
	m_arrHeader.Add(_T("R(deg)"));
	m_arrHeader.Add(_T("�ٶ�(mm/s)"));
	m_arrHeader.Add(_T("�㽺����"));
	m_arrHeader.Add(_T("�������"));
	m_arrHeader.Add(_T("�ź�ģʽ"));
	m_arrHeader.Add(_T("��Ϳʱ��"));
	m_arrHeader.Add(_T("��ȫ�߶�"));
	m_arrHeader.Add(_T("��ʼ��ʱ"));
	m_arrHeader.Add(_T("������ʱ"));

	m_arrMCType.RemoveAll();
	m_arrMCType.Add(_T("��"));
	m_arrMCType.Add(_T("�߶ο�ʼ��"));
	m_arrMCType.Add(_T("�߶ξ�����"));
	m_arrMCType.Add(_T("�߶ν�����"));
	m_arrMCType.Add(_T("Բ���м��"));
	m_arrMCType.Add(_T("��ʱ"));

	m_arrGlueSwitch.RemoveAll();
	m_arrGlueSwitch.Add(_T("����"));
	m_arrGlueSwitch.Add(_T("�ؽ�"));

	m_arrSignMode.RemoveAll();
	m_arrSignMode.Add(_T("���罺"));
	m_arrSignMode.Add(_T("AB��"));


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
	
	//�б�ͷ��������
	m_ListCtrl.GetHeaderCtrl()->EnableWindow(FALSE);

	//����������
	for (int i=0; i<10; ++i)		//m_arrHeader.GetSize()
	{
		m_ListCtrl.InsertColumn(i,m_arrHeader.GetAt(i),LVCFMT_LEFT, 90);
	}
	//m_ListCtrl.SetColumnWidth(1,120);

	//����������
	for(int i=0; i<19; i++)
	{
		CString strText;
		strText.Format(_T("%d"), i);
		m_ListCtrl.InsertItem(i, strText);
	}

	MCPoint mcPoint;
	//����������
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

	//��������--
	//��������������
	m_ListCtrl.SetRowColTotal(100, 14);
	//����ĳ��Ϊ�����б�
	m_ListCtrl.SetDataComboCol(1, m_arrMCType);
	m_ListCtrl.SetDataComboCol(7, m_arrGlueSwitch);
	m_ListCtrl.SetDataComboCol(9, m_arrSignMode);
	//����ĳ��Ϊ�༭��
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
	//���õ�M�е�N��Ϊ�����б�
	//m_ListCtrl.SetDataCombo(1,7,m_arrGlueSwitch);
	//m_ListCtrl.SetDataCombo(1,9,m_arrSignMode);
	//���õ�M�е�N��Ϊ�༭��
	//m_ListCtrl.SetDataEdit(1,5);
	//m_ListCtrl.SetDataEdit(1,6);
	m_ListCtrl.m_Data.SetDataCanModify(1);
//	m_ListCtrl.SetHeaderBkColor(150,200,250,2);				//����ͷ������ɫ
//	m_ListCtrl.SetHeaderFgColor(RGB(0x66,0x00,0x99));		//����ͷ������ɫ
//	m_ListCtrl.GetCtrlData()->SetDataBkColor(RGB(0x11,0x22,0x33));
//	m_ListCtrl.GetCtrlData()->SetDataFgColor(RGB(0x55,0xdd,0x11));
//	m_ListCtrl.GetCtrlData()->SetDataBkColor(0,0,RGB(0,255,0));
//	m_ListCtrl.GetCtrlData()->SetDataFgColor(0,0,RGB(255,0,0));

//	m_ListCtrl.SetHeaderHeight(42);
//	m_ListCtrl.SetHeaderFontH(16);
//	m_ListCtrl.SetHeaderFontW(0);
//	m_ListCtrl.SetHeaderFontName(L"����");
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCustomListCtrlTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCustomListCtrlTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCustomListCtrlTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
