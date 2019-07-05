// MyHeaderCtrl.cpp : ʵ���ļ�
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
	m_fontName = L"����";
	m_color = RGB(0x33,0xff,0x99);	//250,50,50
}

CMyHeaderCtrl::~CMyHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyHeaderCtrl, CHeaderCtrl)
	ON_WM_PAINT()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()



// CMyHeaderCtrl ��Ϣ�������



void CMyHeaderCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CHeaderCtrl::OnPaint()
	int nItem; 
	nItem = GetItemCount();//�õ��м�����Ԫ 
	for(int i = 0; i<nItem;i++) 
	{ 
		CRect tRect;
		GetItemRect(i,&tRect);	//�õ�Item�ĳߴ�
		int R = m_R,G = m_G,B = m_B;
		CRect nRect(tRect);		//�����ߴ絽�µ������� 
		nRect.left+=1;			//�����ָ��ߵĵط� 

		
		{
			CRect rcSep = tRect;
			rcSep.right = rcSep.left+1;
			if (0==i)
			{
				rcSep.left -= 1;
			}
			CBrush _brush; 
			_brush.CreateSolidBrush(RGB(245,245,245));//������ˢ 
			dc.FillRect(&rcSep,&_brush); //��䱳�� 
			_brush.DeleteObject(); //�ͷŻ�ˢ 
		}
		//�������屳�� 
		for(int j = tRect.top;j<=tRect.bottom;j++) 
		{ 
			nRect.bottom = nRect.top+1; 
			CBrush _brush; 
			_brush.CreateSolidBrush(RGB(R,G,B));//������ˢ 
			dc.FillRect(&nRect,&_brush); //��䱳�� 
			_brush.DeleteObject(); //�ͷŻ�ˢ 
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
		nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,m_fontName);//�������� 
		nOldFont = dc.SelectObject(&nFont);

		TEXTMETRIC metric;
		dc.GetTextMetrics(&metric);
		int ofst = 0;
		ofst = tRect.Height() - metric.tmHeight;
		tRect.OffsetRect(0,ofst/2);
		dc.DrawText(m_HChar[i],&tRect,DT_CENTER);
		dc.SelectObject(nOldFont); 
		nFont.DeleteObject(); //�ͷ����� 
	} 
	//��ͷ��ʣ�ಿ��
	CRect rtRect;
	CRect clientRect;
	GetItemRect(nItem - 1,rtRect);
	GetClientRect(clientRect);
	rtRect.left = rtRect.right+1;
	rtRect.right = clientRect.right;
	int R = m_R,G = m_G,B = m_B;
	CRect nRect(rtRect);
	//�������屳�� 
	for(int j = rtRect.top;j<=rtRect.bottom;j++) 
	{ 
		nRect.bottom = nRect.top+1; 
		CBrush _brush; 
		_brush.CreateSolidBrush(RGB(R,G,B));//������ˢ 
		dc.FillRect(&nRect,&_brush); //��䱳�� 
		_brush.DeleteObject(); //�ͷŻ�ˢ 
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
	//��ͷ�߶�Ϊԭ��1.5�������Ҫ��̬�޸ı�ͷ�߶ȵĻ�����1.5���һ��ȫ�ֱ��� 
//	int nHeight = (int)(pwpos->cy * m_Height);
//	pwpos->cy = nHeight; 
//	prc->top = nHeight; 

	return lResult; 
}