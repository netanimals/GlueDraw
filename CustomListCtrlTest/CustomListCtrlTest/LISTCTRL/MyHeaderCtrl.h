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
	CString m_Format;		//表示对齐类型的整型数组,0表示左对齐，1表示中间对齐，2表示右对齐
public:
	int m_R;
	int m_G;
	int m_B;
	int m_Gradient;			//画立体背景，渐变系数
	UINT m_Height;			//表头高度
	int m_fontHeight;		//字体高度
	int m_fontWith;			//字体宽度
	CString m_fontName;		//字体名称
	COLORREF m_color;
	LRESULT OnLayout( WPARAM wParam, LPARAM lParam );
};


