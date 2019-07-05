#pragma once


// CMyHeaderCtrl

class CMyHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CMyHeaderCtrl)

public:
	CMyHeaderCtrl();
	virtual ~CMyHeaderCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CStringArray m_HChar;
	CString m_Format;		//��ʾ�������͵���������,0��ʾ����룬1��ʾ�м���룬2��ʾ�Ҷ���
public:
	int m_R;
	int m_G;
	int m_B;
	int m_Gradient;			//�����屳��������ϵ��
	UINT m_Height;			//��ͷ�߶�
	int m_fontHeight;		//����߶�
	int m_fontWith;			//������
	CString m_fontName;		//��������
	COLORREF m_color;
	LRESULT OnLayout( WPARAM wParam, LPARAM lParam );
};


