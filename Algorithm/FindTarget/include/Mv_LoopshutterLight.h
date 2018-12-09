// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef MV_LOOPSHUTTERLIGHT_H_ 
#define MV_LOOPSHUTTERLIGHT_H_

#include <stdio.h>
#include <time.h>
#include <vector>

//#include "cxtypes.h"

#include "Car.h"


#define  BUFFER_SIZE_LIGHT  1000

#define  ROADINDEX_BUFFER_SIZE 5


using namespace std;
typedef struct	_MVVIDEOSHUTTERPAR{
	int64 ts;   //ʱ���
	bool  bFlagShutter;//�Ƿ񴥷�������
	int   nRoadIndex;//���ڵĳ�����
    bool  bHavReprted;
	_MVVIDEOSHUTTERPAR()
	{
		ts = -1;
		bFlagShutter = false;
		nRoadIndex = -1;
		bHavReprted = false;
	}
}mvvideoshutterpar;


//�����Ȧ״̬�ṹ
typedef struct _MV_PHYSIC_LOOP_STATUS{
	int64 ts;//ʱ���
	bool b0; //������Ȧ״̬
	bool b1; //ץ����Ȧ״̬
	_MV_PHYSIC_LOOP_STATUS()
	{
		ts = -1;
		b0 = false;
		b1 = false;
	}
}mv_physic_loop_status;

typedef struct _LoopShuterobj
{
	int64  nTimes;
	unsigned int nFreqNum;
	double dMean;
	uchar  uModelGain;
	uchar  uCurrentGain;
	bool   bDspShutter;
	//bool   bPlus;//��Ƶ�����ź�
	mvvideoshutterpar  m_VideoShutter[5];	

	mv_physic_loop_status m_Loop_Status[ROADINDEX_BUFFER_SIZE];//���һ���������5����Ȧ

	_LoopShuterobj()
	{
		nTimes = 0;
		nFreqNum = 0;
		dMean = 0.0;
		uModelGain = 0;
		uCurrentGain = 0;	
		bDspShutter = false;
		//bPlus = false;
	}

}LoopShuterobj;


class Mv_LoopShutterLight
{
public:
	Mv_LoopShutterLight();
	~Mv_LoopShutterLight();

	void mv_UpDateNumber( );
	void mv_UpDateBuffer( LoopShuterobj obj );
	void mv_UpDatePhysicalLoopStatusBuffer( int64 ts, bool b0, bool b1, int nRoadIndex );
	bool mv_FixuSeq(Car *pCar, int nRoadIndex, int64 st, int64 et, Time_Mode mode, unsigned int &useqframe, double &mean, bool bVideoShutter,
		bool bFlagDsp,bool &bFindBrit ,bool bRecord =true);
	double mv_GetBackGroundLight( );
	float mv_GetCurrentGainScale();
	uchar mv_GetCurrentGain();
	void mv_UpDateVideoBuffer( vector<mvvideoshutterpar> videoshutterpar );
	bool mv_GetStartAndEenTime(Car *pCar, int nRoadIndex, int64 &nStartTime, int64 &nEndTime, unsigned int &useqframe, bool bFlag, 
		Time_Mode m_mode ,bool bDir=true,bool bRecord = true); //��Զ����Ϊtrue.����Ϊfalse

	void  mv_SetVideoShutter( bool m_physic_loop, bool m_video_loop );

	int mv_CheckPhsicalStatus( int64 st, int64 et, int nRoadIndex );
	
	bool mv_checksinglestatus( int64 st, int64 et, int64 nDelayTime, int64 nUpdateTime, int nRoadIndex, int &nLoopStatus, bool bFlag );

	void mvsavevideopar(unsigned int nFreqNum);//���������Ϣ
	void mvreadvideopar( FILE *fp );
	void mvsetdelayframe( int pardelay );

public:
	
	LoopShuterobj m_LoopShutter[BUFFER_SIZE_LIGHT];


	bool  m_Physic_Loop_Shutter;
	bool  m_Video_Loop_Shutter;
	int   m_ChannelNumber;
	unsigned int m_nMinSeq;
	

private:
	unsigned int m_nLoopNumber;
	vector<int> m_nDelyNum;
	

	int nDelayFrame;
	bool m_bStartShut;

};
















#endif