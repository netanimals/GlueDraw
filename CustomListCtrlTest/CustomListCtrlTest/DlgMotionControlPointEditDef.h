#pragma once



//无
//线段开始点
//线段经过点
//线段结束点
//圆弧中间点
//信号输入--外部输入信号
//信号输入--内部辅助信号
//信号输出--外部输入信号
//信号输出--内部辅助信号
//延时
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

//开胶
//关胶
enum eGlueSwitch
{
	GlueSwitch_ON,
	GlueSwitch_OFF,
};


//导电胶
//AB胶
enum eSignMode
{
	SignMode_ELEC,
	SignMode_ABA,
};

//地址
//类型
//X(mm)
//Y(mm)
//Z(mm)
//R(deg)
//速度(mm/s)
//点胶开关
//输入输出
//信号模式
//点涂时间
//安全高度
//开始延时
//结束延时
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