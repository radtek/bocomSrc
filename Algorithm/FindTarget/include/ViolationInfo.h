#ifndef VIOLATIONINFO_H
#define VIOLATIONINFO_H

#include "CarInfo.h"

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

	DSP_EVT_PERSON_AGAINST,			//DETECT_RESULT_EVENT_PERSON_AGAINST, //11 ��������
	DSP_EVT_CROSS,					//30	DETECT_RESULT_EVENT_CROSS,		    //12 �����ᴩ
	DSP_EVT_PERSON_APPEAR,			//31	DETECT_RESULT_EVENT_PERSON_APPEAR,  //13 ���˳���
	DSP_EVT_APPEAR,				    //32	DETECT_RESULT_EVENT_APPEAR,		    //14 ����������
	DSP_EVT_DECILIT,				 //33	������
	EVT_NO_PARKING,                  //34    ������ͣ��
	EVT_BREAK_GATE,					//35    �忨
	EVT_NOT_CUTRTESY_DRIVE,			//36	û����������

	EVT_CROSSLINE_STOP,				//37	Խ��ͣ��
	EVT_GASSER,						//38    ����
	ELE_ARROW_RED_VIO,              //39   ��ͷ�����
	ELE_CIRCLE_RED_VIO,              //40	Բ�δ����
	ELE_ONE_WAY_STREET_VIO,          //41	���е�������
	EVT_TAKE_UP_EMERGENCYWAY    //42  ռ��Ӧ������
};

enum VIO_EVENT_RECORD
{
	EVT_FORE_FIRST_RECORD,			//0 ѹ��һ����תǰ���߼�¼
	EVT_STOP_SECOND_RECORD			//1 ѹ�ڶ�����תֹͣ���߼�¼
};

typedef struct _ViolationInfo
{
	int          id;
	CarInfo carInfo;             // ����Ƶĳ�����Ϣ����Ҫ�ǣ����ƺ��롢��ɫ���ٶȡ����û�г�����******��*++++++*��ʾ��
	unsigned int frameSeqs[20];  // �����䴳��Ƶ���֡ͼ���֡�š�
	unsigned int dis[20];        // �ڴ�����¼������ڱ�ʾ3֡ͼƬ���ƿ�ʼ֡�ļ����֡����
	unsigned int uUpperFrm, uLowerFrm;  //ȡ��ͼʱ���жϵ�һ��ͼ�������ޣ�
	int64        redLightStartTime;   //��ƿ�ʼʱ�䣡
	int          index[20];
	int          nPicCount;      // ͼ����

	int          nChannel;       // �����ţ�-1��δ֪
	VIO_EVENT_TYPE evtType;      // �¼�����

	int          nChannelTurnDir;  //����������ʻ�������ԣ�-1,��ת��������ת+ֱ�г�����1����ת��������ת+ֱ�г�����

	bool         bFlagHoldReg;    //�Ƿ�Ϊ��ת������ƣ���Ҫ�����ڵ�������ʱȡͼ�� //true��ʾ�Ǵ�ת��
	MvLine*       pLineTouch;      //������������ֱ���ĸ��ֱ��Ĵ���� 
	unsigned int uFirstRedLightFrame;// = 0;
	int          nRedLightTime;
	int          nRedLightViolationAllowance;
	int          nOutState; //��0���洢��1�����2:ɾ��
	_ViolationInfo()
	{
		nChannelTurnDir = -2;  //δ֪��
		nChannel  = -1;
		nPicCount = 3;
		uUpperFrm = 0; uLowerFrm = 0;
		redLightStartTime = -1;
		memset(dis, 0, 3*sizeof(unsigned int));
		bFlagHoldReg = false;
		uFirstRedLightFrame = 0;
		nRedLightTime = 0;
		nRedLightViolationAllowance = 0;
		nOutState = 1;		
	}
} ViolationInfo;

typedef struct _VioPressRecode
{
	unsigned int frameSeqsFore;  // �����䴳���ѹ��һ��תǰ���ߵ�֡�š�
	unsigned int frameSeqsStop;  // �����䴳���ѹ�ڶ���תֹͣ�ߵ�֡�š�
	VIO_EVENT_RECORD evtType;      // �¼�����
	_VioPressRecode()
	{
		frameSeqsFore = 0;
		frameSeqsStop = 0;
	}
} VioPressRecode;

#endif
