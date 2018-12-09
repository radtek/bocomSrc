// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
#ifndef CAR_INFO_H
#define CAR_INFO_H

#include <string>
#include "cxcore.h"

#include "ObjectColor.h"
#include "ObjTypeForOutput.h"

using namespace std;

#include <vector>

#ifndef CARNUMROW
#define CARNUMROW
enum CARNUM_ROW{ listrow=1, doublerow, other };
#endif

#ifndef SUB_VEHICLE_TYPE
#define SUB_VEHICLE_TYPE
//��������ϸ�֣�
enum SubVehicleTypeForOutput
{
	SVT_Default = 0,     //0    δ����
	SVT_Bus,             //1	���
	SVT_Truck,           //2	����
	SVT_MiniBus,       //3	�а�
	SVT_Car,             //4	�γ�
	SVT_UnKnown,         //5    δ֪
	SVT_WrongPos,        //6	����λ��̫ƫ
	SVT_MiniVan         //7	С�ͻ���
};
#endif

typedef struct _NovehiclInfo
{
	 CvRect   ObjRec;
	unsigned int     uSeq;                  //֡��
	_NovehiclInfo()
	{
		ObjRec = cvRect(0,0,1,1);
		uSeq = 0;

	}

 }NovehiclInfo;

typedef struct _CarInfo
{
    
	std::vector < _NovehiclInfo >  CharSerInf;
	int              id;                    //id�����ڻ�д
	char             strCarNum[8];          //���ƺ���

	char             wj[2];                 //�侯����С��

	int64            ts;                    //ʱ���(΢�룡)
	int              ix;                    //����ͼ������
	int              iy;
	int              iwidth;                //���ƿ��(pixels)
	int              iheight;               //���Ƹ߶�
	unsigned int     uSeq;                  //֡��
	double           wx;                    //������������
	double           wy;
	double           vx;                    //�����ٶȣ��������꣩m/s
	double           vy;
	double           ax;                    //���ٶ�
	double           ay;
	int              updateTimes;           //���´���

	unsigned int     uTimestamp;            //ʱ���(��)for yufeng
	int              color;                 //������ɫ      for yufeng
	int              vehicle_type;          //�������ʹַ֣�	   for yufeng   ����ObjTypeForOutput����
											//С��5.5С��5.5��9.5�У� ����9.5��
	int              subVehicleType;        //���ڳ���ϸ�֣�����vehicle_type������
	float	         iscarnum;              //ģ��ƥ���غ϶�  //�������Ŷ� for yufeng
	double           mean;                  //��������      for yufeng
	double           stddev;			    //���Ʒ���      for yufeng
	int              imgIndex;              //ͼ����      for yufeng
	unsigned int     uSedImgFramseq;         //�ڶ���ͼ���֡�� for yufeng
	object_color     objColor;	
	int              carnumrow;             //���Ż���˫�ų���

	CvRect           smear[20];              //
	int              smearCount;

	int              VerticalTheta;          //��ֱ��б��,�ԽǶ�Ϊ��λ
	int              HorizontalTheta;        //ˮƽ��б��,�ԽǶ�Ϊ��λ      
	int              RoadIndex;              //�������

	//�ǻ�����λ����Ϣ
	CvRect          m_NovehiclRec;

	// TODO: ��ֵ��
	int              nDirection;             //�˶�����ǰ�ƣ���Զ������Ϊ0�����棨�ӽ���Զ��Ϊ1��-1δ֪��
	
#ifdef OBJ_CORRESPONDENCE
	unsigned short   features[1000];
	int              nFeatureSize;
#endif

	bool             bIsMotorCycle;          //�Ƿ�ΪĦ�г���
	//�Ƿ�����ҵ�����ͼ
	bool             m_UseShutter;
	//����ͼ���ǵĳ���λ���Ƿ����Թ��ƻ��Ǿ�ȷ��λ
	bool             m_EstPos;
	//����������ͼ�е�λ��
	CvRect           m_CarnumPos;
	//����ͼ��֡��
	unsigned int     m_useq;
	//�����ֶ�������Ȧ������β���Ƿ����
	bool             m_BackCarnum;
	//����ͼ������ֵ
	double           m_Mean;
	//���������������
	CvRect           m_CarWholeRec;

	//�ó��ƶ�Ӧ��ץ����Ȧ��ʼʱ�̺���ֹʱ�̡�Ϊ�����Ȧ״̬��
	int64 st;

	int64 et;

	int nNoCarNum;//0:��ʾ���Ƴ�(Ĭ��ֵ);1:��ʾ���Ƴ�;2.��������ǻ������ֳ���  //��ȦĿ����ʱ����Ϊ�����Ƴ���

	_CarInfo()
	{
		
		uSedImgFramseq = 0;
		id = -1;
	    uTimestamp = 0;
	    ix = 0;
	    iy = 0;
	    iwidth = 0;
	    iheight = 0;
        uSeq = 0;
		wx = 0;
		wy = 0;
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
		updateTimes = 0;
		m_CarWholeRec = cvRect(0,0,0,0);

		ts = 0;
		color = 0;
		vehicle_type = OTHER;
		subVehicleType = SVT_Default;
		iscarnum = -1;
		mean = -1.0f;
		stddev = -1;
		imgIndex = 0;
		strCarNum[7] = '\0';
		wj[0] = '\0';
		wj[1] = '\0';
		carnumrow = 0;

		smearCount = 0;
		VerticalTheta = 0;
		HorizontalTheta = 0;
		RoadIndex       = -1;
		nDirection      = -1;

#ifdef OBJ_CORRESPONDENCE
		nFeatureSize    = 0;
#endif
		bIsMotorCycle = false;

		m_UseShutter = false;    //�Ƿ��ҵ���ͼ
		m_EstPos     = false;	//Ŀ������ͼ�е�λ���ǹ��ƵĻ�����ȷ��
		m_CarnumPos = cvRect(0,0,0,0);//Ŀ������ͼ�е�λ��
		m_NovehiclRec = cvRect(0,0,0,0);
		m_useq = 0; //��ͼ��λ��
		m_BackCarnum = false;
		m_Mean = 0.0;
		st = -1;
		et = -1;

		nNoCarNum = 0;
	}

	// �ж�ֵ�Ƿ�һ��
	bool IsDifferent(const _CarInfo &ci)
	{
		// ������Ʋ�һ������ͬ
		if (0 != strncmp(ci.strCarNum, this->strCarNum, 7*sizeof(char)) ||
			(ci.strCarNum[0] == 'L' && 0 != strncmp(ci.wj, wj, 2*sizeof(char))))
		{
			return true;
		}

		if (((int)sqrt(ci.vx * ci.vx + ci.vy * ci.vy)) != (int)(sqrt(vx * vx + vy * vy)))
		{
			return true;
		}

		if (vehicle_type != ci.vehicle_type)
		{
			return true;
		}

		return false;
	}
	
} CarInfo; 

#endif
