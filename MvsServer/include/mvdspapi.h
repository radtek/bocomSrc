/* ��Ȩ���� 2013 �Ϻ�����������Ϣ�������޹�˾
* Copyright (c) 2013��Shanghai Bocom Intelligent Information Technologies Ltd
* �������ܹ�˾����
* Bocom Intelligent Confidential Proprietary
* �ļ����ƣ�MvDspAPI.h
* ժҪ: 
* �汾: SVN 1611
* ����: 
* �������: 2013��1��11��
* �޸�˵����1��PCӦ����Ҫ����һ���꿪��  #define MV_DSP_USE_SLIM_STRU
*			2��2013-2-27 �汾1184 ���ӵ�·���������߶�
*			3��2013-3-14 �汾1224 ����Ԥ��GlobeLineԤ���ֶ�	
*			4��2013-3-19 �汾1234 Ϊ�˼����Կ��ǣ�ȥ��GlobeLineԤ���ֶ�
*			5��2013-3-26 �汾1274 ��������汾��
*			6��2013-3-28 �汾1289 ���Ӷ��¼���֧��
*			7��2013-4-1  �汾1294 MvDspGlobalSetting    ���ӿ���ͼƬ�������
*								  busReserved[4096];    ����Ԥ���ֶ�
*								  �ṹCarInfo�����ֶ� unsigned int	pExtFrame[4];	
*			8��2013-4-18 �汾1359 ���ӳ������԰��մ�С���ֱ����г���
*			9��2013-4-18 �汾1362 ���ӳ��������������ж�
*			10��2013-05-13 svn1443 �����������ӳ�����ʻ�ٶȵ����趨�ı����ٶ�
*			11��2013-05-20 svn1465 ֧�ֻ������Զ��з�
*			12��2013-07-01 svn1669 �����������Ŀ��������С MvRect rtContour;	//����Ŀ�����֡��������С����ʼ��ӦΪ(0,0,0,0)
*           13��2014-02-24 svn141  ���нṹ�������õ���������չ�����ӳ��٣���ʱ��α���
*			14��2014-05-04 svn220  1.���ӳ��Ʒ��� 2.����ͳ����Ϣ
*			15��2014-06-16 svn317  1.����������⹦�� 2�����Ƴ�Υ�¼�� 3��Խ��ͣ�����
*/
#ifndef ALGORITHM_YUV

#ifndef MV_DSP_API_H__
#define MV_DSP_API_H__
#include "declare.h"

#define MAX_IMG_WIDTH		432
#define MAX_IMG_HEIGHT		360

#define L_MAX_IMG_WIDTH		480
#define L_MAX_IMG_HEIGHT	400

#define MON 0x01//��һ
#define TUE 0x02//�ܶ�
#define WEN 0x04//����
#define THU 0x08//����
#define FRI 0x10//����
#define SAT 0x20//����
#define SUN 0x40//����
#define WEK 0x7F//ȫ��
#define WED 0x60//����������
#define WKD 0x1F//��һ�����壬������

#define DO_CAR_NUM_DETECT			0x001           // �Ƿ���г��ƹ��ˡ������ڲ�Ĭ�ϴ򿪡�
#define DO_FIND_TARGET				0x002           // �Ƿ���п���Ŀ����
#define DO_ELE_POLICE				0x004           // ���Ӿ���
#define DO_COLOR_DETECT				0x008           // �����ɫ
#define DO_VEHICLE_TYPE				0x010           // ���ͼ��
#define DO_LOOP_SHUTTER				0x020			// ��Ȧ����
#define DO_DSP_EVENT				0x040			// �¼����
#define DO_NOPLATE					0x080			// ���Ƴ�Υ�¼��
#define DO_LOOP_DETECT				0x100           // ��Ȧ���
#define DO_ON_BUS_VIO_DET			0x200           // ���ؼ��
#define DO_RADAR_DETECT				0x400           // �״���
#define DO_VIOLATION_DETECT			0x800           // Υ�¼��
#define DO_DETECT_TRAFFIC_LIGHT		0x1000			// ��Ƶ�����̵�
#define DO_LASER_DETECT				0x2000			// ������
#define DO_VIDEO_SHUTTER			0x8000			// ��Ƶ����

#ifdef MV_DSP_ENV
#define int64  long long
//typedef int  bool;
//const int true = 1;
//const int false = 0;
#endif

/*
enum ObjTypeForOutput
{
	OTHER = 1,     // δ֪
	PERSON,        // ����5
	TWO_WHEEL,     // ���ֳ�
	SMALL,         // С 1
	MIDDLE,        // �� 2
	BIG,           // �� 3
};*/

typedef struct _MvRect
{
	int x;
	int y;
	int width;
	int height;
}MvRect;

 /*MvRect  mvRect( int x, int y, int width, int height )
{
	MvRect r;

	r.x = x;
	r.y = y;
	r.width = width;
	r.height = height;

	return r;
}*/

typedef struct DspMvPoint
{
	int x;
	int y;
}DspMvPoint;
/*
static  DspMvPoint  mvPoint( int x, int y )
{
	DspMvPoint p;

	p.x = x;
	p.y = y;

	return p;
}
*/
//����ź�
typedef struct _DSP_VTS_SIGNAL_STATUS
{
	int  nRoadIndex;	   //�������
	unsigned int uFrameSeq;

	int bLeftSignal;     //��ת��״̬.���true���̵�false��
	int bStraightSignal; //ֱ�е�״̬
	int bRightSignal;    //��ת��״̬

	/*
	_VTS_SIGNAL_STATUS()
	{
		uFrameSeq       = 0;
		nRoadIndex      = -1;
		bLeftSignal     = 0;
		bStraightSignal = 0;
		bRightSignal    = 0;
	}
	*/

}Dsp_VTS_SIGNAL_STATUS, DspMvChannelFrameSignalStatus;

typedef struct MvPoint2D64f
{
	double x;
	double y;
}
MvPoint2D64f;


static  MvPoint2D64f  mvPoint2D64f( double x, double y )
{
	MvPoint2D64f p;

	p.x = x;
	p.y = y;

	return p;
}


typedef struct _DspMvLine
{
	// ͼ�����ꡣ
	DspMvPoint start;  //(Ӧ������)
	DspMvPoint end;    //��Ӧ�����ã�

}DspMvLine;

typedef struct _MV_DSP_CAR_INFO
{
	char   strCarNum[8];  //���ƺ���
	char   wj[2];         //�侯����С��

	int64				ts;					//ʱ���(΢��)
	unsigned int		nFrame;				//֡��
	unsigned int		nX;					//����ͼ������
	unsigned int		nY;
	unsigned int		nWidth;				//���ƿ��(pixels)
	unsigned int		nHeight;			//���Ƹ߶�

	unsigned int		fVelocity;			//�����ٶȣ�km/H��

	unsigned int		nCarnumMean;		//��������
	unsigned int		nColor;				//��ɫ
	unsigned int		uPlateType;			//�������� 
	unsigned int		nVehicleType;		//�������ʹַ֣�С��5.5С��5.5��9.5�У� ����9.5��

	unsigned int		nChannel;			//������

	float  iscarnum;      //ģ��ƥ���غ϶�,���Ŷȷ�Χ��0,1����Խ��Խ���ɿ�

	unsigned int		pExtFrame[4];		//
	MvRect				rtContour;			//����Ŀ�����֡��������С����ʼ��ӦΪ(0,0,0,0)
} MvDspCarInfo, DspCarInfo;

// ��ֹͨ����Ϣ��
// ������ֹͨ�е�ʱ��Σ��Լ���ֹͨ�еĳ������͡�
typedef struct _DspNoPassingInfo
{
	unsigned char ucWeekDay; //��ֹͨ�е����졣���԰�λ�� (Ӧ������)

	int nStart;   // ��ֹͨ��ʱ��Ͽ�ʼ����0ʱ0��0�뵽��ֹͨ��ʱ���������  (Ӧ������)
	int nEnd;     // �����1�㵽�����ǽ���ʱ�䣬��nStart = 1*60*60, nEnd = 2*60*60     (Ӧ������)

	int nVehType; // //0��ʾ�����У�1��ʾ����С����2��ʾ���д󳵣�3��ʾ�������г���   (Ӧ������)
	               ////��Ҫ���䶨��4��ʾ����5��ʾ���ҡ�6��ʾ��ǰ��7��ʾ���١�8��ʾ���д����
    /*
	_NoPassingInfo()
	{
		ucWeekDay = WEK;
		nStart    = -1;
		nEnd      = -1;
		nVehType  = 0;
	}
	*/
} DspNoPassingInfo;


typedef struct _MV_DSP_REGION
{
	DspMvPoint arrList[16];
	int nPoints;
}MvDspRegion;


/*
�����ṹ�塣
*/
typedef struct _DspChannelRegion
{
	int			nRoadIndex;	//������ţ�Ӧ�����ã�
	int			nVerRoadIndex; //�����߼���ţ���ʱû���ô�����Ӧ�����ã�
	int			nDirection;    //��������Ӧ�����ã����������Ұ��ᣬ��ˮƽ����Ϊ��㣬˳ʱ��ת�����ýǶȣ�
	DspMvLine		vDirection;    //���������ߣ�Ӧ�����ã�

	DspMvPoint		arrListChannel[16];     //��������Ӧ�����ã�
	
	int			nPhysicalLoop;			//������Ȧ������Ӧ�����ã�
	float		fLoopDist;				//������Ȧ֮��ľ��루Ӧ�����ã�Ĭ��Ϊ5m��
	
	int			nChannlePointNumber;  //����ÿ����������Ķ��������Ӧ�����ã�
	int			bNoTurnLeft;		//����Ӧ�����ã�
	int			bNoTurnRight;		//���ң�Ӧ�����ã�
	int			bNoForeward;		//��ֹǰ�У�Ӧ�����ã�

	int     bNoReverse;				// ��ֹ���У�Ӧ�����ã�
	int     bNoPressLine;			//��ֹѹ�ߣ���Ӧ�����ã�
	int     bNoChangeChannel;		//��ֹ�������Ӧ�����ã�

	int     nNoTurnAround;          //��ֹ��ͷ ����Ӧ������
    int     nNonMotorWay;           // �Ƿ�Ϊ�ǻ���������־����0��ʾ����������1��ʾ�ǻ�������
	                                // 2��ʾ����������3��ʾ���ǻ��г�����4��ʾ���е�����Ӧ������

	//������ʻ����:ֱ�г���0����ת����1����ת+ֱ�г���2����ת����3����ת+ֱ�г���4,�ȣ�
	int      nChannelDriveDir; //��Ӧ�����ã�
	DspMvLine   vForeLine;  //ÿ����һ��ǰ���ߣ���Ӧ�����ã������ԭͼ���꣡���Ǵ���MvViolationDetecter��ֹͣ�ߺ�vDirection�����߶�Ϊ��Сͼ���꣬��һ��Ҫע�⣡

	//ÿ������һ��ֹͣ��
	DspMvLine   vStopLine;  //��Ӧ�����ã�


	//��ת��
	int     bFlagHoldStopReg;  //�Ƿ���ڴ�ת����Ӧ�����ã�
	DspMvLine   vHoldForeLineFirst;  //��ת����һǰ���ߣ�Ӧ�����ã�
	DspMvLine   vHoldForeLineSecond;  //��ת���ڶ�ǰ���ߣ�Ӧ�����ã�
	DspMvLine   vHoldStopLineFirst;    //��ת����һֹͣ�ߣ�Ӧ�����ã�
	DspMvLine   vHoldStopLineSecond;    //��ת���ڶ�ֹͣ�ߣ�Ӧ�����ã�
 
	MvRect OnOffRed;      //�������Ӧ�����ã�
    MvRect OnOffGreen;    //�̵�����Ӧ�����ã�

	//������
	MvRect roiLeftLight;   //��ߵ�����Ӧ�����ã�
	MvRect roiMidLight;    //�м������Ӧ�����ã�
	MvRect roiRightLight;  //�ұߵ�����Ӧ�����ã�
	MvRect roiTurnAroundLight; //���������Ӧ�����ã�

	//�����ǿ�õ�
	MvRect roiLeftLight_red, roiLeftLight_green;  //��ߺ졢�̵�����Ӧ�����ã�
	MvRect roiMidLight_red, roiMidLight_green;    //�м�졢�̵�����Ӧ�����ã�
	MvRect roiRightLight_red, roiRightLight_green; //�ұߺ졢�̵�����Ӧ�����ã�
	MvRect roiTurnAroundLight_red, roiTurnAroundLight_green; //����졢�̵�����Ӧ�����ã�

	MvRect rectMedianPos;  //����ƻ�羯ʱ���ɿͻ���ָ���ĵڶ���ͼ�ĳ���λ�á�(Ӧ������)����̫���ϣ�������ת����ת�羯�Ϳ���ȡ���������е�ȡͼ���ðɣ�

	DspNoPassingInfo   vecNoPassingInfo[24]; //��ֹͨ��ʱ������ԣ�Ӧ�����ã�
	int             nNoPassingInfoNumber;  //��ֹͨ����ʱ��θ�����Ӧ�����ã�

	int nRadarAlarmVelo;				//�״�Ԥ���ٶ�
	
	int64          m_pRedLightDelayTime[2];    //����ӳ�ʱ�䣨�룩��ÿ����������ʱ��Σ�[0]�ź��ӳٽ���ʱ�䣬[1]��Ƶĳ���ʱ��

	int  nLeftControl;  //��ת���� (ȡֵ��Χ0-11)
	int  nStraightControl;  //ֱ�п���(ȡֵ��Χ0-11)
	int nRightControl;   //��ת����(ȡֵ��Χ0-11)
	
	//����0����ֱ��1������2����ֱ��3������4����ֱ��5������6����ֱ��7������8�����ң�9�����ң�10�����ң�11������

	int  nJamp;               //�Ƿ��жϽ�ͨӵ�£�1���ǣ� 0����
    int  nPassagerCross;      //�Ƿ��ж����˺ᴩ��1���ǣ� 0����
	int  nCarSlow;            //�Ƿ��жϳ������У�1���ǣ� 0����
	int  nPerson_Stop;        //�Ƿ��ж�����ͣ����1���ǣ� 0����
	int  nNonMotorAppear;     //�Ƿ��жϷǻ��������֣� 1���ǣ� 0����
	int  nPerson_Against;     //�Ƿ��ж��������У�1���ǣ� 0����
	int  nCarCross;           //�Ƿ��жϳ����ᴩ�� 1���ǣ�0����
	int  nPersonAppear;       //�Ƿ��ж����˳��֣� 1���ǣ�0����
	int  nCarAppear;          //�Ƿ��жϻ��������֣�1:�ǣ�0����
	int  nDelicit;				//�������жϣ� 1���ǣ� 0�� ��

	//˵����������������ٶ�Ϊ0�������nRadarAlarmVelo�����ֵ
	unsigned int uAlarmBig;			//������
	unsigned int uAlarmSmall;		//С������

	int nCarStop;				//�Ƿ��ж�ͣ���¼�
	int nStopTime;				//ͣ����ñ���(��λ��)
	
	unsigned int uLowThresh;		//������ʻ�ٶȵ����趨�ı����ٶȣ�

	int bCrossLineStop;				//Խ��ͣ����� Ĭ��Ϊ0 

	char pReserved[2048-1028];			//Ԥ���ֶ�
 
}DspChannelRegion;


typedef struct _GlobeLine
{
	// ���Ӿ���ĸ����ߣ�����ڵ羯��Сͼ��
	DspMvLine           m_stopLine;   //��·ֹͣ�ߣ�Ӧ�����ã�
	DspMvLine           m_foreLine;   //��·ǰ���ߣ�Ӧ�����ã�
	DspMvLine           m_rightLine;  //�����ߣ�Ӧ�����ã�
	DspMvLine           m_leftLine;   //�����ߣ�Ӧ�����ã�


	DspMvLine           m_firstLine;		//�羯��һ�����ߣ�Ӧ�����ã�
	DspMvLine           m_secondLine;  //	//�羯�ڶ������ߣ�Ӧ�����ã�
	DspMvLine           m_rightLineOri;	//���ҳ�ʼ�����ߣ�Ӧ�����ã�
	DspMvLine           m_leftLineOri;		//�����ʼ�����ߣ�Ӧ�����ã�
	DspMvLine           m_foreLineOri;     //��ǰ��ʼ�����ߣ�Ӧ�����ã�

	//�����ж���
	DspMvLine m_vecYellowLine[8];    //���ߣ�Ӧ�����ã�
	DspMvLine m_vecWhiteLine[8];     //���ߣ�Ӧ�����ã�
	DspMvLine m_vecBianDaoXian[8];   //����ߣ�Ӧ�����ã�
	int    m_vecYellowNumber;     //���ߵ�������Ӧ�����ã�
	int    m_vecWhiteNumber;      //���ߵ�������Ӧ�����ã�
	int    m_vecBianDaoXianNumber;  //����ߵ�������Ӧ�����ã�

    DspMvLine  m_NoTurnAroundLine;     //��ֹ��ͷ�� ����Ӧ������
    DspMvLine  m_NoTurnAroundLineOri;     //��ֹ��ͷ��ʼ������ ����Ӧ������

	//unsigned char pReserved[1024-572];


}GlobeLine;

//��·������
typedef struct _MV_DSP_ROAD_REGIN
{
	int direct;	//����
	DspMvPoint arrList[16];
	int nPoints;
}MvDspRoadRegion;

//�漰�����ݽṹ
//�漰��ȫ�ֲ���
typedef struct _MV_DSP_GLOBAL_SETTING
{
	int nWidth;           //ͼ��Ŀ�ȣ�Ӧ�����ã�
	int nHeight;          //ͼ��ĸ߶ȣ�Ӧ�����ã�

	float m_fScaleX;			//m_nWidth*m_nScaleX==ԭͼ�Ŀ�-  ��ȵ����ű�����Ӧ�����ã�				
	float m_fScaleY;            //�߶ȵ����ű�����Ӧ�����ã�
 
    int nCheckType;			//���������ͣ�Ӧ�����ã�
	
	MvRect m_rtCarNum;		//���Ƽ����,�����Сͼ��λ�ã�Ӧ�����ã�

	int nChannels;					//������Ŀ��Ӧ�����ã�
	DspChannelRegion ChnlRegion[8];    //�������ԣ�Ӧ�����ã�
	//
	GlobeLine gLines;			//ȫ���õ����ߣ�Ӧ�����ã�
	
	unsigned short m_pMaxSizeX[MAX_IMG_HEIGHT];	//
	unsigned short m_pMaxSizeY[MAX_IMG_HEIGHT];
	float m_pWorldX[MAX_IMG_HEIGHT];
	float m_pWorldY[MAX_IMG_HEIGHT];

    MvRect m_rtRemoteCarNum;				//Զ�����ƴ�С
	MvRect m_rtLocalCarNum;					//�������ƴ�С

	int				m_nMaskRegionCount;		//����������Ŀ
	MvDspRegion		m_pMaskRegion[8];		//������	
	
	int             nNoPutInRegNum;			//��ֹʻ������Ŀ����Ӧ������ 
	MvDspRegion     NoPutInReg[8];			//��ֹʻ���� ����Ӧ������

	int             nNoStopRegNum;			//��ͣ����Ŀ����Ӧ������
    MvDspRegion     NoStopReg[8];			//��ͣ�� ����Ӧ������

	int             nNoResortRegNum;		//��ֹ��������Ŀ����Ӧ������
    MvDspRegion     NoResortReg[8];			//��ֹ·�������� ����Ӧ������

	int			m_nDelayOutput;				//�����ӳ����ʱ��(�����ã���λ����)

	//�궨6�����Ӧ��ͼ���������������
	float m_pXYImage[12];					//��ԭͼλ��
	float m_pXYWorld[12];					//ԭͼ��Ӧλ��

	int m_nRoadCount;						//��·����,��������ĸ�
	MvDspRoadRegion m_pRoadRegion[4];		//��·����
	
	MvDspRegion vioRegion;					//Υ�¼������
	
	float		cameraHeight;				//������߶�

	int nVersion;							//�汾��

	int				nCarPicCount;			//�������������Ĭ��Ϊ1

	MvDspRegion parkingRegion;				//����������

	int nMode;								//0:��ͨģʽ��16Ϊ����ģʽ��Ĭ��Ϊ0

	int nIsRankVio;                         //�Ƿ����Υ�·ּ���0����1����
	int pVioTypeRank[64];                   //�ṹenum VIO_EVENT_TYPE��ÿ��Υ�����Ͷ�Ӧ�ĵȼ���
	                                        //Ĭ��0���ּ�����9������9������ߣ�1���

	int nBreakGate;							//�Ƿ�忨

	int nNotCoutesyDrive;					//�Ƿ���������

	int bStrictMode;						//�Ƿ�Ϊ�ϸ�ģʽ

	int nFrameRate;

	int nFluxDetect;						//�Ƿ�������ͳ�ƣ�Ĭ��Ϊ0

	unsigned char reserved[1024*32-26796];

	unsigned short m_pSizeX[512];	//
	unsigned short m_pSizeY[512];
	float m_pWY[512];

	unsigned char busReserved[4096];		//����Ԥ���ֶ�


}MvDspGlobalSetting;



//����ʱÿ֡��Ҫ���������
typedef struct _MV_DSP_GLOBAL_PARA
{
	int m_nIsDay;			//1 ����, 0 ҹ�� -1�Զ��ж�
	
	unsigned int nFrameIndex;	//֡��
	int64 ts;					//ʱ���(��΢��Ϊ��λ)

	int nCarNum;			//��������
	DspCarInfo arrCarInfo[16];	//������Ϣ

	DspMvChannelFrameSignalStatus arrChnl[8];		//�����ź�״̬��Ҫ�ͳ�����Ӧ

	int arPhysicalLoopStatus[8][2];			//������Ȧ״̬
	int64 arPhyLoopTs[8];			//������Ȧ�ɼ��źŶ�Ӧʱ���
	
	unsigned char arrImageStatus[8];		//��ͼ״̬��1-��ͼ�� 0-����ͼ

	unsigned char *pImage;			//ͼ����Ϣ

	unsigned int m_pRadar[8];  //��¼ÿ���������״����ֵ

}MvDspGlobalPara;

/*
enum VIO_EVENT_TYPE
{
	ELE_RED_LIGHT_VIOLATION,        // 0	�����
	ELE_PARKING_VIOLATION,          // 1	Υ��ͣ��
	ELE_FORBID_LEFT,                // 2	��ֹ���
	ELE_FORBID_RIGHT,               // 3	��ֹ�ҹ�
	ELE_FORBID_STRAIGHT,            // 4	��ֹǰ��
	ELE_RETROGRADE_MOTION,          // 5	����
	ELE_PRESS_LINE,                 // 6	ѹ����
	ELE_PRESS_WHITE_LINE,           // 7	ѹ����
	ELE_NO_PASSING,                 // 8	����
	ELE_EVT_BIANDAO,                // 9	���
	OBV_TAKE_UP_BUSWAY,             // 10	ռ�ù�����

	EVT_CYC_APPEAR, 				//11	���ͳ�����
	EVT_FORBID_TRUCK,				//12	�������
	EVT_GO_FAST,                    //13	��������
	EVT_NON_LOCAL_PLATE,            //14	�Ǳ��س���
	EVT_YELLOW_PLATE,               //15	���Ƴ���
	EVT_CYC_YELLOE_PLATE,           //16	���Ʋ��ͳ���
	EVT_TAKE_UP_NONMOTORWAY,        //17	��ռ��

	EVT_FORBID_SMALL,				//18	����С��
	EVT_FORBID_BIG,					//19	���д�
	
	EVT_NO_PUTIN,                   //20	��ֹʻ��
	EVT_NO_STOP,                    //21	��ͣ
	EVT_NO_RESORT,                  //22	·������
	EVT_NO_TURNAROUND,               //23	��ֹ��ͷ

	DSP_EVT_JAM,					//24    ��ͨӵ�£���Ӧ�¼�DETECT_RESULT_TYPE::DETECT_RESULT_EVENT_JAM
	DSP_EVT_PASSBY,					//25	���˺ᴩ, DETECT_RESULT_TYPE::DETECT_RESULT_EVENT_PASSERBY,			
	DSP_EVT_SLOW,					//26	��������, DETECT_RESULT_TYPE::DETECT_RESULT_EVENT_GO_SLOW,		
	DSP_EVT_PERSON_STOP,			//27	DETECT_RESULT_EVENT_PERSON_STOP,	//9 ����ͣ��
	DSP_EVT_WRONG_CHAN,				//28	DETECT_RESULT_EVENT_WRONG_CHAN,		//10 �ǻ���������
	DSP_EVT_PERSON_AGAINST,			//29	DETECT_RESULT_EVENT_PERSON_AGAINST, //11 ��������
	DSP_EVT_CROSS,					//30	DETECT_RESULT_EVENT_CROSS,		    //12 �����ᴩ
	DSP_EVT_PERSON_APPEAR,			//31	DETECT_RESULT_EVENT_PERSON_APPEAR,  //13 ���˳���
	DSP_EVT_APPEAR,					//32	DETECT_RESULT_EVENT_APPEAR,		    //14 ����������
	DSP_EVT_DECILIT,				//33	������
	
	EVT_NO_PARKING,					//34	��ͣ������Ⱥ�(������)
	EVT_BREAK_GATE,					//35    �忨

	EVT_NOT_CUTRTESY_DRIVE,			//36	û����������

	EVT_CROSSLINE_STOP				//37	Խ��ͣ��
	EVT_GASSER						//38    ����

	OBV_TAKE_UP_BUSWAY_1 //39.���������ڵ����� һ.�����ߵ��Ҳ�1�������ߵ����2�������㷨�������������� 
	OBV_TAKE_UP_BUSWAY_2 //40.�ǹ��������ڣ����г����� ��.�����ߵ����3�������ߵ��Ҳ�4�� 
	OBV_TAKE_UP_BUSWAY_3 //41.�㷨�ڲ��������� ��.�����㷨1/3��ͣ��·�ڡ��Ҳ��г���ת���ͷ�� 
	OBV_TAKE_UP_BUSWAY_4 //42.δ���������߼����� ��.δ���������ߵġ� 
};
*/


typedef struct _DspViolationInfo
{
	DspCarInfo carInfo;             // ����Ƶĳ�����Ϣ����Ҫ�ǣ����ƺ��롢��ɫ���ٶȡ����û�г�����******��*++++++*��ʾ��
	unsigned int frameSeqs[16];  // �����䴳��Ƶ���֡ͼ���֡�š�
	unsigned int dis[16];        // �ڴ�����¼������ڱ�ʾ3֡ͼƬ���ƿ�ʼ֡�ļ����֡����
	unsigned int uUpperFrm, uLowerFrm;  //ȡ��ͼʱ���жϵ�һ��ͼ�������ޣ�
	int64        redLightStartTime;   //��ƿ�ʼʱ�䣡
	//int          index[20];
	int          nPicCount;      // ͼ����

	int          nChannel;       // �����ţ�-1��δ֪
	int          evtType;        // �¼�����

	int          nChannelTurnDir;  //����������ʻ�������ԣ�-1,��ת��������ת+ֱ�г�����1����ת��������ת+ֱ�г�����
	/*
	_ViolationInfo()
	{
		nChannelTurnDir = -2;  //δ֪��
		nChannel  = -1;
		nPicCount = 3;
		uUpperFrm = 0; uLowerFrm = 0;
		redLightStartTime = -1;
		memset(dis, 0, 3*sizeof(unsigned int));
	}
	*/
} DspViolationInfo;

typedef struct _MV_DSP_OUTPUT
{
	int nCarinfoNum;		//���ƻ���Ŀ������
	DspCarInfo pCarInfo[16];

	int nViNum;				//Υ������
	DspViolationInfo pViInfo[16];

	int nCodingNum;
	unsigned int pCodingIndex[16];

	int nDelNum;
	unsigned int pDelIndex[16];

	unsigned char uChalShutState[8];    //��������״̬

	int nStatus;					//��¼����ִ�е�״̬
	char pMsg[256];		

}MvDspOutPut;


typedef struct _MV_DSP_STATINFO
{
	int nChnl;					// �������
	int nFlux;					// ʵʱ��ͨ����
	unsigned int nAvgVelo;		// ƽ������,��λ������/Сʱ
	unsigned int nOccupyRatio;	// ƽ��ռ���ʣ���λ��%
	unsigned int nAvgDis;		// ƽ����ͷ��ࣻ��λ����
}MvDspStatInfo;


//==========================================================
//	�ӿں���
//**********************************************************
//1��MvInit()
//2��MvUnInit()
//3��MvInput()
//4��MvOutPut()
//**********************************************************

/************************************************************************/
/* ����˵������ʼ������
   ����˵����pSetting	������Ϣ�������ַ	
			 pPara		������Ϣ�������ַ
			 pOutPut	ÿ֡���صĽ��
*/
/************************************************************************/
int mvInit();

int mvUnInit();


int mvInput();		//�������ݵ�pPara

int mvOutput();		//��ȡpOutPut����

int mvInquireStaticInfo(MvDspStatInfo pStatInfo[8]);		//��ȡ������ͳ����Ϣ

int mvGetVersion(char * ver);	//��ȡ�汾��

#endif

#endif
