// MyHeaderCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "MyHeaderCtrl.h"


// CMyHeaderCtrl

IMPLEMENT_DYNAMIC(CMyHeaderCtrl, CHeaderCtrl)

CMyHeaderCtrl::CMyHeaderCtrl()
{
	//150,200,250,2
	m_R = (150);
	m_G = (200);
	m_B = (250);
	m_Gradient = (5);
	m_Format = L"";
	m_Height = 36;
	m_fontHeight = 15;
	m_fontWith = 0;
	m_fontName = L"黑体";
	m_color = RGB(0x33,0xff,0x99);	//250,50,50
}

CMyHeaderCtrl::~CMyHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyHeaderCtrl, CHeaderCtrl)
	ON_WM_PAINT()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()



// CMyHeaderCtrl 消息处理程序



void CMyHeaderCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CHeaderCtrl::OnPaint()
	int nItem; 
	nItem = GetItemCount();//得到有几个单元 
	for(int i = 0; i<nItem;i++) 
	{ 
		CRect tRect;
		GetItemRect(i,&tRect);	//得到Item的尺寸
		int R = m_R,G = m_G,B = m_B;
		CRect nRect(tRect);		//拷贝尺寸到新的容器中 
		nRect.left+=1;			//留出分割线的地方 

		
		{
			CRect rcSep = tRect;
			rcSep.right = rcSep.left+1;
			if (0==i)
			{
				rcSep.left -= 1;
			}
			CBrush _brush; 
			_brush.CreateSolidBrush(RGB(245,245,245));//创建画刷 
			dc.FillRect(&rcSep,&_brush); //填充背景 
			_brush.DeleteObject(); //释放画刷 
		}
		//绘制立体背景 
		for(int j = tRect.top;j<=tRect.bottom;j++) 
		{ 
			nRect.bottom = nRect.top+1; 
			CBrush _brush; 
			_brush.CreateSolidBrush(RGB(R,G,B));//创建画刷 
			dc.FillRect(&nRect,&_brush); //填充背景 
			_brush.DeleteObject(); //释放画刷 
			R-=m_Gradient;G-=m_Gradient;B-=m_Gradient;
			if (R<0)R = 0;
			if (G<0)G = 0;
			if (B<0)B= 0;
			nRect.top = nRect.bottom; 
		} 
		dc.SetBkMode(TRANSPARENT);
		CFont nFont ,* nOldFont; 
		//dc.SetTextColor(RGB(250,50,50)); 
		dc.SetTextColor(m_color);
		nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,m_fontName);//创建字体 
		nOldFont = dc.SelectObject(&nFont);

		TEXTMETRIC metric;
		dc.GetTextMetrics(&metric);
		int ofst = 0;
		ofst = tRect.Height() - metric.tmHeight;
		tRect.OffsetRect(0,ofst/2);
		dc.DrawText(m_HChar[i],&tRect,DT_CENTER);
		dc.SelectObject(nOldFont); 
		nFont.DeleteObject(); //释放字体 
	} 
	//画头部剩余部分
	CRect rtRect;
	CRect clientRect;
	GetItemRect(nItem - 1,rtRect);
	GetClientRect(clientRect);
	rtRect.left = rtRect.right+1;
	rtRect.right = clientRect.right;
	int R = m_R,G = m_G,B = m_B;
	CRect nRect(rtRect);
	//绘制立体背景 
	for(int j = rtRect.top;j<=rtRect.bottom;j++) 
	{ 
		nRect.bottom = nRect.top+1; 
		CBrush _brush; 
		_brush.CreateSolidBrush(RGB(R,G,B));//创建画刷 
		dc.FillRect(&nRect,&_brush); //填充背景 
		_brush.DeleteObject(); //释放画刷 
		R-=m_Gradient;G-=m_Gradient;B-=m_Gradient;
		if (R<0)R = 0;
		if (G<0)G = 0;
		if (B<0)B= 0;
		nRect.top = nRect.bottom; 
	} 
}
LRESULT CMyHeaderCtrl::OnLayout( WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = 0;
	CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 
	HD_LAYOUT* hdl = (HD_LAYOUT *)(lParam); 
	RECT *prc = hdl->prc; 
	WINDOWPOS *pwpos = hdl->pwpos; 

	pwpos->cy = m_Height;
	prc->top = m_Height;
	//表头高度为原来1.5倍，如果要动态修改表头高度的话，将1.5设成一个全局变量 
//	int nHeight = (int)(pwpos->cy * m_Height);
//	pwpos->cy = nHeight; 
//	prc->top = nHeight; 

	return lResult; 
}