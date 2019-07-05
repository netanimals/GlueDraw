#pragma once



//��
//�߶ο�ʼ��
//�߶ξ�����
//�߶ν�����
//Բ���м��
//�ź�����--�ⲿ�����ź�
//�ź�����--�ڲ������ź�
//�ź����--�ⲿ�����ź�
//�ź����--�ڲ������ź�
//��ʱ
enum eMCType
{
	MC_NONE,
	MC_LINESTART,
	MC_LINEPASS,
	MC_LINEEND,
	MC_LINEARC,
	MC_LINEDI_OUT,
	MC_LINEDI_IN,
	MC_LINEDO_OUT,
	MC_LINEDO_IN,
	MC_DELAY,
};

//����
//�ؽ�
enum eGlueSwitch
{
	GlueSwitch_ON,
	GlueSwitch_OFF,
};


//���罺
//AB��
enum eSignMode
{
	SignMode_ELEC,
	SignMode_ABA,
};

//��ַ
//����
//X(mm)
//Y(mm)
//Z(mm)
//R(deg)
//�ٶ�(mm/s)
//�㽺����
//�������
//�ź�ģʽ
//��Ϳʱ��
//��ȫ�߶�
//��ʼ��ʱ
//������ʱ
class MCPoint
{
public:
	MCPoint(){memset(this, 0x0, sizeof(MCPoint));};
	~MCPoint(){};
public:
	int Addr;
	eMCType Type;
	double X;
	double Y;
	double Z;
	double R;
	double Speed;
	eGlueSwitch GlueSwitch;
	int DIDO;
	eSignMode SingMode;
	double GlueTime;
	double SafeHeight;
	double DelayBegin;
	double DelayEnd;
};

typedef CArray<MCPoint, MCPoint&> MCPointArr;