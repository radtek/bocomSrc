// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "MvFindTargetByVirtualLoop.h"

class Parameters
{

public:
	static int RED_LIGHT_MEM_SIZE;      // ���״̬��¼֡��
	static int CAR_OBJECT_KEEP_TIME;    // Car������CarManager���汣��ʱ�䣬��λ�롣



	//////////////////////////////////////////////////////////////////////////
	// �ְ������ϵ�ֵ
	//////////////////////////////////////////////////////////////////////////
public:
	




	static int OPTICAL_FLOW_FORM_RECT_SIZE_THRESH;//       = DAY_OPTICAL_FLOW_FORM_RECT_SIZE_THRESH;       //���������ǰ��rectҪ����Ͱ����������߸�����
	static int OPTICAL_FLOW_FORM_RECT_LENGTH_THRESH;//     = DAY_OPTICAL_FLOW_FORM_RECT_LENGTH_THRESH;     //���������ǰ��rectҪ�����������߳���
	//static float CAR_FORCE_SEAL_FLOW;//                      = DAY_CAR_FORCE_SEAL_FLOW ;                     //С��ǿ������
	//static float BUS_FORCE_SEAL_FLOW;//                      = DAY_BUS_FORCE_SEAL_FLOW;                      //busǿ������
	//static float NOVEICHLE_FORCE_SEAL_FLOW;//                = DAY_NOVEICHLE_FORCE_SEAL_FLOW;                //�ǻ�ǿ������
	//static float UNKONOWN_FORCE_SEAL_FLOW ;//                = DAY_UNKONOWN_FORCE_SEAL_FLOW;
	//static float CAR_MAX_FLOW;//                             = DAY_CAR_MAX_FLOW;                             //С���������
	//static float BUS_MAX_FLOW    ;//                         = DAY_BUS_MAX_FLOW;
	//static float NONVEICHLE_MAX_FLOW ;//                     = DAY_NONVEICHLE_MAX_FLOW;
	//static float UNKNOWN_MAX_FLOW    ;//                     = DAY_UNKNOWN_MAX_FLOW;
	static float CAR_MIN_FLOW        ;//                     = DAY_CAR_MIN_FLOW;                             //С����С����
	static float BUS_MIN_FLOW       ;//                      = DAY_BUS_MIN_FLOW;
	static float NONVEICHLE_MIN_FLOW  ;//                    = DAY_NONVEICHLE_MIN_FLOW;
	static float UNKNOWN_MIN_FLOW     ;//                    = DAY_UNKNOWN_MIN_FLOW;
	static int DISAPPERA_ALLOWRANCE_FRAMES;//              = DAY_DISAPPERA_ALLOWRANCE_FRAMES;                 //����֡û�����¾���Ȼ��
	static int SEAL_RESONABLE_FRAME_DIS;//                 = 5;                                               //�Ϻ������ж�������ļ��֡��
	
	
	



	static float NONVEICHLE_WIDTH;
	static float CAR_WIDTH;
	static float BUS_WIDTH;

	static float NONVEICHLE_MIN_WIDTH;
	static float CAR_MIN_WIDTH;
	static float BUS_MIN_WIDTH;

	static float NONVEICHLE_MAX_WIDTH;
	static float CAR_MAX_WIDTH;
	static float BUS_MAX_WIDTH;


	static int CORNER_DET_MIN_DIS;
	static float CORNER_DET_QUALITY;
	
	static int BG_GRADIENT;  //������Ŀ��ֱ���ݶ���ֵ��
	static int FG_GRADIENT;


	//
	static float RED_LIGHT_VIO_PIC_FAR;
	static float RED_LIGHT_VIO_PIC_NEAR;


	// ��ֹ�����˸����ֵ��Խ��Խ���׽������г���������������к�Ʋ����ģ��򽫸�ֵ��С��
	static float PREVENT_RED_LIGHT_FLASH_THRESHOLD;

	// ��Ȧ��⳵��������������Ȧ�����ĳ���-������
	static float LOOP_VEHICLE_LEN_FIX;

	// ��Ȧ���Ŀ��֡�������������=�����+������
	static int   LOOP_OUTPUT_SEQ_PLUS;


	static bool USE_SURF;           //ʹ��ʹ��Surfƥ�������Ƶ�ٶȣ�
	static bool USE_EXTERNAL_CTRL;  //�Ƿ��ⲿ���Ƴ��ƾ��������ظ߶�!
	static int  PROJECTION_PIXEL;   //��Ƶ����ʱ�����ƾ��������ظ߶�!

	static bool USE_CHONGHONGDENG;  //�Ƿ�ʹ�ó��ƹ��ܣ�
	static bool USE_JUDGE_TURNING;  //�Ƿ�ʹ��ת������ֱ�д�������ƹ��ܣ�
	static int  MIN_TURN_ANGLE;   //��Ϊ����ת�����С�Ƕȣ�

	static void SelectParameterGroup(Time_Mode mode);
	
private:
	static int DAY_NIGHT_DISAPPERA_ALLOWRANCE_FRAMES[2];//            = 4;
	static int DAY_NIGHT_OPTICAL_FLOW_FORM_RECT_SIZE_THRESH[2];//     = 6;                
	static int DAY_NIGHT_OPTICAL_FLOW_FORM_RECT_LENGTH_THRESH[2];//   = 20;              
	//static float DAY_NIGHT_CAR_FORCE_SEAL_FLOW[2];//                    = 350;
	//static float DAY_NIGHT_BUS_FORCE_SEAL_FLOW[2] ;//                   = 800;
	//static float DAY_NIGHT_NOVEICHLE_FORCE_SEAL_FLOW[2]  ;//            = 220;
	//static float DAY_NIGHT_UNKONOWN_FORCE_SEAL_FLOW[2]  ;//             = 120;
	//static float DAY_NIGHT_CAR_MAX_FLOW[2]         ;//                  = 500;
	//static float DAY_NIGHT_BUS_MAX_FLOW[2]         ;//                  = 1050;
	//static float DAY_NIGHT_NONVEICHLE_MAX_FLOW[2]   ;//                 = 350;
	//static float DAY_NIGHT_UNKNOWN_MAX_FLOW[2]   ;//                    = 300;
	static float DAY_NIGHT_CAR_MIN_FLOW[2]       ;//                    = 200;
	static float DAY_NIGHT_BUS_MIN_FLOW[2]       ;//                    = 800;
	static float DAY_NIGHT_NONVEICHLE_MIN_FLOW[2]  ;//                  = 170;
	static float DAY_NIGHT_UNKNOWN_MIN_FLOW[2]       ;//                = 400;
	static int DAY_NIGHT_SEAL_RESONABLE_FRAME_DIS[2];

	static float DAY_NIGHT_NONVEICHLE_WIDTH[2];
	static float DAY_NIGHT_CAR_WIDTH[2];
	static float DAY_NIGHT_BUS_WIDTH[2];
	
	static float DAY_NIGHT_NONVEICHLE_MIN_WIDTH[2];
	static float DAY_NIGHT_CAR_MIN_WIDTH[2];
	static float DAY_NIGHT_BUS_MIN_WIDTH[2];

	static float DAY_NIGHT_NONVEICHLE_MAX_WIDTH[2];
	static float DAY_NIGHT_CAR_MAX_WIDTH[2];
	static float DAY_NIGHT_BUS_MAX_WIDTH[2];

	static int DAY_NIGHT_CORNER_DET_MIN_DIS[2];
	static float DAY_NIGHT_CORNER_DET_QUALITY[2];

	static int DAY_NIGHT_BG_GRADIENT[2];   
	static int DAY_NIGHT_FG_GRADIENT[2];
};


#endif